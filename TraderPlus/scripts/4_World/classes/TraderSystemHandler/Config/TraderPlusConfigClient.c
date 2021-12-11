class TraderPlusGnrlConfigClient
{
  /*Sometimes, our config cannot be send to client so we need to define an intermediary config*/
	bool   EnableShowAllPrices;
	bool   IsReceiptTraderOnly;
	bool   UseGarageToTradeCar;
	bool   EnableShowAllCheckBox;
	bool   DisableHeightFailSafeForReceiptDeployment;
	bool 	 AcceptWorn, AcceptDamaged, AcceptBadlyDamaged;
	bool   StoreOnlyToPristineState;
	bool   EnableStockAllCategory;
	string LicenceKeyWord;
	ref    map<int, bool>EnableStockAllCategoryForIDs;
	ref    map<int, string>IDsCategories;
	ref    map<int, string>CurrenciesAccepted;
	ref    map<int, string>Licences;
	ref 	 array<string>MoneyName;
	ref 	 array<int>MoneyValue;
	ref    array<string>VehicleNames;
	ref    array<vector>TraderPos;
	ref    array<string>GivenNames;
	ref    array<string>Roles;

  void TraderPlusGnrlConfigClient()
  {
		EnableStockAllCategoryForIDs = new map<int, bool>;
		IDsCategories 							 = new map<int, string>;
		CurrenciesAccepted					 = new map<int, string>;
		Licences        						 = new map<int, string>;
		MoneyName 									 = new array<string>;
		MoneyValue 									 = new array<int>;
		VehicleNames   						   = new array<string>;
		GivenNames      						 = new array<string>;
		Roles           						 = new array<string>;
		TraderPos       						 = new array<vector>;

  }

	void TransformToSendableConfig(TraderPlusGeneralSettings m_gnrlconfig,TraderPlusIDsSettings m_TraderPlusIDsSettings,TraderPlusVehiclesSettings    m_TraderPlusVehiclesSettings)
	{
		EnableShowAllPrices   = m_gnrlconfig.EnableShowAllPrices;
		UseGarageToTradeCar   = m_gnrlconfig.UseGarageToTradeCar;
		AcceptWorn 					 = m_gnrlconfig.AcceptedStates.AcceptWorn;
		AcceptDamaged 			 = m_gnrlconfig.AcceptedStates.AcceptDamaged;
		AcceptBadlyDamaged 	 = m_gnrlconfig.AcceptedStates.AcceptBadlyDamaged;
		IsReceiptTraderOnly  = m_gnrlconfig.IsReceiptTraderOnly;
		LicenceKeyWord       = m_gnrlconfig.LicenceKeyWord;
		DisableHeightFailSafeForReceiptDeployment= m_gnrlconfig.DisableHeightFailSafeForReceiptDeployment;
		EnableShowAllCheckBox= m_gnrlconfig.EnableShowAllCheckBox;
		StoreOnlyToPristineState= m_gnrlconfig.StoreOnlyToPristineState;
		EnableStockAllCategory = m_gnrlconfig.EnableStockAllCategory;
		for(int h=0;h<m_gnrlconfig.Traders.Count();h++)
		{
			TraderPos.Insert(m_gnrlconfig.Traders.Get(h).Position);
			GivenNames.Insert(m_gnrlconfig.Traders.Get(h).GivenName);
			Roles.Insert(m_gnrlconfig.Traders.Get(h).Role);
		}

		for(int i=0;i<m_gnrlconfig.Currencies.Count();i++)
		{
			MoneyName.Insert(m_gnrlconfig.Currencies.Get(i).ClassName);
			MoneyValue.Insert(m_gnrlconfig.Currencies.Get(i).Value);
		}

		for(int j=0;j<m_TraderPlusIDsSettings.IDs.Count();j++)
		{
			TraderPlusIDs id = new TraderPlusIDs;
			id = m_TraderPlusIDsSettings.IDs[j];
			int key = m_TraderPlusIDsSettings.IDs[j].Id;
			string data="";
			EnableStockAllCategoryForIDs.Set(key,id.EnableStockAllCategoryForID);
			if(EnableStockAllCategory && id.EnableStockAllCategoryForID)
			{
				data="#tpm_all"+" ";
			}
			for(int k = 0;k<id.Categories.Count();k++)
			{
				data = data + "," + id.Categories.Get(k);
			}
			#ifdef TRADERPLUSDEBUG
			GetTraderPlusLogger().LogInfo("key:"+ key + " data:"+data);
			#endif
			IDsCategories.Set(key,data);
			string licences = "";
			for(int j_i=0;j_i<id.LicencesRequired.Count();j_i++)
			{
				if(j_i==0)licences += id.LicencesRequired.Get(j_i);
				else licences += ","+id.LicencesRequired.Get(j_i);
			}
			#ifdef TRADERPLUSDEBUG
			GetTraderPlusLogger().LogInfo("key:"+ key + " data:"+licences);
			#endif
			Licences.Set(key,licences);

			string currencies = "";
			for(int j_k=0;j_k<id.CurrenciesAccepted.Count();j_k++)
			{
				if(j_k==0)currencies += id.CurrenciesAccepted.Get(j_k);
				else currencies += ","+id.CurrenciesAccepted.Get(j_k);
			}
			#ifdef TRADERPLUSDEBUG
			GetTraderPlusLogger().LogInfo("key:"+ key + " data:"+currencies);
			#endif
			CurrenciesAccepted.Set(key,currencies);
		}

		for(int l=0;l<m_TraderPlusVehiclesSettings.VehiclesParts.Count();l++)
		{
			VehicleNames.Insert(m_TraderPlusVehiclesSettings.VehiclesParts.Get(l).VehicleName);
		}

		TraderPlusJsonLoader<TraderPlusGnrlConfigClient>.SaveToFile(TRADERPLUS_CONFIG_DIR_SERVER + "TransformedGeneralConfig.json", this);
	}
};
