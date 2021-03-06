class SafeAreaSettings
{
	bool      IsHideOutActive = true;
	bool      EnableNameTag;
	bool      EnableAfkDisconnect;
	int       KickAfterDelay;
	string 		MsgEnterZone;
	string 		MsgExitZone;
	string    MsgOnLeavingZone;
	string    MustRemoveArmband = "You must remove your armband in order to make your stash appear !";
	ref array<ref SafeZoneLocation> SafeAreaLocation;
	int CleanUpTimer;
	ref array<string>ObjectsToDelete;
	ref array<string> SZSteamUIDs;
	ref array<string>BlackListedItemInStash;

	void SafeAreaSettings() {
		SZSteamUIDs =  new array<string>;
		ObjectsToDelete = new array<string>;
		BlackListedItemInStash = new array<string>;
		SafeAreaLocation = new array<ref SafeZoneLocation>;
	}

	void SafeAreaDefaultSettings()	{
		EnableNameTag = true;
		EnableAfkDisconnect = false;
		KickAfterDelay = 30;
    CleanUpTimer = 1200;
		MsgEnterZone="You Have Entered The Safe Zone!";
		MsgExitZone="You Have Left The Safe Zone!";
		MsgOnLeavingZone="You're leaving the safezone in:";
		SafeAreaLocation.Insert(new SafeZoneLocation("Trader", 11595, 14392, 150, 30));
		ObjectsToDelete.Insert("Paper");
		SZSteamUIDs.Insert("76561198047475641");
		BlackListedItemInStash.Insert("Apple");
		JsonFileLoader<SafeAreaSettings>.JsonSaveFile(SZ_CONFIG, this);
	}

	void CheckForUpdate()
	{
		JsonFileLoader<SafeAreaSettings>.JsonSaveFile(SZ_CONFIG, this);
	}

	static ref SafeAreaSettings Load()	{
		SafeAreaSettings settings = new SafeAreaSettings();

		if ( !FileExist( SZ_CONFIG_ROOT_SERVER ) )
		{
			MakeDirectory( SZ_CONFIG_ROOT_SERVER );
			if ( !FileExist( SZ_CONFIG_DIR_SERVER ) )
			{
				MakeDirectory( SZ_CONFIG_DIR_SERVER );
			}
		}

		if (FileExist(SZ_CONFIG)) {
			JsonFileLoader<SafeAreaSettings>.JsonLoadFile(SZ_CONFIG, settings);
			settings.CheckForUpdate();
		}
		else {
			settings.SafeAreaDefaultSettings();
		}

		return settings;
	}
}
