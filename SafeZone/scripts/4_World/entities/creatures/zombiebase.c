modded class ZombieBase extends DayZInfected
{
	override bool ChaseAttackLogic(int pCurrentCommandID, DayZInfectedInputController pInputController, float pDt)
	{

    PlayerBase m_player = PlayerBase.Cast(m_ActualTarget);
    if(m_player && m_player.IsInsideSZ.SZStatut == true)
    {
      //Print("IsInsideSZ_ZombyDELETED");
      this.Delete();
      return false;
    }

    return super.ChaseAttackLogic(pCurrentCommandID,pInputController,pDt);
	}

	override bool FightAttackLogic(int pCurrentCommandID, DayZInfectedInputController pInputController, float pDt)
	{
    PlayerBase m_player = PlayerBase.Cast(m_ActualTarget);
    if(m_player && m_player.IsInsideSZ.SZStatut == true)
    {
      //Print("IsInsideSZ_ZombyDELETED");
      this.Delete();
      return false;
    }

		return super.FightAttackLogic(pCurrentCommandID,pInputController,pDt);
	}
}
