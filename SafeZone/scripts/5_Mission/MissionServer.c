modded class MissionServer extends MissionBase
{
	void MissionServer() {
		m_SZSafeZoneCore = NULL;
		GetSZSafeZoneCore();
	}

	override void OnInit()
	{
		super.OnInit();
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player,identity);
		InitSafeZoneConfig(player,identity);
	}

	void InitSafeZoneConfig(PlayerBase player, PlayerIdentity identity)
	{
		GetSZSafeZoneCore().SendConfigToPlayer(identity);
		GetSZSafeZoneCore().m_SZSafeZoneServer.CheckIfInsideSafeZone(player);
		if(SZIsAdmin(player))
		{
			player.SetAdminStatus();
		}
	}
}
