class TraderPlusPriceSettings
{
	bool EnableAutoCalculation;
	bool EnableAutoDestockAtRestart;
	int EnableDefaultTraderStock;
	ref array<ref TraderPlusCategory>TraderCategories;

	void TraderPlusPriceSettings()
	{
		TraderCategories = new array<ref TraderPlusCategory>;
	}

	void DefaultTraderPlusPriceSettings()
	{
		EnableAutoCalculation = false;
		EnableAutoDestockAtRestart = false;
		EnableDefaultTraderStock = 0;
		TraderCategories.Insert(new  TraderPlusCategory("Vegetables"));
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Apple,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("GreenBellPepper,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Pear,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Plum,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Kiwi,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Orange,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Banana,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Potato,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Tomato,-1,-1,-1,0,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Zucchini,-1,-1,-1,3,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("Pumpkin,-1,-1,-1,3,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("CaninaBerry,-1,-1,-1,1,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("SambucusBerry,-1,-1,-1,1,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("AgaricusMushroom,-1,-1,-1,2,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("AmanitaMushroom,-1,-1,-1,2,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("LactariusMushroom,-1,-1,-1,2,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("MacrolepiotaMushroom,-1,-1,-1,2,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("PsilocybeMushroom,-1,-1,-1,2,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("AuriculariaMushroom,-1,-1,-1,2,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("BoletusMushroom,-1,-1,-1,2,1");
		TraderCategories.Get(0).AddProductToTraderPlusCategory("PleurotusMushroom,-1,-1,-1,2,1");
		TraderCategories.Insert(new  TraderPlusCategory("Weapons"));
		TraderCategories.Get(1).AddProductToTraderPlusCategory("Izh18,-1,200,1,350,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("Mosin9130,-1,200,1,400,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("CZ527,-1,100,1,250,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("Winchester70,-1,50,1,500,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("SKS,-1,50,1,600,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("MakarovIJ70,-1,200,1,100,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("CZ75,-1,200,1,135,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("FNX45,-1,200,1,150,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("Mp133Shotgun,-1,200,1,500,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("CZ61,-1,200,1,700,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("UMP45,-1,200,1,1000,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("MP5K,-1,200,1,800,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("FAL,-1,200,1,1500,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("AKM,-1,200,1,1300,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("M4A1,-1,200,1,1350,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("VSS,-1,200,1,1600,0.8");
		TraderCategories.Get(1).AddProductToTraderPlusCategory("SVD,-1,200,1,2000,0.8");
		TraderCategories.Insert(new  TraderPlusCategory("Ammunitions"));
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_380,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_9x19,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_45ACP,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_12gaPellets,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_12gaSlug,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_9x39,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_556x45,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_762x39,0.998,1000,1,10,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_762x54,0.998,1000,1,10,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("Ammo_308Win,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_380_35rnd,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_9x19_25rnd,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_45ACP_25rnd,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_00buck_10rnd,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_12gaSlug_10Rnd,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_9x39_20Rnd,0.998,1000,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_9x39AP_20Rnd,0.998,500,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_556x45_20Rnd,0.998,500,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_762x39_20Rnd,0.998,500,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_762x54_20Rnd,0.998,500,1,5,0.6");
		TraderCategories.Get(2).AddProductToTraderPlusCategory("AmmoBox_308Win_20Rnd,0.998,500,1,80,0.8");
		TraderCategories.Insert(new  TraderPlusCategory("Meats"));
		TraderCategories.Get(3).AddProductToTraderPlusCategory("Bone,-1,-1,75,2,1");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("Guts,-1,-1,75,2,1");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("SmallGuts,-1,-1,75,2,1");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("Lard,-1,-1,-1,2,1");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("ChickenBreastMeat,-1,-1,75,2,1");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("GoatSteakMeat,-1,-1,75,3,1");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("SheepSteakMeat,-1,-1,75,3,2");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("BoarSteakMeat,-1,-1,75,4,2");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("WolfSteakMeat,-1,-1,75,5,3");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("DeerSteakMeat,-1,-1,75,4,2");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("CowSteakMeat,-1,-1,75,4,2");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("Sardines,-1,-1,75,7,4");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("Carp,-1,-1,75,10,5");
		TraderCategories.Get(3).AddProductToTraderPlusCategory("Mackerel,-1,-1,75,10,5");
		TraderCategories.Insert(new  TraderPlusCategory("Magazines"));
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_IJ70_8Rnd,0.99,300,0,30,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_CZ75_15Rnd,0.99,300,0,40,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_FNX45_15Rnd,0.99,300,0,40,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_CZ527_5rnd,0.99,300,0,60,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_CZ61_20Rnd,0.99,300,0,100,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_UMP_25Rnd,0.99,200,0,150,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_MP5_30Rnd,0.99,200,0,100,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_FAL_20Rnd,0.99,100,0,150,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_AKM_30Rnd,0.99,150,0,220,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_STANAG_30Rnd,0.99,150,0,220,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_VSS_10Rnd,0.99,1000,0,250,0.8");
		TraderCategories.Get(4).AddProductToTraderPlusCategory("Mag_SVD_10Rnd,0.99,500,0,250,0.8");
		TraderCategories.Insert(new  TraderPlusCategory("Vehicles"));
		TraderCategories.Get(5).AddProductToTraderPlusCategory("OffroadHatchback,-1,20,1,8000,0.8");
		TraderCategories.Get(5).AddProductToTraderPlusCategory("Hatchback_02,-1,20,1,9600,0.8");
		TraderCategories.Get(5).AddProductToTraderPlusCategory("CivilianSedan,-1,20,1,11000,0.8");
		TraderCategories.Insert(new  TraderPlusCategory("Vehicle Parts"));
		TraderCategories.Get(6).AddProductToTraderPlusCategory("HeadlightH7_Box,-1,60,1,30,0.8");
		TraderCategories.Get(6).AddProductToTraderPlusCategory("SparkPlug,-1,60,1,60,0.8");
		TraderCategories.Get(6).AddProductToTraderPlusCategory("CarBattery,-1,60,1,100,0.8");
		TraderCategories.Get(6).AddProductToTraderPlusCategory("CarRadiator,-1,60,1,100,0.8");
		TraderCategories.Get(6).AddProductToTraderPlusCategory("TireRepairKit,-1,60,1,150,0.8");
		TraderCategories.Insert(new  TraderPlusCategory("Drinks"));
		TraderCategories.Get(7).AddProductToTraderPlusCategory("SodaCan_Cola,-1,-1,-1,2,1");
		TraderCategories.Get(7).AddProductToTraderPlusCategory("SodaCan_Kvass,-1,-1,-1,2,1");
		TraderCategories.Get(7).AddProductToTraderPlusCategory("SodaCan_Pipsi,-1,-1,-1,2,1");
		TraderCategories.Get(7).AddProductToTraderPlusCategory("SodaCan_Spite,-1,-1,-1,2,1");
		TraderCategories.Get(7).AddProductToTraderPlusCategory("WaterBottle,-1,-1,-1,2,1");
		TraderCategories.Get(7).AddProductToTraderPlusCategory("Canteen,-1,-1,-1,2,1");
		TraderCategories.Get(7).AddProductToTraderPlusCategory("Vodka,-1,-1,-1,12,8");
		TraderCategories.Insert(new  TraderPlusCategory("Medical Supplies"));
		TraderCategories.Get(8).AddProductToTraderPlusCategory("BandageDressing,-1,-1,-1,3,1");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("BloodTestKit,-1,-1,-1,5,2");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("Thermometer,-1,-1,-1,5,2");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("DisinfectantSpray,-1,-1,-1,5,2");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("Heatpack,-1,-1,-1,18,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("StartKitIV,-1,-1,-1,10,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("SalineBag,-1,-1,-1,15,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("BloodBagEmpty,-1,-1,-1,18,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("FirstAidKit,-1,-1,-1,20,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("CharcoalTablets,-1,-1,-1,5,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("DisinfectantAlcohol,-1,-1,-1,5,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("VitaminBottle,-1,-1,-1,5,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("TetracyclineAntibiotics,-1,-1,-1,10,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("PainkillerTablets,-1,-1,-1,10,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("Epinephrine,-1,-1,-1,15,0.8");
		TraderCategories.Get(8).AddProductToTraderPlusCategory("Morphine,-1,-1,-1,15,0.8");
		TraderCategories.Insert(new  TraderPlusCategory("Tools"));
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Screwdriver,-1,-1,-1,3,1");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Wrench,-1,-1,-1,3,1");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("SewingKit,-1,-1,-1,4,1");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Pliers,-1,-1,-1,4,1");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("LeatherSewingKit,-1,-1,-1,5,2");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Whetstone,-1,-1,-1,5,2");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Hammer,-1,-1,-1,7,3");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Hacksaw,-1,-1,-1,7,3");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("HandSaw,-1,-1,-1,7,3");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("WeaponCleaningKit,-1,-1,-1,9,3");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("KitchenKnife,-1,-1,-1,9,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("SteakKnife,-1,-1,-1,9,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("HandSaw,-1,-1,-1,7,3");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("WeaponCleaningKit,-1,-1,-1,9,3");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("KitchenKnife,-1,-1,-1,9,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("SteakKnife,-1,-1,-1,9,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("HuntingKnife,-1,-1,-1,9,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("CanOpener,-1,-1,-1,10,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Compass,-1,-1,-1,10,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("OrienteeringCompass,-1,-1,-1,10,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Hatchet,-1,-1,-1,10,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Machete,-1,-1,-1,12,6");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("ChernarusMap,-1,-1,-1,15,5");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Lockpick,-1,-1,-1,20,10");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Binoculars,-1,-1,-1,30,15");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("FishingRod,-1,-1,-1,60,25");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("LugWrench,-1,-1,-1,4,1");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Crowbar,-1,-1,-1,5,3");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Shovel,-1,-1,-1,6,3");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("Pickaxe,-1,-1,-1,10,4");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("SledgeHammer,-1,-1,-1,12,6");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("PipeWrench,-1,-1,-1,15,7");
		TraderCategories.Get(9).AddProductToTraderPlusCategory("FiighterAxe,-1,-1,-1,30,12");
		TraderCategories.Insert(new  TraderPlusCategory("Electronics"));
		TraderCategories.Get(10).AddProductToTraderPlusCategory("Battery9V,-1,-1,-1,8,3");
		TraderCategories.Get(10).AddProductToTraderPlusCategory("PersonalRadio,-1,-1,-1,10,5");
		TraderCategories.Get(10).AddProductToTraderPlusCategory("Megaphone,-1,-1,-1,30,15");
		TraderCategories.Get(10).AddProductToTraderPlusCategory("ElectronicRepairKit,-1,-1,-1,35,17");
		TraderCategories.Get(10).AddProductToTraderPlusCategory("CableReel,-1,-1,-1,40,20");
		TraderCategories.Get(10).AddProductToTraderPlusCategory("BatteryCharger,-1,-1,-1,40,20");
		TraderCategories.Get(10).AddProductToTraderPlusCategory("BaseRadio,-1,-1,-1,50,30");
		TraderCategories.Get(10).AddProductToTraderPlusCategory("Rangefinder,-1,-1,-1,60,35");
		TraderCategories.Get(10).AddProductToTraderPlusCategory("NVGoggles,-1,-1,-1,400,220");
		TraderCategories.Insert(new  TraderPlusCategory("Fire & Lights"));
		TraderCategories.Get(11).AddProductToTraderPlusCategory("Chemlight_Blue,-1,-1,-1,2,1");
		TraderCategories.Get(11).AddProductToTraderPlusCategory("Chemlight_Green,-1,-1,-1,2,1");
		TraderCategories.Get(11).AddProductToTraderPlusCategory("Chemlight_Red,-1,-1,-1,2,1");
		TraderCategories.Get(11).AddProductToTraderPlusCategory("Chemlight_White,-1,-1-1,2,1");
		JsonFileLoader<TraderPlusPriceSettings>.JsonSaveFile(TRADERPLUS_PRICE_CONFIG, this);
	}

	void AddCategoryToConfig(string name)
	{
		TraderCategories.Insert(new  TraderPlusCategory(name));
	}

	void AddCategoryToConfigClient( TraderPlusCategory category)
	{
		TraderCategories.Insert(category);
	}

	void AddProductToCategory(int pos, string data)
	{
		TraderCategories.Get(pos).AddProductToTraderPlusCategory(data);
	}

	void Save()
	{
		JsonFileLoader<TraderPlusPriceSettings>.JsonSaveFile(TRADERPLUS_PRICE_CONFIG, this);
	}

	void CheckForSpacesToRemove()
	{
		GetTraderPlusLogger().LogInfo("CheckForSpacesToRemove - Started");
		for(int i=0; i<TraderCategories.Count();i++)
		{
			for(int j=0; j<TraderCategories.Get(i).Products.Count();j++)
			{
				string line = TraderCategories.Get(i).Products.Get(j);
				line = TraderPlusTrimSpaces(line);
				TraderCategories.Get(i).Products.Set(j, line);
			}
		}
		GetTraderPlusLogger().LogInfo("CheckForSpacesToRemove - Ended");
	}

	static ref TraderPlusPriceSettings Load()	{
		ref TraderPlusPriceSettings settings = new TraderPlusPriceSettings();

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
		}
		//Now we check if config exist, if yes, we load it. if no, we call function defaultTraderPlussettings that will initialize default value
		if (FileExist(TRADERPLUS_PRICE_CONFIG)) {
			GetTraderPlusLogger().LogInfo("TraderPlus file exist ! loading...");
			//JsonFileLoader<TraderPlusPriceSettings>.JsonLoadFile(path, settings);
			TraderPlusJsonLoader<TraderPlusPriceSettings>.LoadFromFile(TRADERPLUS_PRICE_CONFIG, settings);
			settings.Save();
			settings.CheckForSpacesToRemove();
			JsonFileLoader<TraderPlusPriceSettings>.JsonSaveFile(TRADERPLUS_PRICE_CONFIG, settings);
		}
		else {
			GetTraderPlusLogger().LogInfo("TraderPlus file doesn't exist ! creating...");
			//settings.DefaultTraderPlusPriceSettings();
		}

		return settings;
	}
}
