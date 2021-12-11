class SZSafeZoneCore
{
  ref SafeAreaSettings m_ActiveSafeAreaSettings;
	ref SafeZoneLocations m_SafeZoneLocations;

	ref SZSafeZoneClient m_SZSafeZoneClient;
	ref SZSafeZoneServer m_SZSafeZoneServer;

	void SZSafeZoneCore()
  	{
    		if (GetGame().IsServer())
    		{
            GetTraderPlusLogger().LogInfo("SafeZoneCore - Started !");
            m_ActiveSafeAreaSettings = SafeAreaSettings.Load();
            m_SafeZoneLocations = new SafeZoneLocations(m_ActiveSafeAreaSettings);

            m_SZSafeZoneServer = new SZSafeZoneServer;

      			#ifdef SZDEBUG
      		  GetTraderPlusLogger().LogInfo("DEBUG MODE ENABLED");
      			#endif
    		}
    		else
    		{
            m_SZSafeZoneClient = new SZSafeZoneClient;
    		}
        InitRPC();
  }

	void InitRPC()
		{
			if (GetGame().IsServer())	{
				//Server calls
				GetRPCManager().AddRPC("SZSafeZone", "GetSafeStatut", m_SZSafeZoneServer, SingeplayerExecutionType.Client);
        GetRPCManager().AddRPC("SZSafeZone", "GetEntitiesCleanUp", m_SZSafeZoneServer, SingeplayerExecutionType.Client);
        GetRPCManager().AddRPC("SZSafeZone", "GetFlagStatus", m_SZSafeZoneServer, SingeplayerExecutionType.Client);
      }
			else	{
				//Client calls
        GetRPCManager().AddRPC("SZSafeZone", "GetConfigResponse", m_SZSafeZoneClient, SingeplayerExecutionType.Server);
			}
		}

	void ~SZSafeZoneCore()
    {

    }

    void SendConfigToPlayer(PlayerIdentity idy)
    {
      if(m_SafeZoneLocations)
      {
        GetRPCManager().SendRPC("SZSafeZone", "GetConfigResponse", new Param1<ref SafeZoneLocations>(m_SafeZoneLocations), true, idy);
      }
    }

}
