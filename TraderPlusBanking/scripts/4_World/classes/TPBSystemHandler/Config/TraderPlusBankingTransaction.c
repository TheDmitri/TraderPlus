//TransactionMode : true = deposit / false = withdraw
class TraderPlusBankingTransaction
{
  PlayerBase Customer=NULL;
  int        Amount;
  bool       TransactionMode=true;

  void Debug()
  {
    string title = "-------BankingTransaction-------";
    string description = "";
    if(Customer)
    {
      description+=" - Customer: "+Customer.GetIdentity().GetName();
    }
    description+=" - Amount: "+Amount.ToString();
    if(TransactionMode){
      description+=" - TransactionMode: deposit";
    }else description+=" - TransactionMode: withdraw";
    GetTraderPlusLogger().LogInfo(title);
    GetTraderPlusLogger().LogInfo(description);
  }
}
