#ifndef CARLOCKDISABLE
modded class MissionGameplay extends MissionBase
{
	void MissionGameplay()
	{
		/*we create the core function on client in order to have the client side working*/
		m_CarLockCore = NULL;
		GetCarLockCore();
	}

	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if ( key == KeyCode.KC_ESCAPE )
		{
			if (player && player.m_CarLockMenu)
				player.m_CarLockMenu.OnHide();
		}

		if ( key == KeyCode.KC_U )
		{
			CarScript car;
			//! player inside vehicle
			if ( player && player.GetCommand_Vehicle() )
			{
				if ( Class.CastTo(car, player.GetCommand_Vehicle().GetTransport()) )
				{
	        if (car && !car.m_CarLock_IsLocked && car.m_CarLockOwner !=-1 && (car.m_CarLockOwner == player.CLSteamlowID || player.HasPassword(car.m_CarLockPassword,car.m_CarLockOwner)))
	        {
						GetRPCManager().SendRPC("CarLock", "CarLockRequest",  new Param2<ref CarScript, bool>(car,true), true, NULL);
	        }
					if (car && car.m_CarLock_IsLocked && car.m_CarLockOwner !=-1 && (car.m_CarLockOwner == player.CLSteamlowID || player.HasPassword(car.m_CarLockPassword,car.m_CarLockOwner)))
	        {
						GetRPCManager().SendRPC("CarLock", "CarLockRequest",  new Param2<ref CarScript, bool>(car,false), true, NULL);
	        }
				}
			}
		}
	}
};
#endif
