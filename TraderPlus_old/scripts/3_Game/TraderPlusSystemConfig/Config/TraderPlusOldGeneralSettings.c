class TraderPlusOldGeneralSettings
{
	bool                                   ConvertTraderConfigToTraderPlus;
	string                                 TraderUIText;
	bool                                   EnableShowAllCheckBox;
	bool                                   EnableStockAllCategory;
	int   																 MaxItemsStockPerId;
	int                                    MaxPlayerPerID;
	bool                                   IsReceiptTraderOnly;
	float                                  LockPickChance;
	int                                    UITimer;
	string                                 LicenceKeyWord;
	ref TStringArray                       Licences;
	ref TraderPlusStates									 AcceptedStates;
	bool                                   StoreOnlyToPristineState;
	ref array<ref TraderPlusCurrency>			 Currencies;
	ref array<ref TraderPlusData>					 Traders;
	ref array<ref TraderPlusObject>				 TraderObjects;

	void TraderPlusOldGeneralSettings()
	{
		Currencies 						= new array<ref TraderPlusCurrency>;
		Licences         			= new TStringArray;
		Traders 							= new array<ref TraderPlusData>;
		TraderObjects 				= new array<ref TraderPlusObject>;
	}

	void ConvertToNewConfig()
	{
		TraderPlusGeneralSettings m_gnrlconfig = new TraderPlusGeneralSettings;
		m_gnrlconfig.ConvertTraderConfigToTraderPlus = ConvertTraderConfigToTraderPlus;
		m_gnrlconfig.EnableShowAllCheckBox = EnableShowAllCheckBox;
		m_gnrlconfig.EnableStockAllCategory = EnableStockAllCategory;
		m_gnrlconfig.IsReceiptTraderOnly = IsReceiptTraderOnly;
		m_gnrlconfig.LockPickChance = LockPickChance;
		m_gnrlconfig.LicenceKeyWord = LicenceKeyWord;
		m_gnrlconfig.Licences = Licences;
		m_gnrlconfig.AcceptedStates = AcceptedStates;
		m_gnrlconfig.StoreOnlyToPristineState = StoreOnlyToPristineState;
		m_gnrlconfig.Currencies = Currencies;
		m_gnrlconfig.Traders = Traders;
		m_gnrlconfig.TraderObjects = TraderObjects;
		JsonFileLoader<TraderPlusGeneralSettings>.JsonSaveFile(TRADERPLUS_CONFIG, m_gnrlconfig);
	}

	static ref TraderPlusOldGeneralSettings Load()	{
		TraderPlusOldGeneralSettings settings = new TraderPlusOldGeneralSettings();
		//Now we check if config exist, if yes, we load it. if no, we call function defaultTraderPlussettings that will initialize default value
		if (FileExist(TRADERPLUS_CONFIG)) {
			GetTraderPlusLogger().LogInfo("TraderPlus file exist ! loading...");
			TraderPlusJsonLoader<TraderPlusOldGeneralSettings>.LoadFromFile(TRADERPLUS_CONFIG, settings);
			settings.ConvertToNewConfig();
		}
		return settings;
	}
}
