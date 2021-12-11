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

      array<ref TraderPlusIDs>IDs = GetTraderPlusIDConfig().IDs;
      foreach(int idx, TraderPlusIDs tpId: IDs)
      {
        foreach(string category: tpId.Categories)
        {
          string categoryPath = TRADERPLUS_DB_DIR_SERVER +"ID_"+tpId.Id.ToString()+"\\" + category + ".json";
          TraderPlusCategory tpStockCategory = new TraderPlusCategory;
    			TraderPlusJsonLoader<TraderPlusCategory>.LoadFromFile(categoryPath, tpStockCategory);
          foreach(int jdx, string product: tpStockCategory.Products)
          {
            string line = product;
            TStringArray token = new TStringArray;
            line.Split(" ", token);
            TStringArray strs = new TStringArray;
            TraderPlusPriceSettings traderPlusPriceSettings = GetTraderPlusPriceConfig();

            foreach(TraderPlusCategory tpCategoryPrice: traderPlusPriceSettings.TraderCategories)
            {
              if(tpCategoryPrice.CategoryName != category)continue;
              TStringArray tpPriceConfigProducts = new TStringArray;
              tpPriceConfigProducts = tpCategoryPrice.Products;
              foreach(string priceproduct: tpPriceConfigProducts)
              {
                string productline = priceproduct;
                productline.Split(",", strs);
                if(strs[0] == token[0])
                {
                  GetTraderPlusLogger().LogInfo("ID:" + tpId.Id + strs[0] + " = " + token[0]);
                  if(token[1].ToInt() >= strs[2].ToInt())
                  {
                    GetTraderPlusLogger().LogInfo(token[1] + " = " + strs[2]);
                    if(strs.Count() >= 7)
                    {
                      GetTraderPlusLogger().LogInfo(" strs.count = " + strs.Count());
                      if(strs[6].ToFloat() == 1.0)
                      {
                        GetTraderPlusLogger().LogInfo("product removed from stock ");
                        tpStockCategory.Products.RemoveOrdered(jdx);
                      }
                      else
                      {
                        token[1] = (token[1].ToInt() - Math.Round(token[1].ToInt() * strs[6].ToFloat())).ToString();
                        GetTraderPlusLogger().LogInfo("new stock value:" + token[1]);
                        string result_data = token[0] + " " + token[1] + " " + token[2];
                        tpStockCategory.Products.RemoveOrdered(jdx);
                        tpStockCategory.Products.Insert(result_data);
                      }
                    }
                  }
                }
              }
            }
          }
          tpStockCategory.Save(tpId.Id);
        }
      }
    }

    void DefaultTraderStock()
    {
      GetTraderPlusLogger().LogInfo("DefaultTraderStock - Started");
      if(GetTraderPlusPriceConfig().EnableDefaultTraderStock == 0)
      return;

      array<ref TraderPlusIDs>tpIDs = GetTraderPlusIDConfig().IDs;

      foreach(int idx, TraderPlusIDs tpId: tpIDs)
      {
        GetTraderPlusLogger().LogInfo("DefaultTraderStock id:"+tpId.Id.ToString());
        foreach(string category: tpId.Categories)
        {
          GetTraderPlusLogger().LogInfo("DefaultTraderStock category:"+category);
          TraderPlusCategory tpStockCategory = new TraderPlusCategory(category);

          TraderPlusPriceSettings traderPlusPriceSettings = GetTraderPlusPriceConfig();

          foreach(TraderPlusCategory tpCategoryPrice: traderPlusPriceSettings.TraderCategories)
          {
            if(tpCategoryPrice.CategoryName != category)continue;
            TStringArray tpPriceConfigProducts = new TStringArray;
            tpPriceConfigProducts = tpCategoryPrice.Products;
            foreach(string product: tpPriceConfigProducts)
            {
              TStringArray strs = new TStringArray;
              string productline = product;
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
                tpStockCategory.Products.Insert(data);
              }
            }
          }
          tpStockCategory.Save(tpId.Id);
        }
        GetTraderPlusLogger().LogInfo("DefaultTraderStock save:");
      }
      GetTraderPlusLogger().LogInfo("DefaultTraderStock - Ended");
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

    bool BuyRequest(TraderPlusProduct product)
    {
      product.Debug();
      bool state;
      int moneyAmount,substract_result;
      string line, result_data;
      TStringArray token = new TStringArray;

      bool canTrade = TraderPlusHelper.CheckifPlayerHasEnoughMoney(product.Customer,product.Price, product.TraderID, moneyAmount);
      GetTraderPlusLogger().LogInfo("money before trade:"+moneyAmount);
      if(!canTrade)return false;


      if(product.MaxStock == TRADEMODE_UNLIMITED)
      {
        state = TraderPlusHelper.CreateInInventoryWithState(product.Customer, product.ClassName, product.Health,product.Quantity);
        if(!state)return false;
        TraderPlusHelper.RemoveMoneyFromPlayer(product.Customer,product.Price, product.TraderID);
        return true;
      }

      TraderPlusCategory tpStockCategory = TraderPlusHelper.GetStockCategory(product.TraderID,product.Category);
      TStringArray stockProducts = tpStockCategory.Products;
      //we look for our product in stock in the category it's suppose to be
      for(int i=0; i<stockProducts.Count();i++)
      {
        line = stockProducts[i];
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
              tpStockCategory.Products.RemoveOrdered(i);
            }
            else
            {
              result_data = token.Get(0) + " " + substract_result.ToString() + " " + token.Get(2);
              tpStockCategory.Products.Set(i, result_data);
            }
            tpStockCategory.Save(product.TraderID);
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

      if(product.MaxStock == TRADEMODE_UNLIMITED)
      {
        if(product.TradMode == TRADEMODE_SELLVEHICLE){
          state = TraderPlusHelper.RemoveVehicleFromGarage(product.Customer, product.ClassName, product.Quantity, product.Health);
        }
        else{
          state = TraderPlusHelper.RemoveOurProduct(product.Customer, product.ClassName, product.Quantity, product.Health, false, product.Multiplier);
        }
        if(state)TraderPlusHelper.AddMoneyToPlayer(product.Customer,product.Price,product.TraderID);
        return true;
      }

      //we don't store infinite stock item to reduce the stock file size
      state = CheckStock(product);
      if(state)return true;

      //the stock doesn't contain our item so we can add it to our stock
      TraderPlusCategory tpStockCategory = TraderPlusHelper.GetStockCategory(product.TraderID,product.Category);
      TStringArray stockProducts = tpStockCategory.Products;

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
        tpStockCategory.Products.Insert(data);
        tpStockCategory.Save(product.TraderID);
        return state;
      }

      return false;
    }

    bool CheckStock(TraderPlusProduct product)
    {
      GetTraderPlusLogger().LogInfo("CheckStock");

      int health = product.Health;

      //if server owner only wants to store item with a pristine state
      if(GetTraderPlusConfigServer().StoreOnlyToPristineState)
          health=0;

      TraderPlusCategory tpStockCategory = TraderPlusHelper.GetStockCategory(product.TraderID,product.Category);
      TStringArray stockProducts = tpStockCategory.Products;

      for(int j=0; j<stockProducts.Count();j++)
      {
        TStringArray token = new TStringArray;
        string line = stockProducts[j];
        line.Split(" ",token);

        string StockClassName = token[0];
        string ProductClassName = product.ClassName;
        StockClassName.ToLower();
        ProductClassName.ToLower();
        bool state = false;
        if(StockClassName == ProductClassName && token[2] == health.ToString())
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
            int substract_result = token[1].ToInt() + product.Multiplier;
            string data;
            if(GetTraderPlusConfigServer().StoreOnlyToPristineState)
              data = token[0] + " " + substract_result.ToString() + " " + "0";
            else data = token[0] + " " + substract_result.ToString() + " " + token[2];
            tpStockCategory.Products.Set(j, data);
            tpStockCategory.Save(product.TraderID);
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
        if(product.TradMode == TRADEMODE_SELL)return false;
        foreach(string licence: GetTraderPlusConfigServer().Licences)
        {
          if(product.ClassName == licence)
          {
            if(product.Customer.m_BankAccount)
            {
              //In case licence is already there, who knows why ...
              if(product.Customer.m_BankAccount.Licences.Find(product.ClassName) == -1)
                  product.Customer.m_BankAccount.Licences.Insert(product.ClassName);
              TraderPlusHelper.RemoveMoneyFromPlayer(product.Customer,product.Price, product.TraderID );
              product.Customer.m_BankAccount.Save(product.Customer.GetIdentity().GetPlainId());
              GetTraderPlusLogger().LogInfo("Transaction Buy Succeeded:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" qty:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
              GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param3<int,TraderPlusStock, string>(TraderPlusResponse.BUY_SUCCESS,TraderPlusStock.GetStockFromID(product.TraderID, TraderPlusHelper.GetCategoriesFromID(product.TraderID)), product.Category), true, product.Customer.GetIdentity());
            }
            else
            {
              GetTraderPlusLogger().LogInfo("Transaction Buy Failed:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" qty:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
              GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param3<int,TraderPlusStock, string>(TraderPlusResponse.BUY_FAILED,TraderPlusStock.GetStockFromID(product.TraderID, TraderPlusHelper.GetCategoriesFromID(product.TraderID)), product.Category), true, product.Customer.GetIdentity());
            }
            return true;
          }
        }
      }
      return false;
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
            GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param3<int,TraderPlusStock, string>(TraderPlusResponse.SELL_SUCCESS,TraderPlusStock.GetStockFromID(product.TraderID, TraderPlusHelper.GetCategoriesFromID(product.TraderID)), product.Category), true, product.Customer.GetIdentity());
          }
          else
          {
            GetTraderPlusLogger().LogInfo("Transaction Sell Failed:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" quantity:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
            GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param3<int,TraderPlusStock, string>(TraderPlusResponse.SELL_FAILED,TraderPlusStock.GetStockFromID(product.TraderID, TraderPlusHelper.GetCategoriesFromID(product.TraderID)), product.Category), true, product.Customer.GetIdentity());
          }
        }
        else
        {
          bool BuySucceed = BuyRequest(product);
          if(BuySucceed)
          {
            GetTraderPlusLogger().LogInfo("Transaction Buy Succeeded:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" quantity:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
            GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param3<int,TraderPlusStock, string>(TraderPlusResponse.BUY_SUCCESS,TraderPlusStock.GetStockFromID(product.TraderID, TraderPlusHelper.GetCategoriesFromID(product.TraderID)), product.Category), true, product.Customer.GetIdentity());
          }
          else
          {
            GetTraderPlusLogger().LogInfo("Transaction Buy Failed:"+product.Customer.GetIdentity().GetName()+" product:"+product.ClassName +" quantity:"+(product.Quantity*product.Multiplier).ToString()+" health:"+product.Health.ToString()+" price:"+product.Price.ToString());
            GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param3<int,TraderPlusStock, string>(TraderPlusResponse.BUY_FAILED,TraderPlusStock.GetStockFromID(product.TraderID, TraderPlusHelper.GetCategoriesFromID(product.TraderID)), product.Category), true, product.Customer.GetIdentity());
          }
        }
      }
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
          traderID = TraderPlayer.TraderID;

        BuildingBase TraderBuilding = BuildingBase.Cast(data.param1);
        if (TraderBuilding)
          traderID = TraderBuilding.TraderID;

        if(traderID==-1)return;

       TraderPlusStock tpStock = new TraderPlusStock;
       tpStock = TraderPlusStock.GetStockFromID(traderID, TraderPlusHelper.GetCategoriesFromID(traderID));

       #ifdef TRADERPLUSDEBUG
  		 int count = tpStock.TraderPlusItems.Count();
  		 GetTraderPlusLogger().LogInfo("Stock count: "+count.ToString());
  		 #endif

       GetRPCManager().SendRPC("TraderPlus", "GetStockResponseBasedOnID",  new Param3<int,TraderPlusStock, string>(TraderPlusResponse.NO_TRADE,tpStock, ""), true, sender);

       #ifdef TRADERPLUSDEBUG
       GetTraderPlusLogger().LogInfo("GetStockRequestBasedOnID by player:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
       #endif
    }

    void GetTradeRequest(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
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
       if(product.TradMode == TRADEMODE_BUY)
          GetTraderPlusLogger().LogInfo("GetBuyRequest:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
       else GetTraderPlusLogger().LogInfo("GetSellRequest by player:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
       #endif
    }
    //---------------------------------------------------------------------------------------------------------//
};
