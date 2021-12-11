class TraderPlusCore
{
	//ref TraderPlusOldGeneralSettings  m_oldconfig;
	ref TraderPlusGeneralSettings     m_TraderPlusGeneralSettings;
	ref TraderPlusVehiclesSettings    m_TraderPlusVehiclesSettings;
	ref TraderPlusPriceSettings    		m_TraderPlusPriceSettings;
	ref TraderPlusIDsSettings					m_TraderPlusIDsSettings;

	ref TraderPlusGnrlConfigClient    m_TraderPlusGnrlConfigClient;

	ref TraderPlusCategories m_TraderPlusCategories;

  ref TraderPlusClient m_TraderPlusClient;
  ref TraderPlusServer m_TraderPlusServer;

	void TraderPlusCore()
  {
		GetTraderPlusLogger().LogInfo("TraderPlusCore - Started !");
		#ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("DEBUG MODE ENABLED");
		#endif

		/*We load every config, class that will run on server side here*/
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			//LOADING CONFIG FILES...
			m_TraderPlusGeneralSettings = TraderPlusGeneralSettings.Load();
			m_TraderPlusVehiclesSettings = TraderPlusVehiclesSettings.Load();
			m_TraderPlusPriceSettings   = TraderPlusPriceSettings.Load();
			m_TraderPlusIDsSettings = m_TraderPlusIDsSettings.Load();

			m_TraderPlusCategories = new TraderPlusCategories;
			m_TraderPlusCategories.ConvertArrayCategoryToMap();

			m_TraderPlusGnrlConfigClient = new TraderPlusGnrlConfigClient;
			m_TraderPlusGnrlConfigClient.TransformToSendableConfig(m_TraderPlusGeneralSettings,m_TraderPlusIDsSettings,m_TraderPlusVehiclesSettings);
			//Creating server side part
			m_TraderPlusServer = new TraderPlusServer;
		}
		else
		{
			/*Then we run every config and class that will run on client only*/
			m_TraderPlusClient = new TraderPlusClient;
			m_TraderPlusGnrlConfigClient = new TraderPlusGnrlConfigClient;
		}
		//we call our function that will initiaze our RPC
		InitRPC();
  }

	void ~TraderPlusCore(){
  }

	void InitRPC()
		{
			if (GetGame().IsServer())
			{
				//Server calls
				//GetRPCManager().AddRPC("ModName (try to be as specific as you can)", "NameOfYourRPCFunction", function where the RPC will be called, SingeplayerExecutionType.Client (Client when you do client to server));
				GetRPCManager().AddRPC("TraderPlus", "GetTradeRequest", m_TraderPlusServer, SingeplayerExecutionType.Client);
				GetRPCManager().AddRPC("TraderPlus", "GetStockRequestBasedOnID", m_TraderPlusServer, SingeplayerExecutionType.Client);
			}
			else
			{
				//Client calls
				//GetRPCManager().AddRPC("ModName (try to be as specific as you can)", "NameOfYourRPCFunction", function where the RPC will be called, SingeplayerExecutionType.Server (Server when you do Server to Client));
			  GetRPCManager().AddRPC("TraderPlus", "GetStockResponseBasedOnID", m_TraderPlusClient, SingeplayerExecutionType.Server);
				GetRPCManager().AddRPC("TraderPlus", "GetTraderPlusGnrlConfigClient", this, SingeplayerExecutionType.Server);
				GetRPCManager().AddRPC("TraderPlus", "GetPriceRequestFromCategory", m_TraderPlusClient, SingeplayerExecutionType.Server);
			}
		}

		//Here we send gnrl config and price config to client
		void TransfertTraderPlusConfigToClient(PlayerBase player)
		{
				/*we create a temporary config class that we will send to client with RPC*/
				GetRPCManager().SendRPC("TraderPlus", "GetTraderPlusGnrlConfigClient",  new Param1<ref TraderPlusGnrlConfigClient>(m_TraderPlusGnrlConfigClient), true, player.GetIdentity());
				GetRPCManager().SendRPC("TraderPlus", "GetPriceRequestFromCategory",  new Param1<ref TraderPlusCategories>(m_TraderPlusCategories), true, player.GetIdentity());
		}


		//-------------------------------------------RPC PART--------------------------------------------------------//
		void GetTraderPlusGnrlConfigClient(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
		{
			if(!GetGame().IsClient())return;

			Param1<ref TraderPlusGnrlConfigClient> data;
	     if (!ctx.Read(data))
	       return;

			m_TraderPlusGnrlConfigClient = data.param1;
			#ifdef TRADERPLUSDEBUG
			JsonFileLoader<ref TraderPlusGnrlConfigClient>.JsonSaveFile(TRADERPLUS_CONFIG, m_TraderPlusGnrlConfigClient);
			#endif
			//we reset the price config before next RPC fills it
			m_TraderPlusClient.ResetPriceConfig();
		}
	};
