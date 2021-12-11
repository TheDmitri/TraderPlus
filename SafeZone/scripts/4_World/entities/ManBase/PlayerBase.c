modded class PlayerBase extends ManBase
{
	private int m_SafeZoneStatus;
	private int m_SafeZoneStatusLocal;
	private string m_SafeZoneName;
	bool ntCanShow;
	int m_SZ_InfluenzaEnteredSafeZone;

	override void Init()
	{
		ntCanShow = true;
		m_SafeZoneStatus = 0;
		m_SafeZoneStatusLocal = 0;
		m_SafeZoneName = "";
		super.Init();
		RegisterNetSyncVariableInt("m_SafeZoneStatus");
	}

	void SetAdminStatus()
	{
		m_SafeZoneStatus = m_SafeZoneStatus | 0x02;
		SetSynchDirty();
	}

	void SetSafeZoneStatus(bool state)
	{
		if(state) m_SafeZoneStatus = m_SafeZoneStatus | 0x01;
		else m_SafeZoneStatus = m_SafeZoneStatus & 0x00;
		HandlePersonnalHideOut();
		SetSynchDirty();
	}

	void SetSafeZoneName(string name)
	{
		m_SafeZoneName = name;
	}

	int GetSafeZoneStatus()
	{
		return m_SafeZoneStatus & 0x01;
	}

	int GetAdminStatus()
	{
		return m_SafeZoneStatus & 0x02;
	}

	string GetSafeZoneName()
	{
		return m_SafeZoneName;
	}

	override void SetSuicide(bool state)
	{
		super.SetSuicide(state);

		if (state && m_SafeZoneStatus == SZ_IN_SAFEZONE && GetGame().IsServer())
		{
			SetAllowDamage(true);
			SetSafeZoneStatus(false);
		}
	}

	//not used since rework
	private void SendMessageClient(string message)
	{
		Param1<string> m_MesParam = new Param1<string>(message);
		GetGame().RPCSingleParam(this, ERPCs.RPC_USER_ACTION_MESSAGE, m_MesParam, true, this.GetIdentity());
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef);
		if(m_SafeZoneStatus == SZ_IN_SAFEZONE)
		{
				if(source.IsDayZCreature() || source.IsAnimal());
				{
					source.Delete();
				}
				#ifdef SZDEBUG
				GetTraderPlusLogger().LogInfo(this.GetIdentity().GetName()+"the source of damage has been deleted");
				#endif
				return;
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		if(slot_name == "Armband")
		{
			if(item.IsKindOf("Clothing")){
				if(GetGame().IsServer())
				{
					HandlePersonnalHideOut();
					SetSynchDirty();
				}
			}
			if(item.IsInherited(HideOutObject))
			{
				item.SetPosition("0 0 0");
			}
		}
	}

	override bool CanDropEntity (notnull EntityAI item)
	{
		if(item.IsInherited(HideOutObject) && GetSafeZoneStatus() == SZ_IN_SAFEZONE)
			return false;

		return super.CanDropEntity(item);
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		if(m_SafeZoneStatusLocal != m_SafeZoneStatus)
		{
			m_SafeZoneStatusLocal = m_SafeZoneStatus;
			HandlePersonnalHideOut();
		}
	}

	void HandlePHOClient()
	{
		if(true)
		{
			#ifdef SZDEBUG
			GetTraderPlusLogger().LogInfo("IsHideOutActive");
			#endif
			int playerId;
			playerId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
			EntityAI tarmband;

			// if(GetSafeZoneStatus() == SZ_OUT_SAFEZONE)
			// {
			// 	// this.GetHumanInventory().SetSlotLock(InventorySlots.ARMBAND, false);
			// 	// Sleep(500);
			// 	EntityAI hideOut = this.FindAttachmentBySlotName("Armband");
			// 	if(!hideOut)return;
			// 	if(hideOut.IsInherited(Clothing))return;
			// 	PredictiveDropEntity(hideOut);
			// 	Sleep(500);
			//
			// 	#ifdef SZDEBUG
			// 	GetTraderPlusLogger().LogInfo("HideOut found and droped from slot!");
			// 	#endif
			//
			// 	hideOut.SetPosition("0 0 0");
			// 	return;
			// }

			HideOutObject stash;
			if(HideOutObject.GetMapAll().Find(playerId, stash))
			{
				tarmband = this.FindAttachmentBySlotName("Armband");
				if(tarmband && !tarmband.IsInherited(HideOutObject))
				{
					//NotificationSystem.SendNotificationToPlayerIdentityExtended(GetIdentity(), 2, "STASH WARNING", GetSZConfig().MustRemoveArmband, "SafeZone/images/SafeZone.paa");
					return;
				}
				#ifdef SZDEBUG
				GetTraderPlusLogger().LogInfo("HideOut found and added to slot!");
				#endif
				stash.SetPosition(GetPosition());
				LocalTakeEntityToTargetAttachmentEx( this, stash, InventorySlots.ARMBAND );
			}
		}
	}

	void HandlePHOServer()
	{
		if(GetSZConfig().IsHideOutActive)
		{
			#ifdef SZDEBUG
			GetTraderPlusLogger().LogInfo("IsHideOutActive");
			#endif
			int playerId;
			if(!GetIdentity())return;
			playerId = GetIdentity().GetPlainId().Substring(8, 9).ToInt();
			EntityAI tarmband;

			if(GetSafeZoneStatus() == SZ_OUT_SAFEZONE)
			{
				// this.GetHumanInventory().SetSlotLock(InventorySlots.ARMBAND, false);
				// SetSynchDirty();
				// Sleep(1000);
				#ifdef SZDEBUG
				GetTraderPlusLogger().LogInfo("GetSafeZoneStatus() == SZ_OUT_SAFEZONE");
				#endif
				EntityAI hideOut = this.FindAttachmentBySlotName("Armband");
				if(!hideOut)return;
				if(hideOut.IsInherited(Clothing))return;
				ServerDropEntity(hideOut);
				#ifdef SZDEBUG
				GetTraderPlusLogger().LogInfo("hideOut droped");
				#endif
				Sleep(500);

				hideOut.SetPosition("0 0 0");
				return;
			}

			HideOutObject stash;
			if(HideOutObject.GetMapAll().Find(playerId, stash))
			{
				tarmband = this.FindAttachmentBySlotName("Armband");
				if(tarmband && !tarmband.IsInherited(HideOutObject))
				{
					NotificationSystem.SendNotificationToPlayerIdentityExtended(GetIdentity(), 2, "STASH WARNING", GetSZConfig().MustRemoveArmband, "SafeZone/images/SafeZone.paa");
					return;
				}
				stash.SetPosition(GetPosition());
				Sleep(500);
				ServerTakeEntityToTargetAttachmentEx( this, stash, InventorySlots.ARMBAND );
				#ifdef SZDEBUG
				GetTraderPlusLogger().LogInfo("hideOut attached to slot");
				#endif
				// this.GetHumanInventory().SetSlotLock(InventorySlots.ARMBAND, true);
				// SetSynchDirty();
			}
			else
			{
					HideOutObject newHideOut = GetGame().CreateObject("HideOutObject", GetPosition());
					newHideOut.SetOwner(playerId);
					newHideOut.InitStarterKit();

					tarmband = this.FindAttachmentBySlotName("Armband");
					if(tarmband && !tarmband.IsInherited(HideOutObject)){
						newHideOut.SetPosition("0 0 0");
						NotificationSystem.SendNotificationToPlayerIdentityExtended(GetIdentity(), 2, "STASH WARNING", GetSZConfig().MustRemoveArmband, "SafeZone/images/SafeZone.paa");
						return;
					}

					ServerTakeEntityToTargetAttachmentEx( this, newHideOut, InventorySlots.ARMBAND );
					// this.GetHumanInventory().SetSlotLock(InventorySlots.ARMBAND, true);
					// SetSynchDirty();
			}
		}
	}

	void HandlePersonnalHideOut()
	{
		if(GetGame().IsServer())
		{
			thread HandlePHOServer();
		}
		else
		{
			thread HandlePHOClient();
		}
	}
}
