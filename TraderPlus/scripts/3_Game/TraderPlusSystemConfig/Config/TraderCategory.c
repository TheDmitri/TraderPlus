class TraderPlusCategories
{
	string DummyString="DONT_ASK_WHY_IM_HERE";
	ref map<string, ref TStringArray> traderCategories;

	void TraderPlusCategories()
	{
		traderCategories = new map<string, ref TStringArray>;
	}

	void ConvertArrayCategoryToMap()
	{
		TraderPlusPriceSettings priceConfig = TraderPlusPriceSettings.Load();
		foreach(TraderPlusCategory tpCategory: priceConfig.TraderCategories)
		{
			traderCategories.Insert(tpCategory.CategoryName, tpCategory.Products);
		}
	}
}

class TraderPlusCategory
{
	string CategoryName;
	ref array<string> Products;

  void TraderPlusCategory(string categoryname = "")
  {
    CategoryName = categoryname;
    Products 		 = new array<string>;
  }

  void AddProductToTraderPlusCategory(string product)
  {
    Products.Insert(product);
  }

	void Save(int id)
	{
		string idPath = TRADERPLUS_DB_DIR_SERVER +"ID_"+id.ToString()+"\\";
		string categoryPath = idPath + CategoryName + ".json";
		TraderPlusJsonLoader<TraderPlusCategory>.SaveToFile(categoryPath, this);
	}
};

class TraderPlusIDs
{
	int               Id;
	bool              EnableStockAllCategoryForID;
	ref array<string> Categories;
	ref TStringArray  LicencesRequired;
	ref TStringArray  CurrenciesAccepted;

  void TraderPlusIDs(bool state = true)
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
