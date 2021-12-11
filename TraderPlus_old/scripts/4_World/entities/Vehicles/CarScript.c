modded class CarScript
{
    string m_TraderPlus_LastDriverID = "";

    void CarScript()
	   {
        SetAllowDamage(false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DisableGodMode, 30000);
	   }

     override void OnEngineStart()
 	   {
         super.OnEngineStart();
         PlayerBase player = PlayerBase.Cast(CrewMember(DayZPlayerConstants.VEHICLESEAT_DRIVER));
         if (player)
             m_TraderPlus_LastDriverID = player.GetIdentity().GetPlainId();
 	   }

     void DisableGodMode()
     {
        SetAllowDamage(true);
     }
}
