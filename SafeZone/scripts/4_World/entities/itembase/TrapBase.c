modded class TrapBase
{
    override void StartActivate( PlayerBase player )
	   {
        if (player)
        {
            if (player.GetSafeZoneStatus() == SZ_IN_SAFEZONE)
               return;
        }
        super.StartActivate(player);
	}
}
