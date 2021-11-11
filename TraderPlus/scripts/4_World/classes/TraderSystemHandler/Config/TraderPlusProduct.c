//TradMod : true = sell / false = buy
class TraderPlusProduct
{
  int        TraderID;
  PlayerBase Customer=NULL;
  string     ClassName;
  int        Multiplier;
  int        Quantity;
  int        MaxStock;
  int        Health;
  int        Price;
  int        Position;
  int        TradMode=1;

  void Debug()
  {
    string title = "-------Product-------";
    string description="TraderID: "+TraderID.ToString();
    if(Customer)
    {
      description+=" - Customer: "+Customer.GetIdentity().GetName();
    }
    description+=" - ClassName: "+ClassName + " - Quantity: "+Quantity.ToString()+" - Multiplier: "+Multiplier.ToString()+" - MaxStock: "+MaxStock.ToString();
    description+=" - Health: "+Health.ToString();
    description+=" - Price: "+Price.ToString() + " - Position: "+Position.ToString();
    if(TradMode){
      description+=" - TradeMode:Sell";
    }else description+=" - TradeMode:Buy";
    //GetTraderPlusLogger().LogInfo(title);
    GetTraderPlusLogger().LogInfo(description);
  }
}
