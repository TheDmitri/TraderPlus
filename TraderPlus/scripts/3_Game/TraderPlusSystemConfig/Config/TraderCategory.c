class TraderPlusCategory
{
	string CategoryName;
	ref array<string> Products;

  void TraderPlusCategory(string categoryname)
  {
    CategoryName = categoryname;
    Products 		 = new array<string>;
  }

  void AddProductToTraderPlusCategory(string product)
  {
    Products.Insert(product);
  }
};

class TraderPlusIDs
{
	bool              EnableStockAllCategoryForID;
	ref array<string> Categories;
	ref TStringArray  LicencesRequired;
	ref TStringArray  CurrenciesAccepted;

  void TraderPlusIDs(bool state)
  {
		EnableStockAllCategoryForID = state;
    Categories = new array<string>;
		LicencesRequired = new TStringArray;
		CurrenciesAccepted = new TStringArray;
  }

  void AddCategoryToId(string categoryname)
  {
    Categories.Insert(categoryname);
  }
};
