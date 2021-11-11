modded class MissionGameplay extends MissionBase
{
	void MissionGameplay()	{

		m_SZSafeZoneCore = NULL;
		GetSZSafeZoneCore();
	}

	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);

		if ( key == KeyCode.KC_N )
		{
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if(!player)return;

			if (player.ntCanShow == true)
			{
				player.ntCanShow = false;
			}else player.ntCanShow = true;
		}
	}
}
