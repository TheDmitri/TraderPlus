class HideOutObject extends Container_Base
{
	private int m_PlayerID = 0;
	private int m_PlayerIDLocal = 0;

	private static ref map<int, HideOutObject > m_MapAllHideOut = new map<int, HideOutObject >;

	void HideOutObject()
	{
		RegisterNetSyncVariableInt("m_PlayerID");
	}

	void ~HideOutObject()
	{
		if(m_MapAllHideOut)
			m_MapAllHideOut.Remove(m_PlayerID);
	}

	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
	override bool CanPutInCargo( EntityAI item )
	{
		return false;
	}

	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if(GetGame().IsServer() && GetSZConfig() && GetSZConfig().BlackListedItemInStash.Find(item.GetType()) != -1)
			return false;

		if(GetGame().IsClient() && GetSZConfigClient() && GetSZConfigClient().BlackListedItemInStash.Find(item.GetType()) != -1)
			return false;

		return super.CanReceiveItemIntoCargo(item);
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		if(m_PlayerIDLocal != m_PlayerID)
		{
			m_PlayerIDLocal = m_PlayerID;
			m_MapAllHideOut.Set(m_PlayerID, this);
		}
	}

	static map<int, HideOutObject > GetMapAll()
	{
		#ifdef SZDEBUG
		GetTraderPlusLogger().LogInfo("Map All HideOut:"+m_MapAllHideOut.Count());
		#endif
		return m_MapAllHideOut;
	}

	void SetOwner(int id)
	{
		m_PlayerID = id;
		m_MapAllHideOut.Set(m_PlayerID, this);
		SetSynchDirty();
	}

	int GetOwner()
	{
		return m_PlayerID;
	}

	override void OnStoreSave( ParamsWriteContext ctx )
	{
		super.OnStoreSave( ctx );
		ctx.Write( m_PlayerID );
	}

	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;

		if ( !ctx.Read( m_PlayerID ) )
		{
			return false;
		}
		else
		{
			m_MapAllHideOut.Set(m_PlayerID, this);
		}

		SetPosition("0 0 0");
		return true;
	}

	void InitStarterKit()
	{
	};
}
