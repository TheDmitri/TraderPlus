
class TraderPlusBankingSettings
{
	//Define your configs variables there
	bool  IsCreditCarNeededForTransaction;
	float TransactionFees;
	int   DefaultStartCurrency;
	int   DefaultMaxCurrency;
	string TextUI;
	ref    TStringArray CurrenciesAccepted;

	void TraderPlusBankingSettings()
	{
		CurrenciesAccepted = new TStringArray;
	}

	void DefaultTraderPlusBankingSettings()
	{
		IsCreditCarNeededForTransaction = false;
		TransactionFees = 0.05;
		DefaultStartCurrency = 0;
		DefaultMaxCurrency = 1000000;
		TextUI="BANK AMOUNT:,Fees:,PLAYER AMOUNT:,MAX:,WITHDRAW,DEPOSIT,PLAYER ACCOUNT,NUMBER ONLY !,YOU CANNOT PUT NEGATIVE OR NULL VALUE!,AMOUNT DESIRED IS SUPERIOR TO BANK AMOUNT!,AMOUNT IS GOING TO REACH BANK AMOUNT LIMIT!,NOT ENOUGH MONEY!,TRANSACTION AMOUNT:";
		//then it saves the file
		JsonFileLoader<TraderPlusBankingSettings>.JsonSaveFile(TPB_CONFIG, this);
	}

	void CheckUpdate()
	{
		bool save = false;
		if(!DefaultStartCurrency || DefaultStartCurrency == 0)
		{
			DefaultStartCurrency = 0;
			save = true;
		}
		if(save)JsonFileLoader<TraderPlusBankingSettings>.JsonSaveFile(TPB_CONFIG, this);
	}

	static ref TraderPlusBankingSettings Load()	{
		TraderPlusBankingSettings settings = new TraderPlusBankingSettings();

		//we check if config folders exist, if not we create them
		if ( !FileExist( TPB_CONFIG_DIR ) )
		{
			MakeDirectory( TPB_CONFIG_DIR );
		}

		//Now we check if config exist, if yes, we load it. if no, we call function defaultTraderPlusBankingsettings that will initialize default value
		if (FileExist(TPB_CONFIG)) {
			#ifdef TRADERPLUSDEBUG
      GetTraderPlusLogger().LogInfo("BankingSettings file exist ! loading..."); //sender.GetName() = player.GetIdentity().GetName()
      #endif
			TraderPlusJsonLoader<TraderPlusBankingSettings>.LoadFromFile(TPB_CONFIG, settings);
			JsonFileLoader<TraderPlusBankingSettings>.JsonSaveFile(TPB_CONFIG, settings);
			//settings.CheckUpdate();
			//JsonFileLoader<TraderPlusBankingSettings>.JsonLoadFile(TPB_CONFIG, settings);
		}
		else {
			#ifdef TRADERPLUSDEBUG
      GetTraderPlusLogger().LogInfo("BankingSettings doesn't exist ! creating..."); //sender.GetName() = player.GetIdentity().GetName()
      #endif
			settings.DefaultTraderPlusBankingSettings();
		}

		return settings;
	}
}
