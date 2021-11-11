modded class DayZPlayerMeleeFightLogic_LightHeavy
{
    override bool HandleFightLogic(int pCurrentCommandID, HumanInputController pInputs, EntityAI pEntityInHands, HumanMovementState pMovementState, out bool pContinueAttack)
	  {
        PlayerBase playerSZClone = PlayerBase.Cast(m_DZPlayer);

        if (playerSZClone)
        {
            if(GetGame().IsServer())
            {
              if (playerSZClone.IsInsideSZ.SZStatut)
              return false;
            }
            else
            {
              if (GetSafeZoneStatut())
              return false;
            }
        }

        return super.HandleFightLogic(pCurrentCommandID, pInputs, pEntityInHands, pMovementState, pContinueAttack);
    }
}
