modded class TrapBase
{
    override void StartActivate( PlayerBase player )
	   {
        if (player)
        {
            if (player.IsInsideSZ.SZStatut == true)
               return;
        }
        super.StartActivate(player);
	}
}
