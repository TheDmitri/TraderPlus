class TraderPlusItem
{
  string CategoryName;
  string ClassName;
  float  Coeff;
  int    Quantity;
  int    MaxStock;
  int    Health;
  int    BuyPrice;
  int    SellPrice;

  void TraderPlusItem(string categoryname,string name,float coeff, int maxstock,int qty, int sellprice,int buyprice, int state=0)
  {
    CategoryName = categoryname;
    ClassName = name;
    Coeff     = coeff;
    MaxStock  = maxstock;
    BuyPrice  = buyprice;
    SellPrice = sellprice;
    Quantity  = qty;
    Health    = state;
  }
};
