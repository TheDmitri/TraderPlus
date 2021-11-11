
class TraderPlusBankingMenu extends UIScriptedMenu
{
  //Player's panel widget
  private   Widget            m_PlayerAccountPanel;
  private   ButtonWidget      m_PlayerAccountBttn;
  private   ButtonWidget      m_PlayerWithdrawBttn;
  private   ButtonWidget      m_PlayerDepositBttn;
  private   RichTextWidget    m_PlayerDebugText;
  private   TextWidget        m_BankAmountText;
  private   TextWidget        m_PlayerFees;
  private   TextWidget        m_PlayerAmountText;
  private   TextWidget        m_PlayerAmountTextOutput;
  private   TextWidget        m_TransactionAmountText;
  private   TextWidget        m_BankAmountTextInput;
  private   TextWidget        m_MaxText;
  private   EditBoxWidget     m_PlayerAmountTextInput;
  private   ProgressBarWidget  m_MoneyProgressBar;

  ref TStringArray TextUI;

  private   int               m_MoneyAmountOnPlayer;
  private   int               m_MaxMoneyBank;
  private   int               m_MoneyBankAmount;

  private   bool              m_canTradeRequest;

  private   float             m_UIUpdate;
  private   float             m_transactionTick;


  //Clan's panel widget

  //Player's transfer widget

  void TraderPlusBankingMenu()
  {
    TextUI = new TStringArray;
    m_UIUpdate            = 0.0;
    m_transactionTick     = 0.0;
    m_MoneyAmountOnPlayer = 0;
    m_canTradeRequest     = true;
    m_MaxMoneyBank = 0;
    m_MoneyBankAmount = 0;
  }

  void Show(bool rep)
  {
    if(rep)
    {
      GetGame().GetInput().ChangeGameFocus(1);
      GetGame().GetUIManager().ShowUICursor(true);
      GetGame().GetMission().GetHud().Show(false);
      OnShow();
    }
    else
    {
      GetGame().GetInput().ResetGameFocus();
      GetGame().GetUIManager().ShowUICursor(false);
      GetGame().GetMission().GetHud().Show(true);
      OnHide();
    }
    layoutRoot.Show(rep);
  }

  override void OnShow()
	{
		super.OnShow();
		PPEffects.SetBlurMenu(0.5);
		GetGame().GetInput().ChangeGameFocus(1);
		SetFocus( layoutRoot );
    UIHandle();
	}

	override void OnHide()
	{
		super.OnHide();
		PPEffects.SetBlurMenu(0);
		GetGame().GetInput().ResetGameFocus();
		Close();
	}

  override Widget Init()
    {
		    layoutRoot = GetGame().GetWorkspace().CreateWidgets( "TraderPlusBanking/gui/BankUI.layout" );
        m_PlayerAccountPanel = Widget.Cast( layoutRoot.FindAnyWidget( "PlayerAccountPanel" ) );
        m_PlayerAccountBttn  = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "PlayerAccountBttn" ) );
        m_PlayerWithdrawBttn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "PlayerWithdrawBttn" ) );
        m_PlayerDepositBttn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "PlayerDepositBttn" ) );
        m_PlayerAmountTextInput = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "PlayerAmountTextInput" ) );
        m_PlayerDebugText = RichTextWidget.Cast(layoutRoot.FindAnyWidget( "PlayerDebugText" ));
        m_BankAmountText = TextWidget.Cast(layoutRoot.FindAnyWidget( "BankAmountText" ));
        m_PlayerFees = TextWidget.Cast(layoutRoot.FindAnyWidget( "PlayerFees" ));
        m_PlayerAmountText = TextWidget.Cast(layoutRoot.FindAnyWidget( "PlayerAmountText" ));
        m_PlayerAmountTextOutput = TextWidget.Cast(layoutRoot.FindAnyWidget( "PlayerAmountTextOutput" ));
        m_BankAmountTextInput = TextWidget.Cast(layoutRoot.FindAnyWidget( "BankAmountTextInput" ));
        m_TransactionAmountText = TextWidget.Cast(layoutRoot.FindAnyWidget( "TransactionAmountText" ));
        m_MaxText = TextWidget.Cast(layoutRoot.FindAnyWidget( "MaxText" ));
        m_MoneyProgressBar = ProgressBarWidget.Cast(layoutRoot.FindAnyWidget( "MoneyProgressBar" ));
        layoutRoot.Show(false);
        return layoutRoot;
    }

  void UIHandle()
  {
    string Text = GetTraderPlusBankingConfigClient().TextUI;
    TextUI.Clear();
    #ifdef TRADERPLUSDEBUG
    GetTraderPlusLogger().LogInfo("BankingBankMenu-UIHandle "+Text);
    #endif
    Text.Split(",",TextUI);
    #ifdef TRADERPLUSDEBUG
    GetTraderPlusLogger().LogInfo("BankingBankMenu-UIHandle count"+TextUI.Count().ToString());
    #endif
    m_BankAmountText.SetText(TextUI[0]);
    int fees = 100*GetTraderPlusBankingConfigClient().TransactionFees;
    m_PlayerFees.SetText(TextUI[1]+fees.ToString()+"%");
    m_PlayerAmountText.SetText(TextUI[2]);
    m_MaxText.SetText(TextUI[3]+GetBankAccount().MaxAmount.ToString());
    m_PlayerWithdrawBttn.SetText(TextUI[4]);
    m_PlayerDepositBttn.SetText(TextUI[5]);
    m_PlayerAccountBttn.SetText(TextUI[6]);
    m_TransactionAmountText.SetText(TextUI[12]);

    m_MoneyAmountOnPlayer = 0;
    m_MaxMoneyBank = GetBankAccount().MaxAmount;
    m_MoneyBankAmount = GetBankAccount().MoneyAmount;

    string stringMoneyBank = TraderPlusHelper.IntToCurrencyString(m_MoneyBankAmount, ",");
    m_BankAmountTextInput.SetText(stringMoneyBank);
    m_PlayerAmountTextInput.SetText("");
    MoneyUpdate();

    #ifdef TRADERPLUSDEBUG
    GetTraderPlusLogger().LogInfo("BankingBankMenu-UIHandle MaxMoney"+m_MaxMoneyBank.ToString());
    GetTraderPlusLogger().LogInfo("BankingBankMenu-UIHandle MoneyBankAmount"+m_MoneyBankAmount.ToString());
    #endif
    int progressValue = 0;
    if(m_MaxMoneyBank!=0)
    {
      progressValue = (m_MoneyBankAmount * 100)/m_MaxMoneyBank;
    }
    #ifdef TRADERPLUSDEBUG
    GetTraderPlusLogger().LogInfo("BankingBankMenu-UIHandle progressvalue"+progressValue.ToString());
    #endif
    m_MoneyProgressBar.SetCurrent(progressValue);

    m_UIUpdate = 1.0;
  }

  void MoneyUpdate()
  {
    m_MoneyAmountOnPlayer = GetPlayerMoney();
    string stringMoney = TraderPlusHelper.IntToCurrencyString(m_MoneyAmountOnPlayer, ",");
    m_PlayerAmountTextOutput.SetText(stringMoney);
  }

  override void Update(float timeslice)
  {
      if(m_UIUpdate > 0.0)
      {
        MoneyUpdate();
        m_UIUpdate -= timeslice;
      }

      if(!m_canTradeRequest)
      {
        m_transactionTick -= timeslice;
        if (m_transactionTick <= 0)
        {
              m_transactionTick = TRADERPLUS_BANK_TRANSACTION_INTERVAL;
              m_canTradeRequest = true;
        }
      }
  }

  static int GetPlayerMoney()
  {
      PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
      if(!player)return 0;

      int amount = 0;
      float qty;
      int value;
      array<EntityAI> itemsArray = new array<EntityAI>;
      player.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);
      for (int i = 0; i < itemsArray.Count(); i++)
      {
          ItemBase item = ItemBase.Cast(itemsArray.Get(i));
          if (item)
          {
              string className = item.GetType();
              for (int j = 0; j < GetTraderPlusConfigClient().MoneyName.Count(); j++)
              {
                TStringArray traderCurrencyArray = new TStringArray;
    						GetTraderPlusConfigClient().MoneyName.Get(j).Split( ",", traderCurrencyArray );
                for(int k=0;k<traderCurrencyArray.Count();k++)
                {
                  if (traderCurrencyArray.Get(k) == className)
                  {
                    if(GetTraderPlusBankingConfigClient().CurrenciesAccepted.Count() == 0)
                    {
                      qty = TraderPlusHelper.GetItemAmount(item);
                      value = GetTraderPlusConfigClient().MoneyValue.Get(j);
                      amount += (value * qty);
                      continue;
                    }

                    for(int l=0;l<GetTraderPlusBankingConfigClient().CurrenciesAccepted.Count();l++)
                    {
                      if(GetTraderPlusBankingConfigClient().CurrenciesAccepted[l]==traderCurrencyArray[k])
                      {
                        qty = TraderPlusHelper.GetItemAmount(item);
                        value = GetTraderPlusConfigClient().MoneyValue.Get(j);
                        amount += (value * qty);
                      }
                    }
                  }
                }
              }
          }
      }
      return amount;
  }

  override bool OnClick (Widget w, int x, int y, int button)
  {
    switch(w)
    {
      case m_PlayerAccountBttn: UIHandle();
      return true;
      break;

      case m_PlayerWithdrawBttn: WithdrawHandler();
      return true;
      break;

      case m_PlayerDepositBttn: DepositHandler();
      return true;
      break;
    }
    return false;
  }

  bool OnChange(Widget w, int x, int y, bool finished)
	{
		super.OnChange(w,x,y,finished);

		if (w == m_PlayerAmountTextInput)
		{
      string  Amount = m_PlayerAmountTextInput.GetText();
      int AmountAttempt = Amount.ToInt();
      m_PlayerDebugText.SetText("");
      if(HasCharacterInPassword(Amount))
      {
        m_PlayerDebugText.SetText(TextUI[7]);
        return false;
      }
      int AmountMinusFees = AmountAttempt - AmountAttempt*GetTraderPlusBankingConfigClient().TransactionFees;
      m_BankAmountTextInput.SetText(m_MoneyBankAmount.ToString()+"(+"+AmountMinusFees.ToString()+"/-"+AmountAttempt.ToString()+")");
		}
		return true;
	}

  bool HasCharacterInPassword(string pwd)
  {
    for(int i=0;i<pwd.Length();i++)
    {
      switch(pwd[i])
      {
        case "0":continue;
        break;

        case "1":continue;
        break;

        case "2":continue;
        break;

        case "3":continue;
        break;

        case "4":continue;
        break;

        case "5":continue;
        break;

        case "6":continue;
        break;

        case "7":continue;
        break;

        case "8":continue;
        break;

        case "9":continue;
        break;

        default:return true;
        break;
      }
    }
    return false;
  }

  void WithdrawHandler()
  {
    if(!m_canTradeRequest)
    {
      m_PlayerDebugText.SetText("#tpm_not_too_fast");
      return;
    }

    string  Amount = m_PlayerAmountTextInput.GetText();
    int AmountAttempt = Amount.ToInt();

    if(HasCharacterInPassword(Amount))
    {
      m_PlayerDebugText.SetText(TextUI[7]);
      return;
    }

    if(AmountAttempt <= 0)
    {
      AmountAttempt = GetBankAccount().MoneyAmount;
    }

    if(AmountAttempt > m_MoneyBankAmount)
    {
      m_PlayerDebugText.SetText(TextUI[9]);
      return;
    }

    GetRPCManager().SendRPC("TraderPlusBanking", "TraderPlusBankingWithdraw",  new Param1<int>(AmountAttempt), true, NULL);
    PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
    player.PlayTradeSound(false);
    m_canTradeRequest = false;
  }

  void DepositHandler()
  {
    if(!m_canTradeRequest)
    {
      m_PlayerDebugText.SetText("#tpm_not_too_fast");
      return;
    }

    string  Amount = m_PlayerAmountTextInput.GetText();
    int AmountAttempt = Amount.ToInt();

    if(HasCharacterInPassword(Amount))
    {
      m_PlayerDebugText.SetText(TextUI[7]);
      return;
    }

    if(AmountAttempt > m_MoneyAmountOnPlayer)
    {
      m_PlayerDebugText.SetText(TextUI[11]);
      return;
    }

    if(AmountAttempt <= 0)
    {
      AmountAttempt = GetPlayerMoney();
    }

    if(AmountAttempt > m_MaxMoneyBank || (AmountAttempt + m_MoneyBankAmount > m_MaxMoneyBank))
    {
      m_PlayerDebugText.SetText(TextUI[10]);
      return;
    }

    GetRPCManager().SendRPC("TraderPlusBanking", "TraderPlusBankingDeposit",  new Param1<int>(AmountAttempt), true, NULL);
    PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
    player.PlayTradeSound(true);
    m_canTradeRequest = false;
  }
};
