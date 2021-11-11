
modded class PlayerBase extends ManBase
{
	ref TraderPlusBankingMenu m_TraderPlusBankingMenu;
	ref TraderPlusBankingData m_BankAccount;

	override void Init()
	{
		super.Init();
		m_BankAccount = new TraderPlusBankingData;
	}

	override void SetActions()
  {
		super.SetActions();
		AddAction(ActionTraderPlusBankingMenu);
  }
};
