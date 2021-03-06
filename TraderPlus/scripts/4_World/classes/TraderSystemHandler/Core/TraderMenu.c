class TraderPlusMenu extends UIScriptedMenu
{
  //Widget of TraderPlusUI
  private   Widget            m_Background;
  private   Widget            m_ProductInformation;
  private   Widget            m_HighLightProduct;
  private   Widget            m_PanelWidgetHealth;
  private   Widget            m_PanelInventory;
  private   Widget            m_PanelPlayerPreview;
  private   Widget            m_LicenceWarningPanel;
  private   Widget            m_StockScrollPanel;
  private   Widget            m_InventoryScrollPanel;
  private   MultilineTextWidget m_LicenceWarningText;
  private   ButtonWidget      m_LicenceCloseBttn;
  private   ButtonWidget      m_BttnReset;
  private   ButtonWidget      m_BttnRemove;
  private   ButtonWidget      m_BttnBackToInventory;
  private   ButtonWidget      m_BttnSell;
  private   ButtonWidget      m_BttnBuy;
  private   ButtonWidget      m_BttnKit;
  private   ItemPreviewWidget m_MainItemPreview;
  private   PlayerPreviewWidget m_PlayerPreview;
  private   TextWidget        m_ShowAllText;
  private   TextWidget        m_TimerText;
  private   TextWidget        m_SlotCountText;
  private   TextWidget        m_QuantityText;
  private   TextWidget        m_InventoryCountText;
  private   TextWidget        m_StockCountText;
  private   TextWidget        m_HealthText;
  private   TextWidget        m_BuyPriceText;
  private   TextWidget        m_SellPriceText;
  //private   TextWidget        m_LoadingTextStock;
  //private   TextWidget        m_LoadingTextInv;
  private   TextWidget        m_PlayerNameText;
  private   TextWidget        m_PlayerMoneyText;
  private   TextWidget        m_TraderNameText;
  private   TextWidget        m_TraderDescriptionText;
  private   RichTextWidget    m_InformationText;
  private   EditBoxWidget     m_SearchInventoryBox;
  private   EditBoxWidget     m_SearchStockBox;
  private   XComboBoxWidget   m_StockCategories;
  private   XComboBoxWidget   m_InventoryCategories;
  private   XComboBoxWidget   m_QuantityMultiplier;
  private   CheckBoxWidget    m_ShowAllCheckBox;
  private   CheckBoxWidget    m_EnablePreview;

  private   ref array<GridSpacerWidget>	m_StockGrids;
  private   GridSpacerWidget	m_MasterStockGrid;
  private   ScrollWidget      m_StockScrollWidget;

  private   ref array<GridSpacerWidget>	m_InventoryGrids;
  private   GridSpacerWidget	m_MasterInventoryGrid;
  private   ScrollWidget      m_InventoryScrollWidget;

  //Preview item and player
  protected EntityAI          m_previewItem;
  protected PlayerBase        m_previewPlayer;

  private   int               TraderID;                  //int trader ID
  private   vector            TraderPos;                 //vector trader position

  private   int               m_SelectedPage;
  private   int               m_selectedRowStock;        //int of the current selected row in stock
  private   int               m_selectedRowInventory;    //int of the current selected row in inventory
  private   int               m_selectedCatInventory;    //int of current category selected in inventory
  private   int               m_selectedCatStock;        //int of the current selected category in stock
  private   int               m_playerMoney;             //int value of the amoubt of money in the player
  private   int               m_QtyMultiplier;           //int value that represent how many times when multiply default tradeqty

  //item preview part
  private   int               m_MainItemPreviewRotationX;
  private   int               m_MainItemPreviewRotationY;
  private   vector            m_MainItemPreviewOrientation;
  private   int 				      m_MainItemPreviewScale;

  //playerpreview part
  protected int               m_CharacterRotationX;
	protected int               m_CharacterRotationY;
	//protected int               m_CharacterScaleDelta;
	protected vector            m_CharacterOrientation;

  private   float             m_transactionTick;         //tick between 2 transaction - 0.5s
  private   float             m_UIUpdate;                //tick between two UI update - 1s
  private   float             m_ScrollListUpdate;        //tick between two product refresh when scrolling - 0.05s
  private   bool              m_canTradeRequest;         //bool that allow trade each m_transactionTick is reached, if not reached display NOT TOO FAST
  private   bool              m_canTrade;                //bool that allow trade if all condition are met : quantity ok, player has enough money etc...
  private   bool              m_RequestTrade;            //bool that is true when trade has been sent to server, will be true until response is back
  private   bool              m_SellMode;                //bool that is true when we're in inventory list false if we're in stock list
  private   bool              m_BuyMode;                 //bool that is true when we're in stock list false if we're in inventory list
  private   bool              m_ShowAll;                 //if check box show all is enable, we show all potential goods in the trader
  private   bool              m_IsPlayerPreviewEnable;
  private   string            m_MissingLicences;         //string that contains all the missing licenses to show in the warning frame
  private   string            m_SearchStock;
  private   string            m_SearchInventory;
  private   Object            m_Trader;                  //npc object

  private   ref array<EntityAI> localStockEntities;
  private   ref array<EntityAI> localInventoryEntities;
  private   int m_StockListPosition;
  private   int m_InventoryListPosition;

  //array list of all potential items that can be attached to item in hand
  private   ref TStringArray  m_compatibleItemsFromItemInHand;

  ref array<ref TraderPlusArticle> m_StockItems;
	ref array<ref TraderPlusArticle> m_PlayerItems;

  //current product that is shown in the product information panel
  ref TraderPlusProduct m_CurrentProduct;

  private ref map<Widget, int>	m_WidgetStockList;
  private ref map<Widget, int>	m_WidgetInventoryList;

  void TraderPlusMenu()
  {
    m_StockGrids                  = new array<GridSpacerWidget>;
    m_InventoryGrids              = new array<GridSpacerWidget>;
    localStockEntities            = new array<EntityAI>;
    localInventoryEntities        = new array<EntityAI>;
    m_WidgetStockList             = new map<Widget, int>();
    m_WidgetInventoryList         = new map<Widget, int>();
    m_StockItems                  = new array<ref TraderPlusArticle>;
  	m_PlayerItems                 = new array<ref TraderPlusArticle>;
    m_compatibleItemsFromItemInHand = new TStringArray;
    m_CurrentProduct              = new TraderPlusProduct;
    m_playerMoney                 = 0;
    m_transactionTick             = 0;
    m_canTradeRequest             = false;
    m_RequestTrade                = false;
    m_BuyMode                     = false;
    m_SellMode                    = false;
    m_ShowAll                     = false;
    m_IsPlayerPreviewEnable       = false;
    m_SelectedPage                = 1;
    m_ScrollListUpdate            = 0.0;
    m_UIUpdate                    = 0.0;
    m_selectedCatInventory        = 0;
    m_selectedCatStock            = 0;
    m_StockListPosition           = -1;
    m_MissingLicences             = "";
    m_SearchStock                 = "";
    m_SearchInventory             = "";
    m_CharacterOrientation        = "0 0 0";
  }

  void ~TraderPlusMenu()
  {
    DestroyLocalStockEntities();
    DestroyLocalInventoryEntities();
  }

  void DestroyAllChildren(Widget w)
	{
		while(w.GetChildren())
		{
			w.RemoveChild(w.GetChildren());
		}
	}

  void ClearAllStockList()
	{
		m_WidgetStockList.Clear();
    foreach(GridSpacerWidget stockGrid:m_StockGrids)
    {
      if(!stockGrid)continue;
      DestroyAllChildren(stockGrid);
      m_MasterStockGrid.RemoveChild(stockGrid);

    }
    m_StockGrids.Clear();
		DestroyLocalStockEntities();
	}

  void ClearAllInventoryList()
	{
		m_WidgetInventoryList.Clear();
    for(int i=0;i<m_InventoryGrids.Count();i++)
    {
      if(m_InventoryGrids[i])
      {
        DestroyAllChildren(m_InventoryGrids[i]);
        m_MasterInventoryGrid.RemoveChild(m_InventoryGrids[i]);
      }
    }
    m_InventoryGrids.Clear();
		DestroyLocalInventoryEntities();
	}

  void DestroyLocalStockEntities()
	{
		if (!localStockEntities || !localStockEntities.Count()) return;
		foreach (auto ent : localStockEntities)
		{
			if (ent)
				ent.Delete();
		}
    delete localStockEntities;
	}

  void DestroyLocalInventoryEntities()
	{
		if (!localInventoryEntities || !localInventoryEntities.Count()) return;
		foreach (auto ent : localInventoryEntities)
		{
			if (ent)
				ent.Delete();
		}
    delete localInventoryEntities;
	}

  override Widget Init()
  {
		    layoutRoot = GetGame().GetWorkspace().CreateWidgets( GetTraderPlusLayoutPath() );
        m_StockScrollPanel = Widget.Cast(layoutRoot.FindAnyWidget("StockScrollPanel"));
        m_InventoryScrollPanel = Widget.Cast(layoutRoot.FindAnyWidget("InventoryScrollPanel"));
        m_LicenceWarningPanel = Widget.Cast(layoutRoot.FindAnyWidget( "LicenceWarningPanel" ));
        m_LicenceWarningText = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "LicenceWarningText" ) );
        m_LicenceCloseBttn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "LicenceCloseBttn" ) );
        m_BttnSell = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BttnSell" ) );
        m_BttnBuy= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BttnBuy" ) );
        m_BttnReset  = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BttnReset" ) );
        m_BttnRemove  = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BttnRemove" ) );
        m_BttnBackToInventory  = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BttnBackToInventory" ) );
        m_BttnKit= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BttnKit" ) );
        m_PanelWidgetHealth = Widget.Cast(layoutRoot.FindAnyWidget( "PanelWidgetHealth" ));
        m_QuantityText = TextWidget.Cast(layoutRoot.FindAnyWidget( "QuantityText" ));
        m_HealthText = TextWidget.Cast(layoutRoot.FindAnyWidget( "HealthText" ));
        m_InventoryCountText = TextWidget.Cast(layoutRoot.FindAnyWidget( "InventoryCountText" ));
        m_StockCountText = TextWidget.Cast(layoutRoot.FindAnyWidget( "StockCountText" ));
        m_BuyPriceText = TextWidget.Cast(layoutRoot.FindAnyWidget( "BuyPriceText" ));
        m_SellPriceText = TextWidget.Cast(layoutRoot.FindAnyWidget( "SellPriceText" ));
        //m_LoadingTextStock= TextWidget.Cast(layoutRoot.FindAnyWidget( "LoadingTextStock" ));
        //m_LoadingTextInv= TextWidget.Cast(layoutRoot.FindAnyWidget( "LoadingTextInv" ));
        m_SearchInventoryBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget( "SearchInventoryBox" ));
        m_SearchStockBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget( "SearchStockBox" ));
        m_StockCategories = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget( "StockCategories" ));
        m_InventoryCategories = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget( "InventoryCategories" ));
        m_QuantityMultiplier = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget( "QuantityMultiplier" ));
        m_PlayerNameText = TextWidget.Cast(layoutRoot.FindAnyWidget( "PlayerNameText" ));
        m_PlayerMoneyText = TextWidget.Cast(layoutRoot.FindAnyWidget( "PlayerMoneyText" ));
        m_TraderNameText = TextWidget.Cast(layoutRoot.FindAnyWidget( "TraderNameText" ));
        m_TraderDescriptionText = TextWidget.Cast(layoutRoot.FindAnyWidget( "TraderDescriptionText" ));
        m_InformationText = RichTextWidget.Cast(layoutRoot.FindAnyWidget( "InformationText" ));
        m_ShowAllText     = TextWidget.Cast(layoutRoot.FindAnyWidget( "ShowAllText"));
        m_SlotCountText = TextWidget.Cast(layoutRoot.FindAnyWidget( "SlotCountText" ));
        m_QuantityText.SetColor(ARGB(255,28,223,77));
        m_ProductInformation = Widget.Cast(layoutRoot.FindAnyWidget( "ProductInformation" ));
        m_Background = Widget.Cast(layoutRoot.FindAnyWidget("Background"));
        m_PanelPlayerPreview = Widget.Cast(layoutRoot.FindAnyWidget("PanelPlayerPreview"));
        m_PanelInventory = Widget.Cast(layoutRoot.FindAnyWidget("PanelInventory"));
        m_ShowAllCheckBox = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ShowAllCheckBox"));
        m_EnablePreview= CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnablePreview"));
        m_BttnKit.Show(false);
        layoutRoot.Show(false);
        if(!GetTraderPlusConfigClient().EnableShowAllCheckBox)
        {
          m_ShowAllCheckBox.Show(false);
          m_ShowAllText.Show(false);
        }
        return layoutRoot;
    }


  //Some of you may be interrested by changing the layout of the trader, so here is the function you can override to change the path:
  string GetTraderPlusLayoutPath()
  {
    return "TraderPlus/gui/TraderPlusUI.layout";
  }

  void UIHandle()
  {
      //Before anything else, we check for potential licenses set to the trader
      LicencesHandler();

      m_canTrade = true;

      //Display trader names and roles
      GetTraderNameAndRole();

      //we check if item in hand is a weapon, if so, we get the compatible items link to it
      ItemInHandHandler();

      //We initiaze the categories from player's inventory
      InitPlayerCategories();
      //Then we get the remaining item regarding that category and we fill the inventory list
      PlayerCategoryHandler();

      //We initiaze the categories
      InitStockCategories();
      //we get items in stock from that category then we fill the list
      StockCategoryHandler();

      //in case of a previous trade, we try to show the current product to sell
      InventoryListHandler();

      //create the player preview based on the player's character
      if(m_IsPlayerPreviewEnable){
        InitPlayerPreview();
      }

      MoneyUpdate();
  }

  void LicencesHandler()
  {
    if(!HasLicences(TraderID))
    {
      m_Background.Show(false);
      m_LicenceWarningPanel.Show(true);
      m_LicenceWarningText.SetText("#tpm_licence_msg"+ "\n" +m_MissingLicences);
    }else
    {
      m_Background.Show(true);
      m_LicenceWarningPanel.Show(false);
    }
  }

  bool HasLicences(int id)
  {
    bool   missingLicence = false;
    string licences = GetTraderPlusConfigClient().Licences.Get(id);
    TStringArray licencesArr = new TStringArray;
    licences.Split(",",licencesArr);
    m_MissingLicences = "";
    foreach(string licence: licencesArr)
    {
      bool haslicence = false;
      if(!GetBankAccount() || !GetBankAccount().Licences)return true;
      if(GetBankAccount().Licences.Find(licence) == -1){
        missingLicence = true;
        m_MissingLicences += "\n -"+licence;
      }
    }
    return !missingLicence;
  }

  void ItemInHandHandler()
  {
    PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
    string     weaponInHand =TraderPlusHelper.GetItemInHand(player);
    if(weaponInHand!="")m_compatibleItemsFromItemInHand = TraderPlusHelper.GetCompatibleAttachmentsArray(weaponInHand);
  }

  void MoneyUpdate()
  {
    m_playerMoney = GetPlayerMoney();
    string stringMoney = TraderPlusHelper.IntToCurrencyString(m_playerMoney, ",");
    m_PlayerMoneyText.SetText("#tpm_money"+ " " +stringMoney);
  }

  override void Update(float timeslice)
  {
      if(m_UIUpdate > 0.0)
      {
        MoneyUpdate();
        InitPlayerCategories();
        PlayerCategoryHandler();
        m_UIUpdate -= timeslice;
      }

      if(m_ScrollListUpdate>=0.1)
      {
        SearchUpdate();

        if(m_StockScrollWidget && m_StockScrollWidget.GetVScrollPos01() > 0.75){
          FillStockListStep();
        }

        if(m_BuyMode){
          m_BttnBuy.Enable(true);
          m_BttnSell.Enable(false);
        }
        else{
          m_BttnSell.Enable(true);
          m_BttnBuy.Enable(false);
        }

        m_ScrollListUpdate = 0.0;
      }
      else
      {
        m_ScrollListUpdate += timeslice;
      }

      if (!m_canTradeRequest)
      {
          m_transactionTick -= timeslice;
          if (m_transactionTick <= 0)
          {
                m_transactionTick = TRADERPLUS_TRANSACTION_INTERVAL;
                m_canTradeRequest = true;
          }
      }
  }

  //Check for change in search bar or checkbox
  bool OnChange(Widget w, int x, int y, bool finished)
	{
		super.OnChange(w,x,y,finished);

    switch(w)
    {
      case m_ShowAllCheckBox:ShowAllCheckBoxHandler();
      return true;
      break;

      case m_EnablePreview:EnablePreviewHandler();
      return true;
      break;
    }
		return false;
	}

  void SearchUpdate()
  {
    SearchInventoryUpdate();
    SearchStockUpdate();
  }

  //search update function when one of the search bar changed
  void SearchInventoryUpdate()
  {
    string searchInventory = m_SearchInventoryBox.GetText();
    if(searchInventory != m_SearchInventory)
    {
      m_SearchInventory = searchInventory;
      ResetInventoryList();
      PlayerCategoryHandler();
    }
  }

  //search update function when one of the search bar changed
  void SearchStockUpdate()
  {
    string searchStock    = m_SearchStockBox.GetText();
    if(searchStock != m_SearchStock)
    {
      m_SearchStock = searchStock;
      ResetStockList();
      StockCategoryHandler();
    }
  }

  void ShowAllCheckBoxHandler()
  {
    if(m_ShowAllCheckBox.IsChecked())
    {
      m_ShowAll = true;
    }
    else
    {
      m_ShowAll = false;
    }
    InitStockCategories();
    StockCategoryHandler();
  }

  void EnablePreviewHandler()
  {
    if(m_EnablePreview.IsChecked())
    {
      m_IsPlayerPreviewEnable = true;
    }
    else
    {
      m_IsPlayerPreviewEnable = false;
      DeletePlayerPreview();
      m_PanelPlayerPreview.Show(false);
      m_PanelInventory.Show(true);
    }
  }

  //when mousebuttondown used, start update rotation for either item preview or player preview
  bool OnMouseButtonDown(Widget w, int x, int y, int button)
  {
    super.OnMouseButtonDown(w, x, y, button);
    switch(w)
    {
      case m_MainItemPreview:
      {
        GetGame().GetDragQueue().Call(this, "UpdateRotation");
        g_Game.GetMousePos(m_MainItemPreviewRotationX, m_MainItemPreviewRotationY);
        return true;
      }
      break;

      case m_PlayerPreview:
      {
        GetGame().GetDragQueue().Call(this, "UpdatePlayerRotation");
        g_Game.GetMousePos( m_CharacterRotationX, m_CharacterRotationY );
        return true;
      }
      break;
    }

    return false;
  }

  //update rotation for item preview
  void UpdateRotation(int mouse_x, int mouse_y, bool is_dragging)
  {
    vector orientation = m_MainItemPreviewOrientation;
    orientation[0] = orientation[0] + (m_MainItemPreviewRotationY - mouse_y);
    orientation[1] = orientation[1] - (m_MainItemPreviewRotationX - mouse_x);

    m_MainItemPreview.SetModelOrientation( orientation );

    if (!is_dragging)
    {
      m_MainItemPreviewOrientation = orientation;
    }
  }

  //update rotation for player preview
  void UpdatePlayerRotation(int mouse_x, int mouse_y, bool is_dragging)
  {
			vector orientation = m_CharacterOrientation;
			orientation[1] = orientation[1] - ( m_CharacterRotationX - mouse_x );

			m_PlayerPreview.SetModelOrientation( orientation );

			if ( !is_dragging )
			{
				m_CharacterOrientation = orientation;
			}
  }

  void GetItemDescription()
  {
    if(m_previewItem)
    {
      InventoryItem iItem = InventoryItem.Cast(m_previewItem);
      if(iItem)
      {
        m_InformationText.SetText(TraderPlusHelper.TrimUnt(iItem.GetTooltip()));
      }
    }
  }

  override bool OnMouseEnter(Widget w, int x, int y)
  {
    super.OnMouseEnter(w, x, y);
    switch(w)
    {
      case m_MainItemPreview:GetItemDescription();
      return true;
      break;
    }

    return false;
  }

	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
  {
    super.OnMouseLeave(w, enterW, x, y);
    switch(w)
    {
      case m_MainItemPreview:
      {
        m_InformationText.SetText("");
        if(m_BuyMode)
        {
          StockListHandler();
        }
        else
        {
          InventoryListHandler();
        }
      }
      return true;
      break;
    }

    return false;
  }

  //update item preview scale, maybe player too in the future
  override bool OnMouseWheel(Widget  w, int  x, int  y, int wheel)
  {
    super.OnMouseWheel(w, x, y, wheel);

    switch(w)
    {
      case m_MainItemPreview:
      {
        m_MainItemPreviewScale = wheel;
        UpdateScale();
        return true;
      }
      break;
    }
    return false;
  }

  //update item preview scale
  void UpdateScale()
  {
    float w, h, x, y;
    m_MainItemPreview.GetPos(x, y);
    m_MainItemPreview.GetSize(w,h);
    w = w + ( m_MainItemPreviewScale / 4);
    h = h + ( m_MainItemPreviewScale / 4 );
    if ( w > 0.5 && w < 3 )
    {
      m_MainItemPreview.SetSize( w, h );

      // align to center
      int screen_w, screen_h;
      GetScreenSize(screen_w, screen_h);
      float new_x = x - ( m_MainItemPreviewScale / 8 );
      float new_y = y - ( m_MainItemPreviewScale / 8 );
      m_MainItemPreview.SetPos( new_x, new_y );
    }
  }

  //filter inventory list based on searchfield in inv search bar
  void ShowFilteredInventoryList(string inventorycontent)
  {
    foreach(int idx, ref TraderPlusArticle playerItem: m_PlayerItems)
    {
      string showedName = TraderPlusHelper.GetDisplayName(playerItem.ClassName);
      showedName.ToLower();
      inventorycontent.ToLower();
      if(!showedName.Contains(inventorycontent) && !playerItem.ClassName.Contains(inventorycontent))
        m_PlayerItems.RemoveOrdered(idx);
    }
    FillInventoryList(m_PlayerItems.Count());
  }

  //filter stock list based on searchfield in inv search bar
  void ShowFilteredStockList(string stockcontent)
  {
    foreach(int idx, ref TraderPlusArticle stockItem: m_StockItems)
    {
      string showedName = TraderPlusHelper.GetDisplayName(stockItem.ClassName);
      showedName.ToLower();
      stockcontent.ToLower();
      if(!showedName.Contains(stockcontent) && !stockItem.ClassName.Contains(stockcontent))
        m_StockItems.RemoveOrdered(idx);
    }
    thread FillStockList(m_StockItems.Count());
  }

  //display trader name and role
  void GetTraderNameAndRole()
  {
    for(int i=0;i<GetTraderPlusConfigClient().TraderPos.Count();i++)
    {
      vector traderpos = GetTraderPlusConfigClient().TraderPos[i];
      float  distance  = vector.Distance(traderpos,TraderPos);
      if(distance < 1 )
      {
        m_TraderNameText.SetText(GetTraderPlusConfigClient().GivenNames[i]);
        m_TraderDescriptionText.SetText(GetTraderPlusConfigClient().Roles[i]);
      }
    }
  }

  //clear and define default categories for inventory list
  void InitPlayerCategories()
  {
    m_InventoryCategories.ClearAll();
    m_InventoryCategories.AddItem("#tpm_sellable");
    m_InventoryCategories.AddItem("#tpm_all");
    m_InventoryCategories.AddItem("#tpm_licences");
    m_InventoryCategories.AddItem("#tpm_vehicles");
    m_InventoryCategories.SetCurrentItem(m_selectedCatInventory);
  }

  //clear and define all categories linked to the traderID, add ALL in addition
  void InitStockCategories()
  {
    m_StockCategories.ClearAll();
    int categoryCount = GetTraderPlusClient().GetCategoriesFromID(TraderID);
    for (int i = 0; i < categoryCount; i++)
    {
      m_StockCategories.AddItem(GetTraderPlusClient().m_StockCategories[i]);
    }
    m_StockCategories.SetCurrentItem(m_selectedCatStock);
  }

  //fill inventory list based on all the arrays "m_playerItems"
  void FillInventoryList(int inventorycount)
  {
    ClearAllInventoryList();
    m_QtyMultiplier = 1;
    if(!m_InventoryScrollWidget)
    {
      m_InventoryScrollWidget = ScrollWidget.Cast(GetGame().GetWorkspace().CreateWidgets( "TraderPlus/gui/StockGrid.layout", m_InventoryScrollPanel));
      m_MasterInventoryGrid = GridSpacerWidget.Cast(m_InventoryScrollWidget.FindAnyWidget("StockGrid"));
    }
    int nbgrid = inventorycount/300 + 1;
    for(int i=0;i<nbgrid;i++)
    {
      GridSpacerWidget tempGrid = GridSpacerWidget.Cast(GetGame().GetWorkspace().CreateWidgets( "TraderPlus/gui/CategoryUI.layout", m_MasterInventoryGrid));
      m_InventoryGrids.Insert(tempGrid);
    }
    int count = 0;
    for(int j = 0; j<inventorycount;j++)
    {
      Widget widget;
  		ItemPreviewWidget itemPlaceholder;
  		TextWidget	itemName;
      ImageWidget	itemHealth;
      TextWidget	itemCount;
      TextWidget	itemCountTitle;
      TextWidget	itemPrice;

      int cA,cR,cG,cB;
      int tradeqty,maxstock, stock = 0;
      int currentGrid = j/300;
      string classname = m_PlayerItems[j].ClassName;
      int    health    = m_PlayerItems[j].Health;
      string category = GetTraderPlusClient().GetProductCategory(classname);
      stock = GetTraderPlusClient().GetStockProductFromStock(category,classname,health);
      //if stock qty exist, we define our stock var
      int    price = GetTraderPlusClient().CalculatePriceForThatItem(m_QtyMultiplier,TRADEMODE_SELL,category,classname,stock,health,maxstock, tradeqty);
      #ifdef TRADERPLUSDEBUG
  		GetTraderPlusLogger().LogInfo("Product:"+classname + " price:"+price);
  		#endif
      if(m_InventoryGrids[currentGrid] == NULL)return;
  		widget = GetGame().GetWorkspace().CreateWidgets( "TraderPlus/gui/ProductCard.layout", m_InventoryGrids[currentGrid]);

  		if (!widget) return;

  		itemPlaceholder = ItemPreviewWidget.Cast(widget.FindAnyWidget("ProductPreview"));
  		itemName 		= TextWidget.Cast(widget.FindAnyWidget("Title"));
      itemHealth  = ImageWidget.Cast(widget.FindAnyWidget("Health"));
      itemCountTitle= TextWidget.Cast(widget.FindAnyWidget("StockCountTitle"));
      itemCount  = TextWidget.Cast(widget.FindAnyWidget("StockCountInput"));
      itemPrice = TextWidget.Cast(widget.FindAnyWidget("Price"));

      string itemType = classname;
      if(itemType.Contains(GetTraderPlusConfigClient().LicenceKeyWord))itemType = "Paper";
  		EntityAI localEnt = EntityAI.Cast(GetGame().CreateObject(itemType, vector.Zero, true, false));

      string displayName = TraderPlusHelper.GetDisplayName(classname);
      int NameLenght = displayName.Length();
      if(NameLenght <= 12)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("Title"));
      }else if(NameLenght <= 16)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleSmall"));
      }else if(NameLenght <= 22)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleVerySmall"));
      }else
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleExtraSmall"));
      }
      itemName.SetText(displayName);
      itemName.Show(true);
      #ifdef TRADERPLUSDEBUG
  		GetTraderPlusLogger().LogInfo("Product:"+classname + " health:"+health);
  		#endif
      string healthText = TraderPlusHelper.GetHealthFromLevel(health,cA,cR,cG,cB);
      itemPrice.SetText(TraderPlusHelper.IntToCurrencyString(price, ","));
      itemHealth.SetColor(ARGB(cA,cR,cG,cB));
      itemCountTitle.SetText("#tpm_count"+" "+":");
      itemCount.SetText(m_PlayerItems[j].Count.ToString());
      ItemBase temp = ItemBase.Cast(localEnt);
      if(temp)
      {
        if(temp.IsInherited(Ammunition_Base))
        {
          Print("Ammunition_Base");
        }
        if(classname.Contains("Mag"))
        {
          Print("Mag");
        }
        if(temp.IsInherited(Ammunition_Base) && !classname.Contains("Mag"))
        {
          Print("Mag + Ammunition_Base");
          itemCount.SetText(m_PlayerItems[j].Quantity.ToString());
        }
      }
      m_WidgetInventoryList.Insert(widget, j);
      if (localEnt)
      {
        itemPlaceholder.SetItem(localEnt);
        itemPlaceholder.SetModelPosition( Vector( 0, 0, 0.5 ) );
        itemPlaceholder.SetModelOrientation( vector.Zero );
        itemPlaceholder.SetView( localEnt.GetViewIndex() );
        if(!localInventoryEntities)localInventoryEntities = new array<EntityAI>;
        localInventoryEntities.Insert(localEnt);
      }
    }
    m_InventoryCountText.SetText("#tpm_inventory_count"+ " " + inventorycount.ToString());
  }

  void FillStockListStep()
  {
    int maxcount = m_StockItems.Count();
    int currentcount = m_WidgetStockList.Count();
    if(currentcount == maxcount)return;
    int step = currentcount + 20;
    if(step > maxcount)step = maxcount;
    for(int i = currentcount; i<step;i++)
    {
      Widget widget;
  		ItemPreviewWidget itemPlaceholder;
  		TextWidget	itemName;
      ImageWidget	itemHealth;
      TextWidget	itemStock;
      TextWidget	itemStockTitle;
      TextWidget	itemPrice;

      int cA,cR,cG,cB;
      string classname = m_StockItems[i].ClassName;
      int    quantity= m_StockItems[i].Quantity;
      int    maxstock= m_StockItems[i].MaxStock;
      int    health  = m_StockItems[i].Health;
      int    tradeqty;
      string  category = GetTraderPlusClient().GetProductCategory(classname);
      int    price = GetTraderPlusClient().CalculatePriceForThatItem(m_QtyMultiplier,false,category,classname,quantity,health,maxstock, tradeqty);
      int    currentGrid = i/300;

      if(m_StockGrids[currentGrid] == NULL)return;
      widget = GetGame().GetWorkspace().CreateWidgets( "TraderPlus/gui/ProductCard.layout", m_StockGrids[currentGrid]);
      if (!widget) return;
      itemPlaceholder = ItemPreviewWidget.Cast(widget.FindAnyWidget("ProductPreview"));
      string itemType = classname;
      if(itemType.Contains(GetTraderPlusConfigClient().LicenceKeyWord))itemType = "Paper";
    	EntityAI localEnt = EntityAI.Cast(GetGame().CreateObject(itemType, vector.Zero, true, false));
      if (localEnt)
      {
          itemPlaceholder.SetItem(localEnt);
          itemPlaceholder.SetModelPosition( Vector( 0, 0, 0.5 ) );
          itemPlaceholder.SetModelOrientation( vector.Zero );
          itemPlaceholder.SetView( localEnt.GetViewIndex() );
          if(!localStockEntities)localStockEntities = new array<EntityAI>;
          localStockEntities.Insert(localEnt);
          m_StockCountText.SetText("#tpm_stock_count" + " " +i.ToString());
      }
      itemHealth  = ImageWidget.Cast(widget.FindAnyWidget("Health"));
      itemStockTitle= TextWidget.Cast(widget.FindAnyWidget("StockCountTitle"));
      itemStock  = TextWidget.Cast(widget.FindAnyWidget("StockCountInput"));
      itemPrice = TextWidget.Cast(widget.FindAnyWidget("Price"));

      string displayName = TraderPlusHelper.GetDisplayName(classname);
      int NameLenght = displayName.Length();
      if(NameLenght <= 12)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("Title"));
      }else if(NameLenght <= 16)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleSmall"));
      }else if(NameLenght <= 22)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleVerySmall"));
      }else
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleExtraSmall"));
      }
      itemName.SetText(displayName);
      itemName.Show(true);
      string healthText = TraderPlusHelper.GetHealthFromLevel(health,cA,cR,cG,cB);
      itemPrice.SetText(TraderPlusHelper.IntToCurrencyString(price, ","));
      itemHealth.SetColor(ARGB(cA,cR,cG,cB));
      string strquantity = quantity.ToString();
      if(quantity==-1 || maxstock == -1)
      {
        strquantity="???";
      }else strquantity = strquantity + "/" + maxstock.ToString();
      itemStockTitle.SetText("#tpm_stock"+" "+":");
      itemStock.SetText(strquantity);
      if(quantity == maxstock && quantity != -1)
      {
        itemName.SetColor(ARGB(255,191,48,48) );
        itemHealth.SetColor(ARGB(255,191,48,48) );
        itemStock.SetColor(ARGB(255,191,48,48) );
      }
      if(IsItemCompatible(classname))
      {
        Widget highLightProduct = Widget.Cast(widget.FindAnyWidget("Highlight"));
        highLightProduct.Show(true);
        highLightProduct.SetColor(ARGB(250,216,89,1));
        itemName.SetColor(ARGB(250,216,89,1));
      }
      m_WidgetStockList.Insert(widget, i);
    }
    m_StockCountText.SetText("#tpm_stock_count" + " " +step.ToString());
  }

  //fill all the stock list based on arrays "m_StockItems"
  void FillStockList(int stockcount)
  {
    ClearAllStockList();
    m_QtyMultiplier = 1;
    if(!m_StockScrollWidget)
    {
      m_StockScrollWidget = ScrollWidget.Cast(GetGame().GetWorkspace().CreateWidgets( "TraderPlus/gui/StockGrid.layout", m_StockScrollPanel));
      m_MasterStockGrid = GridSpacerWidget.Cast(m_StockScrollWidget.FindAnyWidget("StockGrid"));
    }
    int nbgrid = stockcount/300 + 1;
    for(int j=0;j<nbgrid;j++)
    {
      GridSpacerWidget tempGrid;
      tempGrid = GridSpacerWidget.Cast(GetGame().GetWorkspace().CreateWidgets( "TraderPlus/gui/CategoryUI.layout", m_MasterStockGrid));
      m_StockGrids.Insert(tempGrid);
    }
    int count = stockcount;
    if(count > 100)count = 100;
    for(int i = 0; i<count;i++)
    {
      Widget widget;
  		ItemPreviewWidget itemPlaceholder;
  		TextWidget	itemName;
      ImageWidget	itemHealth;
      TextWidget	itemStock;
      TextWidget	itemStockTitle;
      TextWidget	itemPrice;

      int cA,cR,cG,cB;
      string classname = m_StockItems[i].ClassName;
      string category = GetTraderPlusClient().GetProductCategory(classname);
      int    quantity = m_StockItems[i].Quantity;
      string strquantity = m_StockItems[i].Quantity.ToString();
      int    health = m_StockItems[i].Health;
      int    maxstock= m_StockItems[i].MaxStock;
      int    tradeqty;
      int    price = GetTraderPlusClient().CalculatePriceForThatItem(m_QtyMultiplier,false,category,classname,quantity,health,maxstock, tradeqty);
      int    currentGrid = i/300;

      if(m_StockGrids[currentGrid] == NULL)return;
      widget = GetGame().GetWorkspace().CreateWidgets( "TraderPlus/gui/ProductCard.layout", m_StockGrids[currentGrid]);
      if (!widget) return;
      itemPlaceholder = ItemPreviewWidget.Cast(widget.FindAnyWidget("ProductPreview"));
      string itemType = classname;
      if(itemType.Contains(GetTraderPlusConfigClient().LicenceKeyWord))itemType = "Paper";
    	EntityAI localEnt = EntityAI.Cast(GetGame().CreateObject(itemType, vector.Zero, true, false));
      if (localEnt)
      {
          itemPlaceholder.SetItem(localEnt);
          itemPlaceholder.SetModelPosition( Vector( 0, 0, 0.5 ) );
          itemPlaceholder.SetModelOrientation( vector.Zero );
          itemPlaceholder.SetView( localEnt.GetViewIndex() );
          if(!localStockEntities)localStockEntities = new array<EntityAI>;
          localStockEntities.Insert(localEnt);
          m_StockCountText.SetText("#tpm_stock_count" + " " +i.ToString());
      }
      itemHealth  = ImageWidget.Cast(widget.FindAnyWidget("Health"));
      itemStockTitle= TextWidget.Cast(widget.FindAnyWidget("StockCountTitle"));
      itemStock  = TextWidget.Cast(widget.FindAnyWidget("StockCountInput"));
      itemPrice = TextWidget.Cast(widget.FindAnyWidget("Price"));

      string displayName = TraderPlusHelper.GetDisplayName(classname);
      int NameLenght = displayName.Length();
      if(NameLenght <= 12)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("Title"));
      }else if(NameLenght <= 16)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleSmall"));
      }else if(NameLenght <= 22)
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleVerySmall"));
      }else
      {
        itemName 		= TextWidget.Cast(widget.FindAnyWidget("TitleExtraSmall"));
      }
      itemName.SetText(displayName);
      itemName.Show(true);
      string healthText = TraderPlusHelper.GetHealthFromLevel(health,cA,cR,cG,cB);
      itemPrice.SetText(TraderPlusHelper.IntToCurrencyString(price, ","));
      itemHealth.SetColor(ARGB(cA,cR,cG,cB));
      if(strquantity=="-1" || maxstock == -1)
      {
        strquantity="???";
      }else strquantity = strquantity + "/" + maxstock.ToString();
      itemStockTitle.SetText("#tpm_stock"+" "+":");
      itemStock.SetText(strquantity);
      if(quantity == maxstock && quantity != -1)
      {
        itemName.SetColor(ARGB(255,191,48,48) );
        itemHealth.SetColor(ARGB(255,191,48,48) );
        itemStock.SetColor(ARGB(255,191,48,48) );
      }
      if(IsItemCompatible(classname))
      {
        Widget highLightProduct = Widget.Cast(widget.FindAnyWidget("Highlight"));
        highLightProduct.Show(true);
        highLightProduct.SetColor(ARGB(250,216,89,1));
        itemName.SetColor(ARGB(250,216,89,1));
      }
      m_WidgetStockList.Insert(widget, i);
    }
    m_StockCountText.SetText("#tpm_stock_count" + " " +stockcount.ToString());
  }

  //Based on item in hand and resulting array determine in UIHandle(), we check for an item if it's compatible
  bool IsItemCompatible(string classname)
  {
    for(int i = 0; i < m_compatibleItemsFromItemInHand.Count();i++)
    {
      if(m_compatibleItemsFromItemInHand[i]==classname)
        return true;
    }
    return false;
  }

  //Get category and show item in inv list according to the category chosen
  void PlayerCategoryHandler()
  {
    m_selectedCatInventory = m_InventoryCategories.GetCurrentItem();
    ResetPlayerItemsArray();
    int inventoryCount = GetTraderPlusClient().GetPlayerItemsFromCategory(m_selectedCatInventory,m_PlayerItems,m_SearchInventory);
    FillInventoryList(inventoryCount);
  }

  //Get category and show item in stock list according to the category chosen
  void StockCategoryHandler()
	{
		m_selectedCatStock = m_StockCategories.GetCurrentItem();
    ResetStockItemsArrays();
    int stockcount = GetTraderPlusClient().GetItemInStockFromCategory(m_selectedCatStock,m_StockItems, m_ShowAll, m_SearchStock);
    thread FillStockList(stockcount);
	}

  //Clear the combo multiplier when it's a an item available in stock
  void RefreshAndSetQuantityMultiplierStock(int tradeqty, int maxitemqty, int itemqty = -1)
  {
    m_QuantityMultiplier.ClearAll();
    if(tradeqty == -1 || tradeqty == 0 || (tradeqty == 1 && maxitemqty <= 1 && itemqty <= 1))
    {
      m_QuantityMultiplier.AddItem("1");
      m_QuantityMultiplier.SetCurrentItem(0);
      return;
    }
    else
    {
      if(maxitemqty<itemqty)maxitemqty = itemqty;
      int count = maxitemqty/tradeqty;
      int pos   = 0;
      if(count > 50)count=50;
      for(int i = 0;i<count;i++)
      {
        string data = ((i+1)*tradeqty).ToString();
        m_QuantityMultiplier.AddItem(data);
      }
      m_QuantityMultiplier.SetCurrentItem(0);
    }
    return;
  }

  //Clear the combo multiplier when it's a an item available in inv
  void RefreshAndSetQuantityMultiplierInventory(string classname, int tradeqty, int maxitemqty, int itemqty = -1, int itemcount = 1)
  {
    m_QuantityMultiplier.ClearAll();
    int count = 1;
    if(itemqty == -1)itemqty = maxitemqty;
    if(tradeqty != 0)count = itemqty / tradeqty;
    if(classname.Contains("Mag_"))
    {
      if(tradeqty == 0)
      {
        count = itemcount;
        tradeqty = 1;
      }
      else
      {
        count = itemqty / tradeqty;
        tradeqty = 1;
      }
    }
    if(maxitemqty == 0)
    {
      count = itemcount;
      tradeqty = 1;
    }
    if(count > 50)count=50;
    for(int i = 0;i<count;i++)
    {
      string data = ((i+1)*tradeqty).ToString();
      m_QuantityMultiplier.AddItem(data);
    }
    m_QuantityMultiplier.SetCurrentItem(0);
  }

  //When clicking on the multiplier combo, we refresh the invotorylisthandler or the stockhandler
  void QuantityMultiplierHandler()
  {
    if(m_CurrentProduct.Price == -1)return;
    m_QtyMultiplier = m_QuantityMultiplier.GetCurrentItem();
    m_QtyMultiplier+=1;
    if(m_CurrentProduct.TradMode)
      InventoryListHandler();
    else
      StockListHandler();
  }

  void ResetMultiplier()
  {
    m_QtyMultiplier = 1;
    m_QuantityMultiplier.ClearAll();
    m_QuantityMultiplier.AddItem("1");
  }

  //Buy quickly when double clicking a product in the list
  void QuickBuyHandler()
  {
    ResetMultiplier();
    m_BuyMode = true;
    m_SellMode = false;
    if(!m_ProductInformation.IsVisible())
        m_ProductInformation.Show(true);
    StockListHandler();
    BuyHandler();
  }

  //Sell quickly when double clicking a product in the list
  void QuickSellHandler()
  {
    ResetMultiplier();
    m_BuyMode = false;
    m_SellMode = true;
    if(!m_ProductInformation.IsVisible())
        m_ProductInformation.Show(true);
    InventoryListHandler();
    SellHandler();
  }

  //On double click is needed so we can trade simply by double clicking
  bool OnDoubleClick(Widget w, int x, int y, int button)
  {
    if(w.GetUserID() == 20062002)
    {
      #ifdef TRADERPLUSDEBUG
      GetTraderPlusLogger().LogInfo("OnClick Special list name:"+w.GetParent().GetName());
      #endif
      int i,j;
      if(m_WidgetStockList.Find(w.GetParent(),i))
      {
        if(m_HighLightProduct)
        {
          m_HighLightProduct.Show(false);
        }
        else
        {
          m_HighLightProduct = Widget.Cast(w.GetParent().FindAnyWidget("Highlight"));
          m_HighLightProduct.Show(true);
        }
        m_StockListPosition = i;
        QuickBuyHandler();
        return true;
      }
      else
      {
        m_StockListPosition = -1;
      }

      if(m_WidgetInventoryList.Find(w.GetParent(),j))
      {
        if(m_HighLightProduct)
        {
          m_HighLightProduct.Show(false);
        }
        else
        {
          m_HighLightProduct = Widget.Cast(w.GetParent().FindAnyWidget("Highlight"));
          m_HighLightProduct.Show(true);
        }
        m_InventoryListPosition = j;
        QuickSellHandler();
        return true;
      }
      else
      {
        m_InventoryListPosition = -1;
      }
      return true;
    }

    return false;
  }

  void ResetStockList()
  {
    if(m_StockScrollWidget)
    {
      DestroyAllChildren(m_StockScrollWidget);
      delete m_StockScrollWidget;
      delete m_MasterStockGrid;
    }
  }

  void ResetInventoryList()
  {
    if(m_InventoryScrollWidget)
    {
      DestroyAllChildren(m_InventoryScrollWidget);
      delete m_InventoryScrollWidget;
      delete m_MasterInventoryGrid;
    }
  }

  //on click needed for a lot of things
  override bool OnClick (Widget w, int x, int y, int button)
  {
    super.OnClick(w,x,y,button);
    if(w.GetUserID() == 20062002)
    {
      int i,j;
      if(m_WidgetStockList.Find(w.GetParent(),i))
      {
        if(m_HighLightProduct)m_HighLightProduct.Show(false);
        m_HighLightProduct = Widget.Cast(w.GetParent().FindAnyWidget("Highlight"));
        m_HighLightProduct.Show(true);
        m_StockListPosition = i;
        ResetMultiplier();
        StockListHandler();
        return true;
      }
      else
      {
        m_StockListPosition = -1;
      }

      if(m_WidgetInventoryList.Find(w.GetParent(),j))
      {
        if(m_HighLightProduct) m_HighLightProduct.Show(false);
        m_HighLightProduct = Widget.Cast(w.GetParent().FindAnyWidget("Highlight"));
        m_HighLightProduct.Show(true);
        m_InventoryListPosition = j;
        ResetMultiplier();
        InventoryListHandler();
        return true;
      }
      else
      {
        m_InventoryListPosition = -1;
      }
      return true;
    }

    switch(w)
    {
      case m_BttnKit:KitHandler();
      return true;
      break;

      case m_LicenceCloseBttn:OnHide();
      return true;
      break;

      case m_InventoryCategories:
      {
        ResetInventoryList();
        PlayerCategoryHandler();
        m_ProductInformation.Show(false);
      }
      return true;
      break;

      case m_StockCategories:
      {
        ResetStockList();
        StockCategoryHandler();
        LicenceCheck(GetTraderPlusClient().m_StockCategories.Get(m_StockCategories.GetCurrentItem()))
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(PlayerCategoryHandler, 200);
        m_StockListPosition = -1;
        m_ProductInformation.Show(false);
        return true;
      }
      break;

      case m_QuantityMultiplier:QuantityMultiplierHandler();
      return true;
      break;

      case m_BttnBuy: BuyHandler();
      return true;
      break;

      case m_BttnSell: SellHandler();
      return true;
      break;

      case m_BttnBackToInventory: BackToInventoryHandler();
      return true;
      break;

      case m_BttnRemove:RemoveAllPlayerClothes();
      return true;
      break;

      case m_BttnReset:InitPlayerPreview();
      return true;
      break;
    }
    return false;
  }

  void LicenceCheck(string categoryName)
  {
    if(GetBankAccount() && GetBankAccount().Licences){
      if(categoryName.Contains(GetTraderPlusConfigClient().LicenceKeyWord) && GetBankAccount().Licences.Find(categoryName) == -1)
        m_InformationText.SetText("#tpm_licence_msg"+ "\n" +categoryName);
        return;
    }
    m_InformationText.SetText("");
  }

  //hide player preview and show inventory panel
  void BackToInventoryHandler()
  {
    m_PanelPlayerPreview.Show(false);
    m_PanelInventory.Show(true);
  }

  //look to see if previous product trade still exist so we keep showing it in the product information panel
  int  CheckifPreviousProductExist(string productname,int health, bool state)
  {
    if(state)
    {
      for(int i=0;i<m_StockItems.Count();i++)
      {
        if(m_StockItems[i].ClassName==productname && m_StockItems[i].Health == health)
        {
          return i;
        }
      }
    }
    else
    {
      for(int j=0;j<m_PlayerItems.Count();j++)
      {
        if(m_PlayerItems[j].ClassName==productname && m_PlayerItems[j].Health == health)
        {
          return j;
        }
      }
    }
    return -1;
  }

  //We a product is selected in stock, we'll run all the functions to check price based on stock, quantity, health, etc.. in order to make the trade ready to be reauested
  void StockListHandler()
  {
    SetTradeMode(TRADEMODE_BUY);

    if(!m_ProductInformation.IsVisible())m_ProductInformation.Show(true);

    //m_ProductInformation.Show(true);
    m_selectedRowStock = m_StockListPosition;
    int tempRow = CheckifPreviousProductExist(m_CurrentProduct.ClassName,m_CurrentProduct.Health, 1);
    if(m_selectedRowStock == -1)
    {
      if(tempRow == -1 && m_CurrentProduct.MaxStock != -1)
      {
        ResetProductPanel();
        return;
      }
      else m_selectedRowStock = tempRow;
    }

    string classname = m_StockItems[m_selectedRowStock].ClassName;
    string category = GetTraderPlusClient().GetProductCategory(classname);
    int    health    = m_StockItems[m_selectedRowStock].Health;

    UpdateItemPreview(classname);

    //Show item health status
    GetTextAndColorRegardingHealth(health);

    int slotcount = TraderPlusHelper.GetItemSlotCount(classname);
    if(slotcount == 0)
    {
      m_SlotCountText.SetText("");
    }else m_SlotCountText.SetText("#tpm_slot"+ " " +slotcount.ToString());

    //Show quantity in stock
    int stock = m_StockItems[m_selectedRowStock].Quantity;

    //Show sellprice of our item based on stock and qty desired
    int TradeQty, MaxStock;
    int MaxItemQty = TraderPlusHelper.GetMaxItemQuantityClient(classname);
    #ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("Buy Product: maxitemqty:"+MaxItemQty.ToString());
		#endif

    int Price = GetTraderPlusClient().CalculatePriceForThatItem(m_QtyMultiplier,false,category,classname,stock,health,MaxStock, TradeQty);
    int SellPrice = GetTraderPlusClient().CalculatePriceForThatItem(m_QtyMultiplier,true,category,classname,stock,health,MaxStock, TradeQty);
    //We check for price overflow in case server owner use ruble or chinese currency with high values
    if(Price > int.MAX)Price = -1;
    string StrPrice = TraderPlusHelper.IntToCurrencyString(Price, ",");

    if(MaxStock == -1)stock = -1;
    string strstock = stock.ToString();
    if(m_QtyMultiplier > stock && MaxStock != -1 || Price == -1 || Price == 0)
    {
      m_QuantityText.SetText("#tpm_stockqty"+ " " +strstock);
      m_QuantityText.SetColor(ARGB(255,191,48,48));
      if(stock == -1)
      {
        strstock="???";
        StrPrice = "??";
      }
      else
      {
        m_InformationText.SetText("#tpm_tradeqty_over_stockqty");
      }
      m_canTrade = false;
    }
    else
    {
      if(stock == -1)strstock="???";
      m_InformationText.SetText("");
      m_QuantityText.SetText("#tpm_stockqty"+ " " +strstock);
      m_QuantityText.SetColor(ARGB(255,28,223,77));
      m_canTrade = true;
    }

    if(Price > m_playerMoney || StrPrice == "??")
    {
      m_InformationText.SetText("#tpm_cant_be_bought");
      m_BuyPriceText.SetText("#tpm_buyprice"+ " " +StrPrice);
      m_BuyPriceText.SetColor(ARGB(255,191,48,48));
      m_canTrade = false;
    }
    else
    {
      m_BuyPriceText.SetText("#tpm_buyprice"+ " " +StrPrice);
      m_BuyPriceText.SetColor(ARGB(255,28,223,77));
    }

    if(classname.Contains(GetTraderPlusConfigClient().LicenceKeyWord) && GetBankAccount() && GetBankAccount().Licences.Find(classname) != -1)
    {
      m_InformationText.SetText("#tpm_already_bought");
      m_BuyPriceText.SetText("#tpm_buyprice"+ " " +StrPrice);
      m_BuyPriceText.SetColor(ARGB(255,191,48,48));
      m_canTrade = false;
    }

    m_SellPriceText.SetText("#tpm_sellprice"+ " " +TraderPlusHelper.IntToCurrencyString(SellPrice, ","));
    m_SellPriceText.SetColor(ARGB(255,254,153,64));
    if(SellPrice == -1)
    {
      m_SellPriceText.SetText("#tpm_sellprice"+ " " +"??");
      m_SellPriceText.SetColor(ARGB(255,191,48,48));
    }

    if(m_QuantityMultiplier.GetNumItems() == 1 && MaxItemQty != 0)
    {
      RefreshAndSetQuantityMultiplierStock(TradeQty, MaxItemQty,MaxItemQty);
    }

    //we define the current product shown so we can transmit it more easely if player wants to buy it
    m_CurrentProduct.TraderID  = TraderID;
    m_CurrentProduct.Category  = category;
    m_CurrentProduct.ClassName = classname;
    m_CurrentProduct.Multiplier= m_QtyMultiplier;
    m_CurrentProduct.Quantity  = TradeQty;
    m_CurrentProduct.MaxStock  = MaxStock;
    m_CurrentProduct.Health    = health;
    m_CurrentProduct.Price     = Price;
    m_CurrentProduct.TradMode  = TRADEMODE_BUY;

    if(m_IsPlayerPreviewEnable)
    {
      UpdatePlayerClothes();
      m_PanelPlayerPreview.Show(true);
      m_PanelInventory.Show(false);
    }
  }

  //reset the product var and hide the product information panel
  void ResetProductPanel()
  {
    if ( m_previewItem )
        GetGame().ObjectDelete( m_previewItem );
    m_InformationText.SetText("");
    m_ProductInformation.Show(false);
  }

  void SetTradeMode(bool trademode)
  {
    if(trademode)
    {
      m_BuyMode = false;
      m_SellMode = true;
      m_SellPriceText.Show(true);
      if(!GetTraderPlusConfigClient().EnableShowAllPrices)
          m_BuyPriceText.Show(false);
    }
    else
    {
      m_BuyMode = true;
      m_SellMode = false;
      m_BuyPriceText.Show(true);
      if(!GetTraderPlusConfigClient().EnableShowAllPrices)
          m_SellPriceText.Show(false);
    }


  }

  //We a product is selected in inv, we'll run all the functions to check price based on stock, quantity, health, etc.. in order to make the trade ready to be reauested
  void InventoryListHandler()
  {
    SetTradeMode(TRADEMODE_SELL);

    if(!m_ProductInformation.IsVisible())
        m_ProductInformation.Show(true);

    //m_ProductInformation.Show(true);
    m_selectedRowInventory = m_InventoryListPosition;
    int tempRow = CheckifPreviousProductExist(m_CurrentProduct.ClassName,m_CurrentProduct.Health, 0);
    if(m_selectedRowInventory == -1)
    {
      if(tempRow == -1)
      {
        ResetProductPanel();
        return;
      }
      else
      {
        m_selectedRowInventory = tempRow;
      }
    }

    string classname = m_PlayerItems[m_selectedRowInventory].ClassName;
    string category  = GetTraderPlusClient().GetProductCategory(classname);
    int    health    = m_PlayerItems[m_selectedRowInventory].Health;
    UpdateItemPreview(classname);

    int slotcount = TraderPlusHelper.GetItemSlotCount(classname);
    if(slotcount == 0)
    {
      m_SlotCountText.SetText("");
    }else m_SlotCountText.SetText("#tpm_slot"+ " " +slotcount.ToString());

    //Show item health status
    GetTextAndColorRegardingHealth(health);

    //Show quantity in stock if exist
    int stock = 0;

    //if stock qty exist, we define our stock var
    stock = GetTraderPlusClient().GetStockProductFromStock(category, classname,health);

    int ItemQty,TradeQty,MaxItemQty,MaxStock=-1;
    ItemQty = m_PlayerItems[m_selectedRowInventory].Quantity;
    MaxItemQty = TraderPlusHelper.GetMaxItemQuantityClient(classname);
    #ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("Sell Product: maxitemqty:"+MaxItemQty.ToString());
		#endif

    //We define the price based on StockQty and our TradeQty var
    int Price = GetTraderPlusClient().CalculatePriceForThatItem(m_QtyMultiplier,TRADEMODE_SELL,category,classname,stock,health,MaxStock, TradeQty);
    int BuyPrice = GetTraderPlusClient().CalculatePriceForThatItem(m_QtyMultiplier,TRADEMODE_BUY,category,classname,stock,health,MaxStock, TradeQty);
    //We check for price overflow in case server owner use ruble or chinese currency with high values
    if(Price > int.MAX)Price = -1;
    string StrPrice = TraderPlusHelper.IntToCurrencyString(Price, ",");;
    if(Price == -1 || Price == 0)StrPrice = "??";
    m_SellPriceText.SetText("#tpm_sellprice"+ " " +StrPrice);
    m_SellPriceText.SetColor(ARGB(255,254,153,64));

    m_BuyPriceText.SetText("#tpm_buyprice"+ " " +TraderPlusHelper.IntToCurrencyString(BuyPrice, ","));
    m_BuyPriceText.SetColor(ARGB(255,28,223,77));
    if(BuyPrice == -1)
    {
      m_SellPriceText.SetText("#tpm_buyprice"+ " " +"??");
      m_SellPriceText.SetColor(ARGB(255,191,48,48));
    }

    /*case 1 : TradeQty > ItemQty => Itemty is too low for trading
      case 2 : (MaxStock < StockQty + TradeQty && MaxStock != -1) => Stock is to high to accept more of that specific item and stock is not unlimited
      case 3 : (MaxStock == -1 && MaxItemQty!=ItemQty && TradeQty < 0) => Stock is unlimited and ItemQty != ItemMaxQty because TradeQty is set to maxqty
    */
    if(Price == -1 || Price == 0 || TradeQty > ItemQty || (MaxStock < stock + m_QtyMultiplier && MaxStock != -1) || (MaxStock == -1 && MaxItemQty!=ItemQty && TradeQty < 0))
    {
      if(Price == -1 || Price == 0)m_InformationText.SetText("#tpm_cant_trade_item");
      if(TradeQty > ItemQty)m_InformationText.SetText("#tpm_tradeqty_over_itemqty");
      if(MaxStock < stock + m_QtyMultiplier && MaxStock != -1)m_InformationText.SetText("#tpm_tradeqty_over_stockqty");
      if(MaxStock == -1 && MaxItemQty!=ItemQty && TradeQty < 0)m_InformationText.SetText("#tpm_tradeqty_over_itemqty");
      m_QuantityText.SetText("#tpm_totalqty"+ " " +ItemQty);
      m_QuantityText.SetColor(ARGB(255,191,48,48));
      m_canTrade = false;
    }
    else
    {
      m_InformationText.SetText("");
      m_QuantityText.SetText("#tpm_totalqty"+ " " +ItemQty);
      m_QuantityText.SetColor(ARGB(255,28,223,77));
      m_canTrade = true;
    }

    if(m_QuantityMultiplier.GetNumItems() == 1)
    {
      RefreshAndSetQuantityMultiplierInventory(classname,TradeQty, MaxItemQty, ItemQty,m_PlayerItems[m_selectedRowInventory].Count);
    }

    //we define the current product shown so we can transmit it more easely if player wants to sell it
    #ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("inventory handler:"+ m_CurrentProduct.ClassName + " " + TradeQty + " qtymulti:"+m_QtyMultiplier);
		#endif

    m_CurrentProduct.TraderID  = TraderID;
    m_CurrentProduct.Category  = category;
    m_CurrentProduct.ClassName = classname;
    m_CurrentProduct.Multiplier= m_QtyMultiplier;
    m_CurrentProduct.Quantity  = TradeQty;
    if(m_QtyMultiplier > 1 && TradeQty == 0)m_CurrentProduct.Quantity = m_QtyMultiplier;
    m_CurrentProduct.Health    = health;
    m_CurrentProduct.Price     = Price;
    m_CurrentProduct.MaxStock  = MaxStock;
    m_CurrentProduct.TradMode  = TRADEMODE_SELL;
    if(m_selectedCatInventory == 3){
      m_CurrentProduct.TradMode  = TRADEMODE_SELLVEHICLE;
      m_CurrentProduct.Quantity  = m_selectedRowInventory;
    }

    #ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("inventory handler:"+ m_CurrentProduct.ClassName + " " + m_CurrentProduct.Quantity);
		#endif
  }

  //by pressing the sell button, we launch this function to attempt to send a trade reauest
  void SellHandler()
  {
    #ifdef TRADERPLUSDEBUG
    GetTraderPlusLogger().LogInfo("SellHandler");
    #endif
    if(m_selectedRowInventory == -1)return;
    if(!m_canTradeRequest)
    {
      m_InformationText.SetText("#tpm_not_too_fast");
      return;
    }
    if(m_CurrentProduct.Price == 0)
    {
      m_InformationText.SetText("#tpm_cant_trade_item");
      return;
    }
    if(m_canTrade)
    {
      if(!m_PlayerItems[m_selectedRowInventory].HasAttachments)
      {
        m_InformationText.SetText("#tpm_empty_item_first");
        return;
      }
      GetRPCManager().SendRPC("TraderPlus", "GetTradeRequest",  new Param1<ref TraderPlusProduct>(m_CurrentProduct), true, NULL);
      m_RequestTrade = true;
      m_canTrade = false;
      m_canTradeRequest = false;
    }
    else m_InformationText.SetText("#tpm_cant_trade_item");
  }

  //by pressing the buy button, we launch this function to attempt to send a trade reauest
  void BuyHandler()
  {
    #ifdef TRADERPLUSDEBUG
    GetTraderPlusLogger().LogInfo("BuyHandler");
    #endif
    if(m_selectedRowStock == -1)return;
    if(!m_canTradeRequest)
    {
      m_InformationText.SetText("#tpm_not_too_fast");
      return;
    }
    if(m_CurrentProduct.Price == 0 || m_CurrentProduct.Price == -1)
    {
      m_InformationText.SetText("#tpm_cant_trade_item");
      return;
    }
    if(m_canTrade)
    {
      GetRPCManager().SendRPC("TraderPlus", "GetTradeRequest",  new Param1<ref TraderPlusProduct>(m_CurrentProduct), true, NULL);
      m_RequestTrade = true;
      m_canTrade = false;
      m_canTradeRequest = false;
      return;
    }
    else if(m_playerMoney < m_CurrentProduct.Price)
    {
      m_InformationText.SetText("#tpm_dont_enough_money");
    }
    else
    {
      m_InformationText.SetText("#tpm_not_enough_qty_stock");
    }
  }

  //send a request to get the actual stock available for the dedicated ID
  void GetStockRequest(int id, vector pos, Object obj)
  {
    m_Trader = obj;
    TraderID = id;
    TraderPos= pos;
    GetRPCManager().SendRPC("TraderPlus", "GetStockRequestBasedOnID",  new Param1<Object>(m_Trader), true, NULL);
  }

  //once the trade reauest send, we're going to get a response afterward that will start this function based on the result
  void GetTradingResponse(int response)
  {
    //just in case they are spamming the trader, we remove a potential previous call
    GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(InventoryListHandler);

    ResetMultiplier();
    m_UIUpdate = 1.0;
    m_canTrade = true;
    m_RequestTrade = false;

    PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
    switch(response)
    {
      case TraderPlusResponse.SELL_SUCCESS:
      {
        m_InformationText.SetText("#tpm_sell_success");
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(InventoryListHandler, 100);
        player.PlayTradeSound(TRADEMODE_SELL);
      }
      break;

      case TraderPlusResponse.SELL_FAILED:
      {
        m_InformationText.SetText("#tpm_sell_failed");
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(InventoryListHandler, 100);
      }
      break;

      case TraderPlusResponse.BUY_SUCCESS:
      {
        m_InformationText.SetText("#tpm_buy_success");
        player.PlayTradeSound(TRADEMODE_BUY);
        StockListHandler();
      }
      break;

      case TraderPlusResponse.BUY_FAILED:
      {
        m_InformationText.SetText("#tpm_buy_failed");
        StockListHandler();
      }
      break;
    }
  }

  //update the UI once we got the tradingresponse
  void UIUpdate()
  {
    ResetStockItemsArrays();
    ResetPlayerItemsArray();
    UIHandle();
  }

  //reset the stock items arrays
  void ResetStockItemsArrays()
  {
    m_StockItems.Clear();
  }

  //reset the inv items arrays
  void ResetPlayerItemsArray()
  {
    m_PlayerItems.Clear();
  }

  //get the text and color based on the health
  void GetTextAndColorRegardingHealth(int health)
  {
    switch(health)
    {
      case 0:
      {
        m_HealthText.SetText("#tpm_pristine");
        m_PanelWidgetHealth.SetColor(ARGB(255,40,159,70));
      }
      break;
      case 1:
      {
        m_HealthText.SetText("#tpm_worn");
        m_PanelWidgetHealth.SetColor(ARGB(255,129,207,149));
      }
      break;
      case 2:
      {
        m_HealthText.SetText("#tpm_damaged");
        m_PanelWidgetHealth.SetColor(ARGB(255,212,149,86));
      }
      break;
      case 3:
      {
        m_HealthText.SetText("#tpm_badly_dmg");
        m_PanelWidgetHealth.SetColor(ARGB(255,161,87,13));
      }
      break;
      case 4:
      {
        m_HealthText.SetText("#tpm_ruined");
        m_PanelWidgetHealth.SetColor(ARGB(255,159,40,40));
      }
      break;
    }
  }

  //called when the current product display in the preview is a kit or contains 'kit'
  void KitHandler()
  {
    string itemType = m_CurrentProduct.ClassName;
    itemType.ToLower();
    if(itemType.Contains("_kit_"))
    {
      return;
    }else if(itemType.Contains("_kit"))
    {
      itemType.Replace("_kit","");
    }else if(itemType.Contains("kit_"))
    {
      itemType.Replace("kit_","");
    }
    UpdateItemPreview(itemType);
  }

  //update item preview when item selected in the list change
  void UpdateItemPreview(string itemType)
	{
    //we check if item is a kit, if it is, we show the kit bttn
    string tempstr = itemType;
    tempstr.ToLower();
    if(tempstr.Contains("kit"))m_BttnKit.Show(true);
    if(itemType.Contains(GetTraderPlusConfigClient().LicenceKeyWord))itemType = "Paper";
    else m_BttnKit.Show(false);

		if ( !m_MainItemPreview )
			{
				Widget preview_frame = layoutRoot.FindAnyWidget("MainItemPreview");

				if ( preview_frame )
				{
					float width;
					float height;
					preview_frame.GetSize(width, height);

					m_MainItemPreview = ItemPreviewWidget.Cast( GetGame().GetWorkspace().CreateWidget(ItemPreviewWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, ARGB(255, 255, 255, 255), 10, preview_frame) );
				}
			}

			if ( m_previewItem )
				  GetGame().ObjectDelete( m_previewItem );

			m_previewItem = EntityAI.Cast(GetGame().CreateObject( itemType, "0 0 0", true, false, true ));
      if(!m_previewItem)return;

      m_MainItemPreview.SetItem(m_previewItem);
      m_MainItemPreview.SetModelPosition( Vector( 0, 0, 0.5 ) );
      m_MainItemPreview.SetModelOrientation( vector.Zero );
      m_MainItemPreview.SetView( m_previewItem.GetViewIndex() );
	}

  void DeletePlayerPreview()
  {
    if(m_PlayerPreview)
        delete m_PlayerPreview;
    if(m_previewPlayer)
        GetGame().ObjectDelete(m_previewPlayer);
  }

  //called when pressing the remove button in the player rpeview panel
  void RemoveAllPlayerClothes()
  {
    if(!m_previewPlayer)
    {
      InitPlayerPreview();
    }
    else
    {
      CreatePlayerForPreview();
      InsertPlayerToPreview();
    }
  }

  void CreatePlayerForPreview()
  {
    if(m_previewPlayer)GetGame().ObjectDelete(m_previewPlayer);

    /*Some of you know I was having the face fucked up, thanks to Steve aka Salutesh and liquidrock, I got a fix but wtf, why ?? why should we do that for a fckg face texture !!!*/
    vector dir = GetGame().GetCurrentCameraDirection();
    dir.Normalize();
    vector pos = GetGame().GetCurrentCameraPosition() - dir * 0.5;
    pos[1] = GetGame().GetPlayer().GetPosition()[1];
    m_previewPlayer = PlayerBase.Cast(GetGame().CreateObjectEx(GetGame().GetPlayer().GetType(), pos, ECE_LOCAL|ECE_NOLIFETIME));
  }

  void InsertPlayerToPreview()
  {
    if(m_PlayerPreview)
    {
      m_PlayerPreview.SetPlayer( m_previewPlayer );
      m_PlayerPreview.UpdateItemInHands(m_previewPlayer.GetHumanInventory().GetEntityInHands());
      m_PlayerPreview.SetModelOrientation( m_CharacterOrientation );
      m_PlayerPreview.SetModelPosition( vector.Zero );
      m_PlayerPreview.SetSize( 1, 1 );  // default scale
    }
  }

  //Update the dummy clothes when we're selecting a new product in stock
  void UpdatePlayerClothes()
  {
    if(!m_previewPlayer)
    {
      InitPlayerPreview();
    }

    int id = TraderPlusHelper.GetSlotForPlayerPreview(m_CurrentProduct.ClassName);

    if(id != -1 && (TraderPlusHelper.playerAttachments[id] != "Hand" || TraderPlusHelper.playerAttachments[id] != "Shoulder" || TraderPlusHelper.playerAttachments[id] != "Melee"))
    {
      EntityAI ent = m_previewPlayer.FindAttachmentBySlotName(TraderPlusHelper.playerAttachments[id]);
      if(ent)
          GetGame().ObjectDelete(ent);
      int slotId = InventorySlots.GetSlotIdFromString(TraderPlusHelper.playerAttachments[id]);
      m_previewPlayer.GetInventory().CreateAttachmentEx(m_CurrentProduct.ClassName, slotId);
    }
    else
    {
      EntityAI current_entityInHand = m_previewPlayer.GetHumanInventory().GetEntityInHands();
      if(current_entityInHand)
          GetGame().ObjectDelete(current_entityInHand);
      EntityAI entityInHand = m_previewPlayer.GetHumanInventory().CreateInHands(m_CurrentProduct.ClassName);
    }

    InsertPlayerToPreview();
  }

  //Init the player preview to default setting, it means we display exactly the player's clothes
  void InitPlayerPreview()
	{
    if(!m_PlayerPreview)
    {
        Widget preview_frame = layoutRoot.FindAnyWidget("PlayerPreview");
        if ( preview_frame )
				{
					float width;
					float height;
					preview_frame.GetSize(width, height);

          m_PlayerPreview = PlayerPreviewWidget.Cast(GetGame().GetWorkspace().CreateWidget(PlayerPreviewWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, ARGB(255, 255, 255, 255), 10, preview_frame) );
        }
    }

    CreatePlayerForPreview();

    for(int i = 0; i < TraderPlusHelper.playerAttachments.Count();i++)
    {
      EntityAI ent = GetGame().GetPlayer().FindAttachmentBySlotName(TraderPlusHelper.playerAttachments[i]);
      if(ent)
      {
        if(TraderPlusHelper.playerAttachments[i] == "Hand")
        {
          EntityAI entityInHand = m_previewPlayer.GetHumanInventory().CreateInHands(ent.GetType());
          continue;
        }
        int slotId = InventorySlots.GetSlotIdFromString(TraderPlusHelper.playerAttachments[i]);
        m_previewPlayer.GetInventory().CreateAttachmentEx(ent.GetType(), slotId);
      }
    }

    InsertPlayerToPreview();
	}

  //Get player's money based on the accepted currencies by the trader
  int GetPlayerMoney()
  {
      PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
      if(!player)return 0;

      int amount = 0;
      float qty = 0.0;
      int value = 0;

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
                    TStringArray acceptedCurrencyArray = new TStringArray;
                    string currency = GetTraderPlusConfigClient().CurrenciesAccepted.Get(TraderID);
        						currency.Split( ",", acceptedCurrencyArray );
                    if(acceptedCurrencyArray.Count() == 0)
                    {
                      qty = TraderPlusHelper.GetItemAmount(item);
                      value = GetTraderPlusConfigClient().MoneyValue.Get(j);
                      amount += (value * qty);
                    }
                    else
                    {
                      for(int l=0;l<acceptedCurrencyArray.Count();l++)
                      {
                        if(className == acceptedCurrencyArray[l])
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
      }
      return amount;
  }

  override void OnShow()
	{
		super.OnShow();
		PPEffects.SetBlurMenu(0.5);
		GetGame().GetInput().ChangeGameFocus(1);
    GetGame().GetUIManager().ShowUICursor(true);
    GetGame().GetMission().GetHud().Show(false);
    GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
		SetFocus( layoutRoot );
	}

	override void OnHide()
	{
		super.OnHide();
		PPEffects.SetBlurMenu(0);
    GetGame().GetUIManager().ShowUICursor(false);
    GetGame().GetMission().GetHud().Show(true);
    GetGame().GetMission().PlayerControlEnable(false);
		GetGame().GetInput().ResetGameFocus();
    if ( m_previewItem )
        GetGame().ObjectDelete( m_previewItem );
    if (m_previewPlayer)
        GetGame().ObjectDelete( m_previewPlayer );
		Close();
	}
}
