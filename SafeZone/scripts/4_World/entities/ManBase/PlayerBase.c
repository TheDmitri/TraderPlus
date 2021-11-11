class InsideSZ{

	string SZName;
	bool   SZStatut;

	void InsideSZ(){
		SZName="";
		SZStatut=false;
	}
}

modded class PlayerBase extends ManBase
{
	bool IsSZAdmin;
	bool ntCanShow;
	ref InsideSZ IsInsideSZ;
	int m_SZ_InfluenzaEnteredSafeZone;

	override void Init()
	{
		ntCanShow = true;
		IsSZAdmin = false;
		super.Init();
		IsInsideSZ=new InsideSZ;
		RegisterNetSyncVariableBool("IsSZAdmin");
	}

	void SetIsSZAdmin()
	{
		IsSZAdmin = true;
		SetSynchDirty();
	}

	override void OnConnect()
	{
		super.OnConnect();
	}

	override void SetSuicide(bool state)
	{
		super.SetSuicide(state);

		if (state && IsInsideSZ.SZStatut && GetGame().IsServer())
			SetAllowDamage(true);
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
		if(IsInsideSZ.SZStatut==true)
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
}
