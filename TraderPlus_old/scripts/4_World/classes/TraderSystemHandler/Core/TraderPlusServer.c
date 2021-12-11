class TraderPlusServer
{
    ref array<ref TraderPlusStock> TraderStocks;
    ref array<ref ProductQueue> StockQueues;

    ref array<ref Object> ObjectTraders;

    float TraderTick;

    void TraderPlusServer()
    {
      GetTraderPlusLogger().LogInfo("TraderPlusServer - Started");
      TraderStocks      = new array<ref TraderPlusStock>;
      StockQueues       = new array<ref ProductQueue>;
      ObjectTraders     = new array<ref Object>;
      TraderTick        = 0;

      //I usually make a small delay to make sure that my static config class is available
      GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(initTraderPlusServer, 1000);
    }

    void  ~TraderPlusServer(){
    }

    void OnUpdate(float timeslice)
    {
      TraderTick+=timeslice;
      if(TraderTick > TRADERPLUS_QUEUE_TRANSACTION_INTERVAL)
      {
        foreach(ProductQueue queue: StockQueues)
        {
          if(queue.HasNextQueue())
          {
            TradeRequest(queue.Peek());
            queue.DeQueue();
          }
        }
        TraderTick = 0;
      }
    }

    void DestockHandler()
    {
      if(!GetTraderPlusPriceConfig().EnableAutoDestockAtRestart)
      return;

      for(int i=0;i<TraderStocks.Count();i++)
      {
        for(int j=0;j<TraderStocks[i].TraderPlusItems.Count();j++)
        {
          string line;
          TStringArray token = new TStringArray;
          line = TraderStocks[i].TraderPlusItems[j];
          line.Split(" ", token);
          for(int k=0;k<GetTraderPlusIDConfig().IDs[i].Categories.Count();k++)
          {
            int pos = -1;
            for(int ki=0;ki<GetTraderPlusPriceConfig().TraderCategories.Count();ki++)
            {
              if(GetTraderPlusPriceConfig().TraderCategories[ki].CategoryName == GetTraderPlusIDConfig().IDs[i].Categories[k])
              {
                pos = ki;
              }
            }
            if(pos == -1)continue;
            for(int l=0;l<GetTraderPlusPriceConfig().TraderCategories[pos].Products.Count();l++)
            {
              TStringArray strs = new TStringArray;
              string productline = GetTraderPlusPriceConfig().TraderCategories[pos].Products[l];
              productline.Split(",", strs);
              if(strs[0] == token[0])
              {
                GetTraderPlusLogger().LogInfo("ID:" + i + strs[0] + " = " + token[0]);
                if(token[1].ToInt() >= strs[2].ToInt())
                {
                  GetTraderPlusLogger().LogInfo(token[1] + " = " + strs[2]);
                  if(strs.Count() >= 7)
                  {
                    GetTraderPlusLogger().LogInfo(" strs.count = " + strs.Count());
                    if(strs[6].ToFloat() == 1.0)
                    {
                      GetTraderPlusLogger().LogInfo("product removed from stock ");
                      TraderStocks[i].TraderPlusItems.RemoveOrdered(j);
                    }
                    else
                    {
                      token[1] = (token[1].ToInt() - Math.Round(token[1].ToInt() * strs[6].ToFloat())).ToString();
                      GetTraderPlusLogger().LogInfo("new stock value:" + token[1]);
                      string result_data = token[0] + " " + token[1] + " " + token[2];
                      TraderStocks[i].TraderPlusItems.Set(j, result_data);
                    }
                  }
                }
              }
            }
          }
        }
        TraderStocks[i].Save(i);
      }
    }

    void DefaultTraderStock()
    {
      if(GetTraderPlusPriceConfig().EnableDefaultTraderStock == 0)
      return;

      for(int i=0;i<TraderStocks.Count();i++)
      {
          TraderStocks[i].TraderPlusItems.Clear();
          for(int k=0;k<GetTraderPlusIDConfig().IDs[i].Categories.Count();k++)
          {
            int pos = -1;
            for(int ki=0;ki<GetTraderPlusPriceConfig().TraderCategories.Count();ki++)
            {
              if(GetTraderPlusPriceConfig().TraderCategories[ki].CategoryName == GetTraderPlusIDConfig().IDs[i].Categories[k])
              {
                pos = ki;
              }
            }
            if(pos == -1)continue;
            for(int l=0;l<GetTraderPlusPriceConfig().TraderCategories[pos].Products.Count();l++)
            {
              TStringArray strs = new TStringArray;
              string productline = GetTraderPlusPriceConfig().TraderCategories[pos].Products[l];
              productline.Split(",", strs);
              int maxStock = strs[2].ToInt();
              if(maxStock > 0)
              {
                string data = "";
                if(GetTraderPlusPriceConfig().EnableDefaultTraderStock == 2)
                {
                  int randomStock = Math.RandomIntInclusive(0,maxStock);
                  data = strs[0] + " " + randomStock.ToString() + " " + "0";
                }
                else
                {
                  data = strs[0] + " " + strs[2] + " " + "0";
                }
                TraderStocks[i].TraderPlusItems.Insert(data);
              }
            }
          }
        TraderStocks[i].Save(i);
      }

      //reset the variable so the stock isn't reset at default stock next restart !
      GetTraderPlusPriceConfig().EnableDefaultTraderStock = 0;
      GetTraderPlusPriceConfig().Save()
    }

    void initTraderPlusServer()
    {
      LoadStockConfig();
      SetTradersSpawner();
      SetObjectSpawner();
      DestockHandler();
      DefaultTraderStock();
    }

    void LoadStockConfig()
    {
      int count = GetTraderPlusIDConfig().IDs.Count();
      GetTraderPlusLogger().LogInfo("ID_count: "+count.ToString());
      for(int i = 0 ; i< count ; i++)
      {
        TraderPlusStock m_tempStock = TraderPlusStock.Load(i);
        TraderStocks.Insert(m_tempStock);
        StockQueues.Insert(new ProductQueue());
      }
    }

    void SetTradersSpawner()
    {
      array<ref TraderPlusData>Traders = GetTraderPlusConfigServer().Traders;
      for(int i = 0;i<Traders.Count();i++)
      {
        string objetName = Traders.Get(i).Name;
    		Object obj = GetGame().CreateObject(objetName, vector.Zero, false, false);
    		if (!obj) return;
        GetTraderPlusLogger().LogInfo("obj created: "+objetName);
        ObjectTraders.Insert(obj);

        PlayerBase TraderPlayer = PlayerBase.Cast(obj);
    		if (TraderPlayer)
        {
          GetTraderPlusLogger().LogInfo("TraderPlayer created and added!: ");
          TraderPlayer.SetupTrader(Traders.Get(i));
          continue;
        }

        BuildingBase TraderBuilding = BuildingBase.Cast(obj);
    		if (TraderBuilding)
        {
          GetTraderPlusLogger().LogInfo("TraderStatic created and added!: ");
          TraderBuilding.SetupTrader(Traders.Get(i));
        }else GetTraderPlusLogger().LogInfo("TraderStatic was NOT created ! Make sure your static object extends BuildingBase as the documentation tells you!");
      }
    }

    void SetObjectSpawner()
    {
      array<ref TraderPlusObject>TraderObjects = GetTraderPlusConfigServer().TraderObjects;
      for(int i = 0;i<TraderObjects.Count();i++)
      {
        string objetName = TraderObjects.Get(i).ObjectName;
    		Object obj = GetGame().CreateObject(objetName, vector.Zero, false, false);
    		if (!obj) return;

        obj.SetPosition(TraderObjects.Get(i).Position);
        obj.SetOrientation(TraderObjects.Get(i).Orientation);
      }
    }

    void TradeRequest(TraderPlusProduct product)
    {
      if(product.Customer)
      {
        if(product.TradMode == TRADEMODE_SELL || product.TradMode == TRADEMODE_SELLVEHICLE)
        {
          bool SellSucceed = SellRequest(product);
          if(SellSucceed)
          {
            GetTraderPlusLogger().LogInfo("Transaction Sell Succeeded:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" quantity:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
            GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param2<int,ref TraderPlusStock>(TraderPlusResponse.SELL_SUCCESS,TraderStocks.Get(product.TraderID)), true, product.Customer.GetIdentity());
          }
          else
          {
            GetTraderPlusLogger().LogInfo("Transaction Sell Failed:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" quantity:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
            GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param2<int,ref TraderPlusStock>(TraderPlusResponse.SELL_FAILED,TraderStocks.Get(product.TraderID)), true, product.Customer.GetIdentity());
          }
        }
        else
        {
          bool BuySucceed = BuyRequest(product);
          if(BuySucceed)
          {
            GetTraderPlusLogger().LogInfo("Transaction Buy Succeeded:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" quantity:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
            GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param2<int,ref TraderPlusStock>(TraderPlusResponse.BUY_SUCCESS,TraderStocks.Get(product.TraderID)), true, product.Customer.GetIdentity());
          }
          else
          {
            GetTraderPlusLogger().LogInfo("Transaction Buy Failed:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" quantity:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
            GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param2<int,ref TraderPlusStock>(TraderPlusResponse.BUY_FAILED,TraderStocks.Get(product.TraderID)), true, product.Customer.GetIdentity());
          }
        }
      }
    }

    bool BuyRequest(TraderPlusProduct product)
    {
      //#ifdef TRADERPLUSDEBUG
      product.Debug();
      //#endif
      bool state;
      int interval_low,interval_high,stock_count, result,substract_result;
      string line, result_data;
      TStringArray token = new TStringArray;

      bool canTrade = TraderPlusHelper.CheckifPlayerHasEnoughMoney(product.Customer,product.Price, product.TraderID);
      if(!canTrade)return false;

      if(product.MaxStock == -1)
      {
        state = TraderPlusHelper.CreateInInventoryWithState(product.Customer, product.ClassName, product.Health,product.Quantity);
        if(!state)return false;
        TraderPlusHelper.RemoveMoneyFromPlayer(product.Customer,product.Price, product.TraderID);
        return true;
      }

      interval_low = 0;
      interval_high = product.Position + 5;
      stock_count = TraderStocks.Get(product.TraderID).TraderPlusItems.Count();
      if(product.Position - 5 > 0){
        interval_low = product.Position - 5;
      }
      if(interval_high > stock_count){
        interval_high = stock_count;
      }

      //we look for our product in stock on a small part of the stock list based on client stock position
      for(int i=interval_low; i<interval_high;i++)
      {
        line = TraderStocks.Get(product.TraderID).TraderPlusItems.Get(i);
        line.Split(" ",token);
        if(token[0] == product.ClassName && token[2] == product.Health.ToString())
        {
					if(token[1].ToInt()<product.Multiplier)
          {
            return false;
          }
          else
          {
            state = TraderPlusHelper.CreateInInventoryWithState(product.Customer, product.ClassName, product.Health,product.Quantity);
            if(!state)return false;
            TraderPlusHelper.RemoveMoneyFromPlayer(product.Customer,product.Price,product.TraderID);
            substract_result = token[1].ToInt() - Math.AbsInt(product.Multiplier);
            if(substract_result == 0)
            {
              TraderStocks.Get(product.TraderID).TraderPlusItems.RemoveOrdered(i);
            }
            else
            {
              result_data = token.Get(0) + " " + substract_result.ToString() + " " + token.Get(2);
              TraderStocks.Get(product.TraderID).TraderPlusItems.Set(i, result_data);
            }
            TraderStocks.Get(product.TraderID).Save(product.TraderID);
            return true;
          }
        }
        token.Clear();
      }

      //we did not find it so we try again with full list
      for(int j=interval_low; j<stock_count;j++)
      {
        line = TraderStocks.Get(product.TraderID).TraderPlusItems.Get(j);
        line.Split(" ",token);
        if(token[0] == product.ClassName && token[2] == product.Health.ToString())
        {
					if(token[1].ToInt()<product.Quantity)
          {
            return false;
          }
          else
          {
            state = TraderPlusHelper.CreateInInventoryWithState(product.Customer, product.ClassName, product.Health,product.Quantity);
            if(!state)return false;
            TraderPlusHelper.RemoveMoneyFromPlayer(product.Customer,product.Price,product.TraderID);
            substract_result = token[1].ToInt() - product.Multiplier;
            result_data = token[0] + " " + substract_result.ToString() + " " + token[2];
            if(substract_result == 0)
            {
              TraderStocks.Get(product.TraderID).TraderPlusItems.RemoveOrdered(i);
            }
            else
            {
              TraderStocks.Get(product.TraderID).TraderPlusItems.Set(i, result_data);;
              TraderStocks.Get(product.TraderID).Save(product.TraderID);
            }
            return true;
          }
        }
        token.Clear();
      }
      return false;
    }

    bool SellRequest(TraderPlusProduct product)
    {
      //#ifdef TRADERPLUSDEBUG
      product.Debug();
      //#endif
      bool state;
      string data;
      int stock_count = TraderStocks.Get(product.TraderID).TraderPlusItems.Count();

      //we don't store infinite stock item to reduce the stock file size
      if(product.MaxStock == -1)
      {
        if(product.TradMode == TRADEMODE_SELLVEHICLE){
          state = TraderPlusHelper.RemoveVehicleFromGarage(product.Customer, product.ClassName, product.Quantity, product.Health);
        }
        else{
          state = TraderPlusHelper.RemoveOurProduct(product.Customer, product.ClassName, product.Quantity, product.Health, false, product.Multiplier);
        }
        if(state)
        {
          TraderPlusHelper.AddMoneyToPlayer(product.Customer,product.Price,product.TraderID);
        }
        return state;
      }

      //If position == -1 it means item doesn't exist in stock so we should be able to add it directly into the stock, but it's possible the previous customer added that product so we must check all stock anyway
      if(product.Position == -1)
      {
        state = CheckStock(product, 0, stock_count);
        if(state)return true;

        //the stock doesn't contain our item so we can add it to our stock
        if(product.TradMode == TRADEMODE_SELLVEHICLE){
          state = TraderPlusHelper.RemoveVehicleFromGarage(product.Customer, product.ClassName, product.Quantity, product.Health);
        }
        else{
          state = TraderPlusHelper.RemoveOurProduct(product.Customer, product.ClassName, product.Quantity, product.Health, false, product.Multiplier);
        }
        if(state)
        {
          TraderPlusHelper.AddMoneyToPlayer(product.Customer,product.Price,product.TraderID);
          if(GetTraderPlusConfigServer().StoreOnlyToPristineState)
          {
            data = product.ClassName + " " + product.Multiplier.ToString() +" "+"0";
          }else data = product.ClassName + " " + product.Multiplier.ToString() +" "+product.Health.ToString();
          TraderStocks.Get(product.TraderID).TraderPlusItems.Insert(data);
          TraderStocks.Get(product.TraderID).Save(product.TraderID);
          return state;
        }
      }
      else //we checked a small part of the stock to find our item regarding the position found on client, we check position + 5< posiiton< position + 5 in case position change because of previous trade in queue
      {
        int interval_low = 0;
        int interval_high = product.Position + 5;
        stock_count = TraderStocks.Get(product.TraderID).TraderPlusItems.Count();
        if(product.Position - 5 > 0){
          interval_low = product.Position - 5;
        }
        if(interval_high > stock_count){
          interval_high = stock_count;
        }

        //check small part of the stock list hoping to find it
        state = CheckStock(product, interval_low, interval_high);
        if(state)return true;

        //check all stock because we haven't found our product in the small one...
        state = CheckStock(product, 0, stock_count);
        if(state)return true;

        //if all previous got fucked, it means previous customer bought it so we add it to the stock
        if(product.TradMode == TRADEMODE_SELLVEHICLE){
          state = TraderPlusHelper.RemoveVehicleFromGarage(product.Customer, product.ClassName, product.Quantity, product.Health);
        }
        else{
          state = TraderPlusHelper.RemoveOurProduct(product.Customer, product.ClassName, product.Quantity, product.Health, false, product.Multiplier);
        }
        if(state)
        {
          TraderPlusHelper.AddMoneyToPlayer(product.Customer,product.Price,product.TraderID);
          if(GetTraderPlusConfigServer().StoreOnlyToPristineState)
          {
            data = product.ClassName + " " + product.Multiplier.ToString() +" "+"0";
          }else data = product.ClassName + " " + product.Multiplier.ToString() +" "+product.Health.ToString();
          TraderStocks.Get(product.TraderID).TraderPlusItems.Insert(data);
          TraderStocks.Get(product.TraderID).Save(product.TraderID);
          return state;
        }

        //we should not be here
        return false;
      }
      return false;
    }

    bool CheckStock(TraderPlusProduct product, int interval_low, int interval_high)
    {
      //GetTraderPlusLogger().LogInfo("CheckStock interval_low:"+interval_low.ToString()+"interval_high"+interval_high.ToString());
      int health = product.Health;

      //if server owner only wants to store item with a pristine state
      if(GetTraderPlusConfigServer().StoreOnlyToPristineState)
      {
        health=0;
      }

      for(int j=interval_low; j<interval_high;j++)
      {
        TStringArray token = new TStringArray;
        string line = TraderStocks.Get(product.TraderID).TraderPlusItems.Get(j);
        line.Split(" ",token);

        string StockClassName = token[0];
        string ProductClassName =  product.ClassName;
        StockClassName.ToLower();
        ProductClassName.ToLower();
        bool state = false;
        //GetTraderPlusLogger().LogInfo("product classname:"+product.ClassName + " product health:"+product.Health.ToString());
        //GetTraderPlusLogger().LogInfo("classname:"+token[0] + " health:"+token[2]);
        if(StockClassName == ProductClassName && token[2] == health.ToString())
        {
          //GetTraderPlusLogger().LogInfo("==");
          if(product.TradMode == TRADEMODE_SELLVEHICLE){
            state = TraderPlusHelper.RemoveVehicleFromGarage(product.Customer, product.ClassName, product.Quantity, product.Health);
          }
          else{
            state = TraderPlusHelper.RemoveOurProduct(product.Customer, product.ClassName, product.Quantity, product.Health, false, product.Multiplier);
          }
          if(state)
          {
            TraderPlusHelper.AddMoneyToPlayer(product.Customer,product.Price,product.TraderID);
            int substract_result = token[1].ToInt() + product.Multiplier;
            string data;
            if(GetTraderPlusConfigServer().StoreOnlyToPristineState)
            {
              data = token[0] + " " + substract_result.ToString() + " " + "0";
            }else data = token[0] + " " + substract_result.ToString() + " " + token[2];
            TraderStocks.Get(product.TraderID).TraderPlusItems.Set(j, data);
            TraderStocks.Get(product.TraderID).Save(product.TraderID);
            return true;
          }
          else
          {
            return false;
          }
        }
        token.Clear();
      }
      return false;
    }

    bool LicenceBuyHandler(TraderPlusProduct product)
    {
      if(product.ClassName.Contains(GetTraderPlusConfigServer().LicenceKeyWord))
      {
        if(product.TradMode == 1)return false;
        for(int i=0;i<GetTraderPlusConfigServer().Licences.Count();i++)
        {
          if(product.ClassName == GetTraderPlusConfigServer().Licences[i])
          {
            if(product.Customer.m_BankAccount)
            {
              //In case licence is already there, who knows why ...
              if(product.Customer.m_BankAccount.Licences.Find(product.ClassName) == -1)
              {
                product.Customer.m_BankAccount.Licences.Insert(product.ClassName);
              }
              TraderPlusHelper.RemoveMoneyFromPlayer(product.Customer,product.Price, product.TraderID );
              product.Customer.m_BankAccount.Save(product.Customer.GetIdentity().GetPlainId());
              GetTraderPlusLogger().LogInfo("Transaction Buy Succeeded:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" qty:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
              GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param2<int,ref TraderPlusStock>(TraderPlusResponse.BUY_SUCCESS,TraderStocks.Get(product.TraderID)), true, product.Customer.GetIdentity());
            }
            else
            {
              GetTraderPlusLogger().LogInfo("Transaction Buy Failed:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" qty:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
              GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param2<int,ref TraderPlusStock>(TraderPlusResponse.BUY_FAILED,TraderStocks.Get(product.TraderID)), true, product.Customer.GetIdentity());
            }
            return true;
          }
        }
      }
      return false;
    }

    //-------------------------------------------RPC PART--------------------------------------------------------//
    void GetStockRequestBasedOnID(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (!GetGame().IsServer())
          return;

         Param1<Object> data;
         if (!ctx.Read(data))
           return;

          int traderID=-1;

          PlayerBase TraderPlayer = PlayerBase.Cast(data.param1);
          if(TraderPlayer)
          {
            traderID = TraderPlayer.TraderID;
          }

          BuildingBase TraderBuilding = BuildingBase.Cast(data.param1);
          if (TraderBuilding)
          {
            traderID = TraderBuilding.TraderID;
          }

       if(traderID==-1)return;

       TraderPlusStock m_tempStock = TraderStocks.Get(traderID);

       #ifdef TRADERPLUSDEBUG
  		 int count = m_tempStock.TraderPlusItems.Count();
  		 GetTraderPlusLogger().LogInfo("Stock count: "+count.ToString());
  		 count = TraderStocks.Get(traderID).TraderPlusItems.Count();
  		 GetTraderPlusLogger().LogInfo("Stock count: "+count.ToString());
  		 #endif

       GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param2<int,ref TraderPlusStock>(TraderPlusResponse.NO_TRADE,m_tempStock), true, sender);

       #ifdef TRADERPLUSDEBUG
       GetTraderPlusLogger().LogInfo("GetStockRequestBasedOnID by player:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
       #endif
    }

    void GetBuyRequest(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
    {
     if (!GetGame().IsServer())
       return;

       Param1<ref TraderPlusProduct> data;
       if (!ctx.Read(data))
         return;

       PlayerBase player = TraderPlusGetPlayerByIdentity(sender);

       TraderPlusProduct product = data.param1;
       product.Customer = player;

       if(LicenceBuyHandler(product))return;

       StockQueues[product.TraderID].EnQueue(product);

       //true equal we remove from storage to create in inventory
       #ifdef TRADERPLUSDEBUG
       product.Debug();
       GetTraderPlusLogger().LogInfo("GetBuyRequest:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
       #endif
    }

    void GetSellRequest(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
    {
     if (!GetGame().IsServer())
       return;

      Param1<ref TraderPlusProduct> data;
      if (!ctx.Read(data))
         return;

      PlayerBase player = TraderPlusGetPlayerByIdentity(sender);

      TraderPlusProduct product = data.param1;
      product.Customer = player;

      StockQueues[product.TraderID].EnQueue(product);

      #ifdef TRADERPLUSDEBUG
      GetTraderPlusLogger().LogInfo(StockQueues[product.TraderID].Peek().ClassName);
      GetTraderPlusLogger().LogInfo("GetSellRequest by player:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
      product.Debug();
      #endif
    }
    //---------------------------------------------------------------------------------------------------------//
};
