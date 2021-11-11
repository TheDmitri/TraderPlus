
class TraderPlusBankingData
{
	//Define your configs variables there
	string  	Name;
	int 			MoneyAmount;
	int   		MaxAmount;
	ref       TStringArray Licences;

	void TraderPlusBankingData()
	{

	}

	void DefaultTraderPlusBankingData(string path, int defaultMaxCurrency, int defaultStartCurrency,string name)
	{
		Name = name;
		MoneyAmount = defaultStartCurrency;
		MaxAmount = defaultMaxCurrency;
		Licences = new TStringArray;
		//then it saves the file
		JsonFileLoader<TraderPlusBankingData>.JsonSaveFile(path, this);
	}

	void Save(string id)
	{
		string path = TPB_DB + id + ".json";
		JsonFileLoader<TraderPlusBankingData>.JsonSaveFile(path, this);
	}

	static ref TraderPlusBankingData Load(string id, int defaultMaxCurrency,int defaultStartCurrency, string name)	{
		TraderPlusBankingData Data = new TraderPlusBankingData();

		//we check if config folders exist, if not we create them
		if ( !FileExist( TPB_CONFIG_DIR ) )
		{
			MakeDirectory( TPB_CONFIG_DIR );
		}

		string path = TPB_DB + id + ".json";
		//Now we check if config exist, if yes, we load it. if no, we call function defaultTraderPlusBankingData that will initialize default value
		if (FileExist(path)) {
			//Print("file exist ! loading...");
			#ifdef TRADERPLUSDEBUG
			GetTraderPlusLogger().LogInfo("BankingData file exist ! loading..."); //sender.GetName() = player.GetIdentity().GetName()
			#endif
			//TraderPlusJsonLoader<TraderPlusBankingData>.LoadFromFile(path, Data);
			JsonFileLoader<TraderPlusBankingData>.JsonLoadFile(path, Data);
			Data.Save(id);
		}
		else {
			//Print("file doesn't exist ! creating...");
			#ifdef TRADERPLUSDEBUG
			GetTraderPlusLogger().LogInfo("BankingData doesn't exist ! creating..."); //sender.GetName() = player.GetIdentity().GetName()
			#endif
			Data.DefaultTraderPlusBankingData(path,defaultMaxCurrency,defaultStartCurrency,name);
		}
		return Data;
	}
}
