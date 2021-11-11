class VehiculeData
{
	string 	VehicleName;
	int     VehicleID;
	float 	EngineHealth;
	float 	FuelAmmount;
	ref array<ref ItemsCargo> ItemsInCargo;

	void VehiculeData(string name, int vdata,float enginehealth, float fuelamount,array<ref ItemsCargo>cargos)
	{
		#ifdef GMDEBUG
		GetGMLogger().LogInfo("new VehiculeData");
		#endif
		VehicleName = name;
		VehicleID  = vdata;
		EngineHealth = enginehealth;
		FuelAmmount = fuelamount;
		ItemsInCargo = new array<ref ItemsCargo>;
    ItemsInCargo = cargos;
	}
}

class ItemsCargo
{
	string ItemName;
	int    Amount;
  float  Health;
	int    ExtraData;

	void ItemsCargo(string name, int amount, float health, int extradata = 0)
	{
		ItemName  = name;
		Amount 	  = amount;
    Health    = health;
		ExtraData = extradata;
	}
}

class GarageData
{
	//Define your configs variables there
	string 		OwnerName;
	string  	OwnerID;
	vector    ParkingPosition = Vector(-1,-1,-1);
	vector    ParkingOrientation = Vector(-1,-1,-1);
	ref       array<ref VehiculeData>Vehicles;

	void GarageData()
	{
		Vehicles = new array<ref VehiculeData>;
	}

	void DefaultGarageData(string path, string steamid, string name)	{
		OwnerName = name;
		OwnerID = steamid;
		//then it saves the file
		JsonFileLoader<GarageData>.JsonSaveFile(path, this);
	}

	void AddVehicle(string name, int data, float engineh, float fuela, array<ref ItemsCargo>itemsincargo)
	{
		Vehicles.Insert(new VehiculeData(name, data, engineh, fuela, itemsincargo));
	}

	void Save(string id)
	{
		string path = GM_DATABASE + id + ".json";
		JsonFileLoader<GarageData>.JsonSaveFile(path, this);
	}

	void DeleteIt(string id)
	{
		string path = GM_DATABASE + id + ".json";
		bool attempt = DeleteFile(path);
	}

	static ref GarageData Load(string id, string name)	{
		GarageData Data = new GarageData();

		//we check if config folders exist, if not we create them
		if ( !FileExist( GM_DB_DIR_SERVER ) )
		{
			MakeDirectory( GM_DB_DIR_SERVER );
		}

		string path = GM_DATABASE + id + ".json";
		//Now we check if config exist, if yes, we load it. if no, we call function defaultTraderPlusBankingData that will initialize default value
		if (FileExist(path)) {
			//Print("file exist ! loading...");
			TraderPlusJsonLoader<GarageData>.LoadFromFile(path, Data);
			//JsonFileLoader<GarageData>.JsonLoadFile(path, Data);
			Data.Save(id);
		}
		else {
			//Print("file doesn't exist ! creating...");
			Data.DefaultGarageData(path,id,name);
		}
		return Data;
	}
}
