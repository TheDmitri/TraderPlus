class TraderPlusIDsSettings
{
	ref array<ref TraderPlusIDs>IDs;

	void TraderPlusIDsSettings()
	{
		IDs   = new array<ref TraderPlusIDs>;
	}

	void DefaultTraderPlusIDsSettings()
	{
    IDs.Insert(new TraderPlusIDs(true));
		IDs.Get(0).AddCategoryToId("Vegetables");
		IDs.Get(0).AddCategoryToId("Meats");
		IDs.Insert(new TraderPlusIDs(true));
		IDs.Get(1).AddCategoryToId("Weapons");
		IDs.Get(1).AddCategoryToId("Ammunitions");
		IDs.Get(1).AddCategoryToId("Magazines");
		IDs.Insert(new TraderPlusIDs(true));
		IDs.Get(2).AddCategoryToId("Vehicles");
		IDs.Get(2).AddCategoryToId("Vehicle Parts");
		JsonFileLoader<TraderPlusIDsSettings>.JsonSaveFile(TRADERPLUS_ID_CONFIG, this);
	}

	void AddID()
	{
		IDs.Insert(new TraderPlusIDs(false));
	}

	void AddCategoryToID(int pos, string categoryname)
	{
		IDs.Get(pos).AddCategoryToId(categoryname);
	}

	void Save()
	{
		JsonFileLoader<TraderPlusIDsSettings>.JsonSaveFile(TRADERPLUS_ID_CONFIG, this);
	}

	static ref TraderPlusIDsSettings Load()	{
		TraderPlusIDsSettings settings = new TraderPlusIDsSettings();

		if ( !FileExist( TRADERPLUS_CONFIG_ROOT_SERVER ) )
		{
			MakeDirectory( TRADERPLUS_CONFIG_ROOT_SERVER );
			if ( !FileExist( TRADERPLUS_CONFIG_DIR_SERVER ) )
			{
				MakeDirectory( TRADERPLUS_CONFIG_DIR_SERVER );
			}
			if ( !FileExist( TRADERPLUS_LOGGER_DIR_SERVER ) )
			{
				MakeDirectory( TRADERPLUS_LOGGER_DIR_SERVER );
			}
			if ( !FileExist( TRADERPLUS_DB_DIR_SERVER ) )
			{
				MakeDirectory( TRADERPLUS_DB_DIR_SERVER );
			}
		}
		//Now we check if config exist, if yes, we load it. if no, we call function defaultTraderPlussettings that will initialize default value
		if (FileExist(TRADERPLUS_ID_CONFIG)) {
			GetTraderPlusLogger().LogInfo("TraderPlus file exist ! loading...");
			//JsonFileLoader<TraderPlusIDsSettings>.JsonLoadFile(TRADERPLUS_ID_CONFIG, settings);
			TraderPlusJsonLoader<TraderPlusIDsSettings>.LoadFromFile(TRADERPLUS_ID_CONFIG, settings);
			settings.Save();
		}
		else {
			GetTraderPlusLogger().LogInfo("TraderPlus file doesn't exist ! place a config...");
			//settings.DefaultTraderPlusIDsSettings();
		}

		return settings;
	}
}
