modded class PlayerBase extends ManBase
{
	ref TraderPlusMenu m_TraderPlusMenu;
	private EffectSound m_TradeSound;

	int TraderID;
	int MaxPlayerPerID;

	override void Init()
	{
		super.Init();
		TraderID = -1;
		RegisterNetSyncVariableInt("TraderID");
	}

	void SetTraderID(int id)
	{
		TraderID = id;
		SetSynchDirty();
	}

	void SetupTrader(TraderPlusData data)
	{
		SetTraderID(data.Id);
		SetPosition(data.Position);
		SetOrientation(data.Orientation);
		SetAllowDamage(false);
		DressTrader(data.Clothes);

		//Safezone function so zombies get removed if chase NPC
		IsInsideSZ.SZStatut = true;
	}

	void DressTrader(array<string> clothes)
	{
		for (int i = 0; i < clothes.Count(); i++)
		{
			if(!clothes.Get(i) || clothes.Get(i) == "")continue;
			GetInventory().CreateInInventory(clothes.Get(i));
		}
	}

	/*override void SetLocalProjectionPosition( vector local_position )
	{
		local_position = TraderPlusHelper.snapToGround(local_position);
		m_LocalProjectionPosition = local_position;
	}*/

	void PlayTradeSound(bool sell)
	{
		if(m_TradeSound && m_TradeSound.IsSoundPlaying())m_TradeSound.SoundStop();
		if(sell)
		{
			PlaySoundSet( m_TradeSound,"TraderPlus_Sound_Sell_SoundSet" , 0, 0);
		}
		else
		{
			PlaySoundSet( m_TradeSound,"TraderPlus_Sound_Buy_SoundSet" , 0, 0);
		}
	}

	void MoveHologram(float value)
	{
		m_LocalProjectionPosition[1]=m_LocalProjectionPosition[1]+value;
	}

	override void SetActions()
  {
		super.SetActions();
		AddAction(ActionTraderPlusMenu);
  }
};
