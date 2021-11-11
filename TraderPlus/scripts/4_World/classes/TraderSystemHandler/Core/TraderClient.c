class TraderPlusClient
{
	ref TraderPlusStock m_TraderStock;
	ref array<ref TraderPlusCategory>m_TraderCategories;
	ref array<ref TraderPlusItem>m_TraderPlusItems;
	ref array<string> m_StockCategories;

	bool EnableStockAllCategoryForID;

	ref TraderPlusPriceSettings m_temppriceconfig;

	bool m_StockRequest;

	void TraderPlusClient()
	{
		m_TraderStock      = new TraderPlusStock;
		m_TraderCategories = new array<ref TraderPlusCategory>;
		m_TraderPlusItems  = new array<ref TraderPlusItem>;
		m_StockCategories  = new array<string>;
		m_temppriceconfig  = new  TraderPlusPriceSettings;
  }

	int GetItemInStockFromCategory(int pos, out array<string> m_StockItemsNames,out array<int>m_StockItemsQuantities,out array<int>m_StockItemsStates, out array<int>m_StockItemsMaxStock, bool showall = false, string filter = "")
	{
		filter.ToLower();
		m_TraderPlusItems.Clear();
		if(pos == 0 && GetTraderPlusConfigClient().EnableStockAllCategory && EnableStockAllCategoryForID){
			GetTraderPlusItemsListFromAllCategory(m_StockCategories);
		}else GetTraderPlusItemsListFromCategory(m_StockCategories.Get(pos));

		#ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("GetItemInStockFromCategory: TraderPlusItems.Count:"+m_TraderPlusItems.Count().ToString() + "maxstock.count"+m_StockItemsMaxStock.Count().ToString());
		#endif

		m_StockItemsNames.Clear();
		m_StockItemsQuantities.Clear();
		m_StockItemsStates.Clear();
		m_StockItemsMaxStock.Clear();

		for(int i=0;i<m_TraderPlusItems.Count();i++)
		{
			bool skip = false;
			#ifdef TRADERPLUSDEBUG
			GetTraderPlusLogger().LogInfo("GetItemInStockFromCategory: TraderPlusStock:"+m_TraderStock.TraderPlusItems.Count());
			#endif
			for(int j = 0 ; j<m_TraderStock.TraderPlusItems.Count();j++)
			{
				string str = m_TraderStock.TraderPlusItems.Get(j);
				string token[3];
				int result = str.ParseString(token);
				if(TraderPlusHelper.Compare2String(token[0],m_TraderPlusItems.Get(i).ClassName) && TraderPlusHelper.CanAddProductToList(filter, m_TraderPlusItems.Get(i).ClassName))
				{
						#ifdef TRADERPLUSDEBUG
					  GetTraderPlusLogger().LogInfo("GetItemInStockFromCategory: TraderPlusItems["+j.ToString()+"] - classname:"+token[0]);
					  #endif
						m_StockItemsNames.Insert(token[0]);
						m_StockItemsQuantities.Insert(token[1].ToInt());
						m_StockItemsStates.Insert(token[2].ToInt());
						m_StockItemsMaxStock.Insert(m_TraderPlusItems.Get(i).MaxStock);
						skip = true;
						continue;
				}
			}
			if(m_TraderPlusItems.Get(i).MaxStock == -1 && !skip && TraderPlusHelper.CanAddProductToList(filter, m_TraderPlusItems.Get(i).ClassName))
			{
				#ifdef TRADERPLUSDEBUG
				GetTraderPlusLogger().LogInfo("m_TraderPlusItems.Get(i).MaxStock == -1");
				#endif
				m_StockItemsNames.Insert(m_TraderPlusItems.Get(i).ClassName);
				m_StockItemsQuantities.Insert(0);
				m_StockItemsStates.Insert(0);
				m_StockItemsMaxStock.Insert(m_TraderPlusItems.Get(i).MaxStock);
				skip = true;
			}
			if(showall && !skip && TraderPlusHelper.CanAddProductToList(filter, m_TraderPlusItems.Get(i).ClassName))
			{
				#ifdef TRADERPLUSDEBUG
				GetTraderPlusLogger().LogInfo("GetItemInStockFromCategory: showall:");
				#endif
				m_StockItemsNames.Insert(m_TraderPlusItems.Get(i).ClassName);
				m_StockItemsQuantities.Insert(0);
				m_StockItemsStates.Insert(0);
				m_StockItemsMaxStock.Insert(m_TraderPlusItems.Get(i).MaxStock);
			}
		}
		return m_StockItemsNames.Count();
	}

	int GetPlayerItemsFromCategory(int pos, out array<string> m_playersItemsClassName, out array<string>m_playersItemsCount, out array<string>m_playersItemsQuantity,out array<string>m_playersItemsHealth, out array<bool>m_playersItemsHasAttachments, string filter = "")
	{
		filter.ToLower();
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if(!player)return 0;

		if(pos == 2)
		{
			m_playersItemsClassName.Clear();
			m_playersItemsCount.Clear();
			m_playersItemsQuantity.Clear();
			m_playersItemsHealth.Clear();
			m_playersItemsHasAttachments.Clear();

			for(int li=0;li<GetBankAccount().Licences.Count();li++)
      {
        m_playersItemsClassName.Insert(GetBankAccount().Licences[li]);
				m_playersItemsQuantity.Insert("");
				m_playersItemsCount.Insert("1");
				m_playersItemsHealth.Insert("");
				m_playersItemsHasAttachments.Insert(false);
      }
			return m_playersItemsClassName.Count();
		}

		if(pos == 3)
		{
			m_playersItemsClassName.Clear();
			m_playersItemsCount.Clear();
			m_playersItemsQuantity.Clear();
			m_playersItemsHealth.Clear();
			m_playersItemsHasAttachments.Clear();

			for(int lv=0;lv<GetGarageCore().m_VehiclesName.Count();lv++)
			{
				m_playersItemsClassName.Insert(GetGarageCore().m_VehiclesName[lv]);
				m_playersItemsQuantity.Insert("1");
				m_playersItemsCount.Insert("1");
				m_playersItemsHealth.Insert(GetGarageCore().m_VehiclesHealth[lv].ToString());
				m_playersItemsHasAttachments.Insert(true);
			}
			return m_playersItemsClassName.Count();
		}

		bool state = TraderPlusHelper.GetPlayersItems(player,m_playersItemsClassName, m_playersItemsCount, m_playersItemsQuantity, m_playersItemsHealth,m_playersItemsHasAttachments,filter);
		if(state)
		{
			if(pos == 1)
			{
				return m_playersItemsClassName.Count();
			}
			else
			{
				// #ifdef TRADERPLUSDEBUG
				// GetTraderPlusLogger().LogInfo("GetItemInStockFromCategory: TraderPlusItems.Count:"+m_TraderPlusItems.Count().ToString());
				// #endif
				TStringArray Names = new TStringArray;
				TStringArray Counts = new TStringArray;
				TStringArray Qties = new TStringArray;
				TStringArray Healths = new TStringArray;
				TBoolArray   Attachs = new TBoolArray;

				for(int j = 0 ; j<m_playersItemsClassName.Count();j++)
				{
					string playerItem = m_playersItemsClassName[j];
					playerItem.ToLower();
					// if(!EnableStockAllCategoryForID)
					// {
					// 	GetTraderPlusItemsListFromAllCategory(m_StockCategories);
					// }
					for(int i=0;i<m_TraderPlusItems.Count();i++)
					{
						string traderItem = m_TraderPlusItems.Get(i).ClassName;
						string categoryName=m_TraderPlusItems.Get(i).CategoryName;
						traderItem.ToLower();
						// #ifdef TRADERPLUSDEBUG
						// GetTraderPlusLogger().LogInfo("GetItemInStockFromCategory: TraderPlusItems_classname"+m_TraderPlusItems.Get(i).ClassName+" m_playersItemsClassName:"+m_playersItemsClassName.Get(j));
						// #endif

						if(playerItem == traderItem && m_StockCategories.Find(categoryName) != -1 && m_TraderPlusItems.Get(i).SellPrice != -1)
						{
							Names.Insert(m_playersItemsClassName.Get(j));
							Counts.Insert(m_playersItemsCount.Get(j));
							Qties.Insert(m_playersItemsQuantity.Get(j));
							Healths.Insert(m_playersItemsHealth.Get(j));
							Attachs.Insert(m_playersItemsHasAttachments.Get(j));
						}
					}
				}

				m_playersItemsClassName.Clear();
				m_playersItemsCount.Clear();
				m_playersItemsQuantity.Clear();
				m_playersItemsHealth.Clear();
				m_playersItemsHasAttachments.Clear();

				m_playersItemsClassName = Names;
				m_playersItemsCount     = Counts;
				m_playersItemsQuantity  = Qties;
				m_playersItemsHealth    = Healths;
				m_playersItemsHasAttachments = Attachs;

				CombinedSpecificItems(m_playersItemsClassName,m_playersItemsCount, m_playersItemsQuantity,m_playersItemsHealth,m_playersItemsHasAttachments);
			}
			return m_playersItemsClassName.Count();
		}
		return 0;
	}

	void CombinedSpecificItems(out array<string> m_playersItemsClassName, out array<string>m_playersItemsCount, out array<string>m_playersItemsQuantity,out array<string>m_playersItemsHealth, out array<bool>m_playersItemsHasAttachments)
	{
		// #ifdef TRADERPLUSDEBUG
		// GetTraderPlusLogger().LogInfo("CombinedSpecificItems + ITEMCLASSNAMECOUNT:"+m_playersItemsClassName.Count().ToString());
		// #endif
		TStringArray Names = new TStringArray;
		TStringArray Counts = new TStringArray;
		TStringArray Qties = new TStringArray;
		TStringArray Healths = new TStringArray;
		TBoolArray   Attachs = new TBoolArray;

		while(m_playersItemsClassName.Count()>0)
		{
			#ifdef TRADERPLUSDEBUG
			GetTraderPlusLogger().LogInfo("CombinedSpecificItems + ITEMCLASSNAMECOUNT:"+m_playersItemsClassName.Count().ToString());
			#endif
			string name = m_playersItemsClassName[0];
			string count = m_playersItemsCount[0];
			string qty = m_playersItemsQuantity[0];
			string health = m_playersItemsHealth[0];
			bool   hasattch = m_playersItemsHasAttachments[0];

			TIntArray SpecificItemsPositions = new TIntArray;

			m_playersItemsClassName.RemoveOrdered(0);
			m_playersItemsHealth.RemoveOrdered(0);
			m_playersItemsCount.RemoveOrdered(0);
			m_playersItemsQuantity.RemoveOrdered(0);
			m_playersItemsHasAttachments.RemoveOrdered(0);

			int countSpecificItem = 0;
			for(int i=0;i<m_playersItemsClassName.Count();i++)
			{
				if(m_playersItemsClassName[i]==name && m_playersItemsHealth[i]==health)
				{
					countSpecificItem++;
				}
			}

			int j=0;
			while(countSpecificItem!=0)
			{
				if(m_playersItemsClassName[j]==name && m_playersItemsHealth[j]==health)
				{
					#ifdef TRADERPLUSDEBUG
					GetTraderPlusLogger().LogInfo("BEFORE m_playersItemsClassName[j]"+m_playersItemsClassName[j]+" count:"+count+"qty="+qty);
					#endif
					count = (count.ToInt() + m_playersItemsCount[j].ToInt()).ToString();
					qty = (qty.ToInt() + m_playersItemsQuantity[j].ToInt()).ToString();
					#ifdef TRADERPLUSDEBUG
					GetTraderPlusLogger().LogInfo("AFTER m_playersItemsClassName[j]"+m_playersItemsClassName[j]+" count:"+count+"qty="+qty);
					#endif

					m_playersItemsClassName.RemoveOrdered(j);
					m_playersItemsHealth.RemoveOrdered(j);
					m_playersItemsCount.RemoveOrdered(j);
					m_playersItemsQuantity.RemoveOrdered(j);
					m_playersItemsHasAttachments.RemoveOrdered(j);
					countSpecificItem--;
					j=0;
				}else
				{
					j++;
				}
			}

			Names.Insert(name);
			Counts.Insert(count);
			Qties.Insert(qty);
			Healths.Insert(health);
			Attachs.Insert(hasattch);
		}

		m_playersItemsClassName.Clear();
		m_playersItemsCount.Clear();
		m_playersItemsQuantity.Clear();
		m_playersItemsHealth.Clear();
		m_playersItemsHasAttachments.Clear();

		m_playersItemsClassName = Names;
		m_playersItemsCount     = Counts;
		m_playersItemsQuantity  = Qties;
		m_playersItemsHealth    = Healths;
		m_playersItemsHasAttachments = Attachs;
	}

	//To try to be efficient on the server, we try to make its life easy by giving to the server the position of the product, to help find it on server stock
	int GetProductPositionFromStock(string name, string states)
	{
		if(GetTraderPlusConfigClient().StoreOnlyToPristineState)states = "0";
		for(int j = 0 ; j<m_TraderStock.TraderPlusItems.Count();j++)
		{
			string line = m_TraderStock.TraderPlusItems.Get(j);
			TStringArray strs = new TStringArray;
			line.Split( " ", strs );
			if(strs[0]==name && strs[2]==states)
			{
				return j;
			}
		}
		return -1;
	}

	int GetStockQtyFromPosition(int pos)
	{
		if(m_TraderStock)
		{
			string line = m_TraderStock.TraderPlusItems.Get(pos);
			TStringArray strs = new TStringArray;
			line.Split( " ", strs );
			return strs[1].ToInt();
		}
		return -1;
	}

	void ResetPriceConfig()
	{
		m_TraderCategories.Clear();
	}

	int GetCategoriesFromID(int id)
	{
		m_StockCategories.Clear();
		EnableStockAllCategoryForID = GetTraderPlusConfigClient().EnableStockAllCategoryForIDs.Get(id);
		string str = GetTraderPlusConfigClient().IDsCategories.Get(id);
		TStringArray strs = new TStringArray;
		str.Split(",",strs);
		int count = strs.Count();
		// #ifdef TRADERPLUSDEBUG
		// GetTraderPlusLogger().LogInfo("GetCategoriesFromID: "+id.ToString()+"count: "+count.ToString());
		// #endif
		for(int i=0;i<count;i++)
		{
			m_StockCategories.Insert(strs[i]);
		}
		return count;
	}

	bool IsCorrectCategory(string categoryname)
	{
		for(int i=0;i<m_StockCategories.Count();i++)
		{
			if(m_StockCategories[i] == categoryname)
			{
				return true;
			}
		}
		return false;
	}

	void GetTraderPlusItemsListFromCategory(string categoryname)
	{
		//In some cases we don't want to clear the items, that's why we need that reset condition
		m_TraderPlusItems.Clear();

		if(GetBankAccount() && GetBankAccount().Licences)
		{
			if(categoryname.Contains(GetTraderPlusConfigClient().LicenceKeyWord) && GetBankAccount().Licences.Find(categoryname) != -1)
				{
					return;
				}
		}

		for(int i=0; i<m_TraderCategories.Count();i++)
		{
			if(m_TraderCategories.Get(i).CategoryName == categoryname)
			{
				for(int j=0;j<m_TraderCategories.Get(i).Products.Count();j++)
				{
					string str = m_TraderCategories.Get(i).Products.Get(j);
					TStringArray strs = new TStringArray;
					str.Split( ",", strs );
					float sellprice = strs[5].ToFloat();
					float tradeqty = strs[3].ToFloat();
					int   maxqty = TraderPlusHelper.GetMaxItemQuantityClient(strs[0]);
					if( sellprice < 1.0 && sellprice != -1.0)
					{
						sellprice = strs[4].ToFloat() * strs[5].ToFloat();
					}
					tradeqty = CalculateTradeQty(strs[0],tradeqty,maxqty);
					// #ifdef TRADERPLUSDEBUG
					// GetTraderPlusLogger().LogInfo("GetTraderPlusItemsListFromCategory: sellprice"+sellprice.ToString()+" buyprice:"+strs[4] + "tradeqty:"+tradeqty.ToString()+" maxstock"+strs[2]);
					// #endif
					m_TraderPlusItems.Insert(new TraderPlusItem(categoryname,strs[0],strs[1].ToFloat(),strs[2].ToInt(),tradeqty,sellprice,strs[4].ToInt()));
				}
			}
		}
	}

	void GetTraderPlusItemsListFromAllCategory(array<string> categories)
	{
		//In some cases we don't want to clear the items, that's why we need that reset condition
		m_TraderPlusItems.Clear();
		// #ifdef TRADERPLUSDEBUG
		// GetTraderPlusLogger().LogInfo("GetTraderPlusItemsListFromAllCategory: traderplusitems.count:"+m_TraderPlusItems.Count().ToString());
		// GetTraderPlusLogger().LogInfo("GetTraderPlusItemsListFromAllCategory: TraderCategories.Count:"+m_TraderCategories.Count().ToString());
		// #endif

		for(int i=0; i<m_TraderCategories.Count();i++)
		{
			for(int k=0; k<categories.Count();k++)
			{
				if(m_TraderCategories.Get(i).CategoryName == categories[k])
				{
					if(GetBankAccount() && GetBankAccount().Licences){
						if(categories[k].Contains(GetTraderPlusConfigClient().LicenceKeyWord) && GetBankAccount().Licences.Find(categories[k]) != -1)
							continue;
					}

					for(int j=0;j<m_TraderCategories.Get(i).Products.Count();j++)
					{
						string str = m_TraderCategories.Get(i).Products.Get(j);
						TStringArray strs = new TStringArray;
						str.Split( ",", strs );
						float sellprice = strs[5].ToFloat();
						if( sellprice < 1.0 && sellprice != -1.0)
						{
							sellprice = strs[4].ToFloat() * strs[5].ToFloat();
						}
						float tradeqty = strs[3].ToFloat();
						int   maxqty   = TraderPlusHelper.GetMaxItemQuantityClient(strs[0]);
						tradeqty = CalculateTradeQty(strs[0],tradeqty,maxqty);
						// #ifdef TRADERPLUSDEBUG
						// GetTraderPlusLogger().LogInfo("ItemName:"+strs[0].ToLower()+" tradeqty:"+strs[3] + " maxstock" + strs[2]);
						// #endif
						m_TraderPlusItems.Insert(new TraderPlusItem(categories[k],strs[0],strs[1].ToFloat(),strs[2].ToInt(),tradeqty,sellprice,strs[4].ToInt()));
					}
				}
			}
		}
	}

	float CalculateTradeQty(string classname,float tradeqty, int maxqty)
	{
		//if the user fucked up the tradqty, we define it as maxqty of the item
		if(tradeqty > maxqty)return maxqty;

		//in case it's a mag and user did not define 0 or Full
		if(classname.Contains("Mag_") && tradeqty != 0.0 )return 0;

		//if our tradeqty is a % or maxqty
		if(tradeqty < 1.0 && tradeqty != 0.0 && tradeqty != -1.0 ) return tradeqty*(1.0*maxqty);

		//if we want to define maxqty of our product
		if(tradeqty == -1.0)return maxqty;

		//finally we return tradeqty if everything is ok or should be...
		return tradeqty;
	}

	//-------------------------------------------RPC PART--------------------------------------------------------//
	void GetStockResponseBasedOnID(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
  {
   	if(!GetGame().IsClient())
     return;

		 #ifdef TRADERPLUSDEBUG
		 GetTraderPlusLogger().LogInfo("GetStockResponseBaseOnIDCategory");
		 #endif

     Param2<int, ref TraderPlusStock> data;
     if (!ctx.Read(data))
       return;


     //We get our stock based on the TraderID from the Trader Menu request
     TraderPlusStock m_tempStock = data.param2;
		 m_TraderStock.TraderPlusItems.Clear();
		 m_TraderStock = m_tempStock;

		 #ifdef TRADERPLUSDEBUG
		 int count = m_tempStock.TraderPlusItems.Count();
		 GetTraderPlusLogger().LogInfo("Stock count: "+count.ToString());
		 count = m_TraderStock.TraderPlusItems.Count();
		 GetTraderPlusLogger().LogInfo("Stock count: "+count.ToString());
		 #endif

		 PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		 if(player && player.m_TraderPlusMenu)
		 {
			 player.m_TraderPlusMenu.UIUpdate();
		 }
		 //We check what kind of stock response is it: Is it a sell/buy update ? or a NO_TRADE response
		 int response = data.param1;
		 if(response == TraderPlusResponse.NO_TRADE)return;

		 if(player && player.m_TraderPlusMenu)
		 {
			 player.m_TraderPlusMenu.GetTradingResponse(response);
		 }
  }

	void GetPriceRequestFromCategory(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (!GetGame().IsClient())
      return;

		#ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("GetPriceRequestFromCategory");
		#endif

    Param1<ref TraderPlusCategory> data;
    if (!ctx.Read(data))
        return;
		m_TraderCategories.Insert(data.param1);
		m_temppriceconfig.AddCategoryToConfigClient(data.param1);
	}
}
