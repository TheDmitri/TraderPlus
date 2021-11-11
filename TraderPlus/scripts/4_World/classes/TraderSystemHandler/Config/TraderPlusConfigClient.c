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
	ref    TStringArray Licences;
	ref 	 array<string>MoneyName;
	ref 	 array<int>MoneyValue;
	ref    array<string>CurrenciesAccepted;
	ref    array<string>IDsCategories;
	ref    array<string>VehicleNames;
	ref    array<vector>TraderPos;
	ref    array<string>GivenNames;
	ref    array<string>Roles;
	ref    array<bool>EnableStockAllCategoryForIDs;

  void TraderPlusGnrlConfigClient()
  {
		Licences        = new TStringArray;
		CurrenciesAccepted= new array<string>;
		MoneyName 			= new array<string>;
		MoneyValue 			= new array<int>;
		IDsCategories 	= new array<string>;
		VehicleNames    = new array<string>;
		GivenNames      = new array<string>;
		Roles           = new array<string>;
		TraderPos       = new array<vector>;
		EnableStockAllCategoryForIDs = new array<bool>;
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
			string data="";
			EnableStockAllCategoryForIDs.Insert(m_TraderPlusIDsSettings.IDs[j].EnableStockAllCategoryForID);
			if(EnableStockAllCategory && m_TraderPlusIDsSettings.IDs[j].EnableStockAllCategoryForID)
			{
				data="#tpm_all"+" " +",";
			}
			for(int k = 0;k<m_TraderPlusIDsSettings.IDs.Get(j).Categories.Count();k++)
			{
				data = data + "," + m_TraderPlusIDsSettings.IDs.Get(j).Categories.Get(k);
			}
			IDsCategories.Insert(data);
			string licences = "";
			for(int j_i=0;j_i<m_TraderPlusIDsSettings.IDs.Get(j).LicencesRequired.Count();j_i++)
			{
				if(j_i==0)licences += m_TraderPlusIDsSettings.IDs.Get(j).LicencesRequired.Get(j_i);
				else licences += ","+m_TraderPlusIDsSettings.IDs.Get(j).LicencesRequired.Get(j_i);
			}
			Licences.Insert(licences);

			string currencies = "";
			for(int j_k=0;j_k<m_TraderPlusIDsSettings.IDs.Get(j).CurrenciesAccepted.Count();j_k++)
			{
				if(j_k==0)currencies += m_TraderPlusIDsSettings.IDs.Get(j).CurrenciesAccepted.Get(j_k);
				else currencies += ","+m_TraderPlusIDsSettings.IDs.Get(j).CurrenciesAccepted.Get(j_k);
			}
			CurrenciesAccepted.Insert(currencies);
		}

		for(int l=0;l<m_TraderPlusVehiclesSettings.VehiclesParts.Count();l++)
		{
			VehicleNames.Insert(m_TraderPlusVehiclesSettings.VehiclesParts.Get(l).VehicleName);
		}
	}
};
