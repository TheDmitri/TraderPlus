
class TraderPlusBankingServer
{
    float BankingTick;
    ref BankingTransactionQueue TransactionsQueue;

    void TraderPlusBankingServer()
    {
      BankingTick = 0.0;
      TransactionsQueue = new BankingTransactionQueue;
      GetTraderPlusLogger().LogInfo("TraderPlusBankingServer - Started");
      //I usually make a small delay to make sure that my static config class is available
    }

  void  ~TraderPlusBankingServer(){}

  void OnUpdate(float timeslice)
  {
    BankingTick+=timeslice;
    if(BankingTick > TRADERPLUS_QUEUE_TRANSACTION_INTERVAL)
    {
        if(TransactionsQueue.HasNextQueue())
        {
          TransactionRequest(TransactionsQueue.Peek());
          TransactionsQueue.DeQueue();
        }
      BankingTick = 0;
    }
  }

  void TransactionRequest(TraderPlusBankingTransaction transaction)
  {
    int newAmount;
    if(transaction.TransactionMode)
    {
      if(transaction.Customer.m_BankAccount)
      {
        if(!TraderPlusBankHelpers.CheckifPlayerHasEnoughMoney(transaction.Customer, transaction.Amount))return;
        int amountMinusFees = transaction.Amount - transaction.Amount*GetTraderPlusBankConfigServer().TransactionFees;
        newAmount = transaction.Customer.m_BankAccount.MoneyAmount + amountMinusFees;
        TraderPlusBankHelpers.SetAmountBankAccount(transaction.Customer,newAmount);
        TraderPlusBankHelpers.RemoveMoneyFromPlayer(transaction.Customer,transaction.Amount);
      }
    }
    else
    {
      if(transaction.Customer.m_BankAccount)
      {
        if(transaction.Customer.m_BankAccount.MoneyAmount < transaction.Amount)return;
        newAmount = transaction.Customer.m_BankAccount.MoneyAmount - transaction.Amount;
        TraderPlusBankHelpers.SetAmountBankAccount(transaction.Customer,newAmount);
        TraderPlusBankHelpers.AddMoneyToPlayer(transaction.Customer,transaction.Amount);
      }
    }
  }

  //-------------------------------------------RPC PART--------------------------------------------------------//
  void TraderPlusBankingRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
  {
     if (!GetGame().IsServer())
     return;

     PlayerBase player = TraderPlusGetPlayerByIdentity(sender);

     TraderPlusBankingData m_tempdata = TraderPlusBankingData.Load(sender.GetPlainId(), GetTraderPlusBankConfigServer().DefaultMaxCurrency,GetTraderPlusBankConfigServer().DefaultStartCurrency,player.GetIdentity().GetName());
     if(player.m_BankAccount)
     {
       player.m_BankAccount = m_tempdata;
       if(player.m_BankAccount.MoneyAmount > player.m_BankAccount.MaxAmount){
         player.m_BankAccount.MoneyAmount = player.m_BankAccount.MaxAmount;
       }
     }
     TraderPlusBankHelpers.SendBankAccountInfo(player);

     #ifdef TRADERPLUSDEBUG
     GetTraderPlusLogger().LogInfo("TraderPlusBankingRequest by player:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
     #endif
  }

  void TraderPlusBankingWithdraw(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
  {
   if (!GetGame().IsServer())
     return;

     Param1<int> data;
     if (!ctx.Read(data))
       return;

     PlayerBase player = TraderPlusGetPlayerByIdentity(sender);

     TraderPlusBankingTransaction m_transaction = new TraderPlusBankingTransaction;
     m_transaction.Customer = player;
     m_transaction.Amount = data.param1;
     m_transaction.TransactionMode = false;

     TransactionsQueue.EnQueue(m_transaction);

     #ifdef TRADERPLUSDEBUG
     GetTraderPlusLogger().LogInfo("TraderPlusBankingWithdraw:"+player.GetIdentity().GetName() +" amount:" +data.param1.ToString()); //sender.GetName() = player.GetIdentity().GetName()
     #endif
  }

  void TraderPlusBankingDeposit(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
  {
   if (!GetGame().IsServer())
     return;

     Param1<int> data;
     if (!ctx.Read(data))
       return;

     PlayerBase player = TraderPlusGetPlayerByIdentity(sender);

     TraderPlusBankingTransaction m_transaction = new TraderPlusBankingTransaction;
     m_transaction.Customer = player;
     m_transaction.Amount = data.param1;
     m_transaction.TransactionMode = true;

     TransactionsQueue.EnQueue(m_transaction);

     #ifdef TRADERPLUSDEBUG
     GetTraderPlusLogger().LogInfo("TraderPlusBankingDeposit:"+sender.GetName() +" amount:" +data.param1.ToString()); //sender.GetName() = player.GetIdentity().GetName()
     #endif
  }
  //---------------------------------------------------------------------------------------------------------//
};
