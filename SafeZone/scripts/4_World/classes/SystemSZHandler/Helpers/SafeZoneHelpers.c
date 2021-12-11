static ref SafeZoneLocations GetSZConfigClient()	{
	return GetSZSafeZoneCore().m_SZSafeZoneClient.m_SafeZoneLocations;
}

static bool GetSafeZoneStatut()	{
	return GetSZSafeZoneCore().m_SZSafeZoneClient.SZStatut;
}

static ref SafeAreaSettings GetSZConfig()	{
	return GetSZSafeZoneCore().m_ActiveSafeAreaSettings;
}

static ref SZSafeZoneClient GetSafeZoneClient(){
	return GetSZSafeZoneCore().m_SZSafeZoneClient;
}

static ref SZSafeZoneCore m_SZSafeZoneCore;
static SZSafeZoneCore GetSZSafeZoneCore() {
	if ( !m_SZSafeZoneCore ) {
		m_SZSafeZoneCore= new SZSafeZoneCore;
	}
	return m_SZSafeZoneCore;
}

	static bool SZIsAdmin(PlayerBase pl)
	{
		//Steam 64 UID
		string sZUID = pl.GetIdentity().GetPlainId();
		int cpt= -1 + GetSZConfig().SZSteamUIDs.Count();
		for(int i=0;i<=cpt;i++)
		{
			if (sZUID == GetSZConfig().SZSteamUIDs.Get(i))
			{
				return true;
			}
		}
		return false;
	}
