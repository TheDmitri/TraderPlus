class TraderPlusStock
{
	ref array<string>TraderPlusItems;

	void TraderPlusStock()
	{
		TraderPlusItems = new array<string>;
	}

	void DefaultTraderPlusStock(string path)
	{
		JsonFileLoader<TraderPlusStock>.JsonSaveFile(path, this);
	}

	void Save(int id)
	{
		string Path = TRADERPLUS_STOCK_CONFIG + "_" + id.ToString() + ".json";
		JsonFileLoader<TraderPlusStock>.JsonSaveFile(Path, this);
	}

	static ref TraderPlusStock Load(int id)	{
		ref TraderPlusStock settings = new TraderPlusStock;

		string Path = TRADERPLUS_STOCK_CONFIG + "_" + id.ToString() + ".json";

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
		}else
		{
			if ( !FileExist( TRADERPLUS_DB_DIR_SERVER ) )
			{
				MakeDirectory( TRADERPLUS_DB_DIR_SERVER );
			}
			if ( !FileExist( TRADERPLUS_LOGGER_DIR_SERVER ) )
			{
				MakeDirectory( TRADERPLUS_LOGGER_DIR_SERVER );
			}
		}

		if (FileExist(Path)) {
			Print("file exist ! loading...");
			//JsonFileLoader<TraderPlusStock>.JsonLoadFile(Path, settings);
			TraderPlusJsonLoader<TraderPlusStock>.LoadFromFile(Path, settings);
		}
		else {
			Print("file doesn't exist ! creating...");
			settings.DefaultTraderPlusStock(Path);
		}

		return settings;
	}
}
