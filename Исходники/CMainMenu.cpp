CMainMenu::CMainMenu(CGUI* pManager)
{
    m_pNewsBrowser = new CNewsBrowser();

    ulPreviousTick = GetTickCount32();
    m_pHoveredItem = NULL;
    m_iMoveStartPos = 0;

    // Initialize
    m_pManager = pManager;
    m_bIsVisible = false;
    m_bIsFullyVisible = false;
    m_bIsIngame = true;
    //    m_bIsInSubWindow = false;
    m_bStarted = false;
    m_fFader = 0;
    m_ucFade = FADE_INVISIBLE;

    // Adjust window size to resolution
    CVector2D ScreenSize = m_pManager->GetResolution();
    m_ScreenSize = ScreenSize;

    int iBackgroundX = 0;
    int iBackgroundY = 0;
    int iBackgroundSizeX = ScreenSize.fX;
    int iBackgroundSizeY;

    // First let's work out our x and y offsets
    if (ScreenSize.fX > ScreenSize.fY)            // If the monitor is a normal landscape one
    {
        float iRatioSizeY = ScreenSize.fY / NATIVE_RES_Y;
        m_iMenuSizeX = NATIVE_RES_X * iRatioSizeY;
        m_iMenuSizeY = ScreenSize.fY;
        m_iXOff = (ScreenSize.fX - m_iMenuSizeX) * 0.5f;
        m_iYOff = 0;

        float iRatioSizeX = ScreenSize.fX / NATIVE_RES_X;
        iBackgroundSizeX = ScreenSize.fX;
        iBackgroundSizeY = NATIVE_BG_Y * iRatioSizeX;
    }
    else            // Otherwise our monitor is in a portrait resolution, so we cant fill the background by y
    {
        float iRatioSizeX = ScreenSize.fX / NATIVE_RES_X;
        m_iMenuSizeY = NATIVE_RES_Y * iRatioSizeX;
        m_iMenuSizeX = ScreenSize.fX;
        m_iXOff = 0;
        m_iYOff = (ScreenSize.fY - m_iMenuSizeY) * 0.5f;

        iBackgroundY = m_iYOff;
        iBackgroundSizeX = m_iMenuSizeX;
        iBackgroundSizeY = NATIVE_BG_Y * iRatioSizeX;
    }
    // First create our filler black background image, which covers the whole screen
    m_pFiller = reinterpret_cast<CGUIStaticImage*>(pManager->CreateStaticImage());
    m_pFiller->LoadFromFile(CORE_MTA_FILLER);
    m_pFiller->SetVisible(false);
    m_pFiller->MoveToBack();
    m_pFiller->SetZOrderingEnabled(false);
    m_pFiller->SetAlwaysOnTop(true);
    m_pFiller->MoveToBack();
    m_pFiller->SetSize(CVector2D(ScreenSize.fX, iBackgroundY), false);

    // Background image
    m_pBackground = reinterpret_cast<CGUIStaticImage*>(pManager->CreateStaticImage());
    m_pBackground->LoadFromFile(CORE_MTA_STATIC_BG);
    m_pBackground->SetProperty("InheritsAlpha", "False");
    m_pBackground->SetPosition(CVector2D(iBackgroundX, iBackgroundY), false);
    m_pBackground->SetSize(CVector2D(iBackgroundSizeX, iBackgroundSizeY), false);
    m_pBackground->SetZOrderingEnabled(false);
    m_pBackground->SetAlwaysOnTop(true);
    m_pBackground->MoveToBack();
    m_pBackground->SetAlpha(0);
    m_pBackground->SetVisible(false);

    m_pFiller2 = reinterpret_cast<CGUIStaticImage*>(pManager->CreateStaticImage());
    m_pFiller2->LoadFromFile(CORE_MTA_FILLER);
    m_pFiller2->SetVisible(false);
    m_pFiller2->SetZOrderingEnabled(false);
    m_pFiller2->SetAlwaysOnTop(true);
    m_pFiller2->MoveToBack();
    m_pFiller2->SetPosition(CVector2D(0, iBackgroundY + iBackgroundSizeY));
    m_pFiller2->SetSize(ScreenSize, false);

    m_pCanvas = reinterpret_cast<CGUIScrollPane*>(pManager->CreateScrollPane());
    m_pCanvas->SetProperty("ContentPaneAutoSized", "False");
    m_pCanvas->SetPosition(CVector2D(m_iXOff, m_iYOff), false);
    m_pCanvas->SetSize(CVector2D(m_iMenuSizeX, m_iMenuSizeY), false);
    m_pCanvas->SetZOrderingEnabled(false);
    m_pCanvas->SetAlwaysOnTop(true);
    m_pCanvas->MoveToBack();
    m_pCanvas->SetVisible(false);

    // Create our MTA logo
    CVector2D logoSize = CVector2D((NATIVE_LOGO_X / NATIVE_RES_X) * m_iMenuSizeX, (NATIVE_LOGO_Y / NATIVE_RES_Y) * m_iMenuSizeY);
    m_pLogo = reinterpret_cast<CGUIStaticImage*>(pManager->CreateStaticImage(m_pCanvas));
    m_pLogo->LoadFromFile(CORE_MTA_LOGO);
    m_pLogo->SetProperty("InheritsAlpha", "False");
    m_pLogo->SetSize(logoSize, false);
    m_pLogo->SetPosition(CVector2D(0.5f * m_iMenuSizeX - logoSize.fX / 2, 0.365f * m_iMenuSizeY - logoSize.fY / 2), false);
    m_pLogo->SetZOrderingEnabled(false);

    // Create the image showing the version number
    m_pVersion = reinterpret_cast<CGUIStaticImage*>(pManager->CreateStaticImage());
    m_pVersion->LoadFromFile(CORE_MTA_VERSION);
    m_pVersion->SetParent(m_pCanvas);
    m_pVersion->SetPosition(CVector2D(0.845f, 0.528f), true);
    m_pVersion->SetSize(CVector2D((32 / NATIVE_RES_X) * m_iMenuSizeX, (32 / NATIVE_RES_Y) * m_iMenuSizeY), false);
    m_pVersion->SetProperty("InheritsAlpha", "False");

    float fBase = 0.613f;
    float fGap = 0.043f;
    // Our disconnect item is shown/hidden dynamically, so we store it seperately
    m_pDisconnect = CreateItem(MENU_ITEM_DISCONNECT, "menu_disconnect.png", CVector2D(0.168f, fBase + fGap * 0));
    m_pDisconnect->image->SetVisible(false);

    // Create the menu items
    // Filepath, Relative position, absolute native size
    // And the font for the graphics is ?
    m_menuItems.push_back(CreateItem(MENU_ITEM_QUICK_CONNECT, "menu_quick_connect.png", CVector2D(0.168f, fBase + fGap * 0)));
    m_menuItems.push_back(CreateItem(MENU_ITEM_BROWSE_SERVERS, "menu_browse_servers.png", CVector2D(0.168f, fBase + fGap * 1)));
    m_menuItems.push_back(CreateItem(MENU_ITEM_HOST_GAME, "menu_host_game.png", CVector2D(0.168f, fBase + fGap * 2)));
    m_menuItems.push_back(CreateItem(MENU_ITEM_MAP_EDITOR, "menu_map_editor.png", CVector2D(0.168f, fBase + fGap * 3)));
    m_menuItems.push_back(CreateItem(MENU_ITEM_SETTINGS, "menu_settings.png", CVector2D(0.168f, fBase + fGap * 4)));
    m_menuItems.push_back(CreateItem(MENU_ITEM_ABOUT, "menu_about.png", CVector2D(0.168f, fBase + fGap * 5)));
    m_menuItems.push_back(CreateItem(MENU_ITEM_QUIT, "menu_quit.png", CVector2D(0.168f, fBase + fGap * 6)));

    // We store the position of the top item, and the second item.  These will be useful later
    float fFirstItemSize = m_menuItems.front()->image->GetSize(false).fY;
    float fSecondItemSize = m_menuItems[1]->image->GetSize(false).fY;

    m_iFirstItemCentre = (m_menuItems.front()->image)->GetPosition().fY + fFirstItemSize * 0.5f;
    m_iSecondItemCentre = (m_menuItems[1]->image)->GetPosition().fY + fSecondItemSize * 0.5f;

    // Store some mouse over bounding box positions
    m_menuAX = (0.168f * m_iMenuSizeX) + m_iXOff;                                                                      // Left side of the items
    m_menuAY = m_iFirstItemCentre - fFirstItemSize * (CORE_MTA_HOVER_SCALE / CORE_MTA_NORMAL_SCALE) * 0.5f;            // Top side of the items
    m_menuBX = m_menuAX + ((390 / NATIVE_RES_X) * m_iMenuSizeX);            // Right side of the items. We add the longest picture (browse_servers)
    m_menuAY += BODGE_FACTOR_1;

    m_pMenuArea = reinterpret_cast<CGUIStaticImage*>(pManager->CreateStaticImage(m_pCanvas));
    m_pMenuArea->LoadFromFile(CORE_MTA_FILLER);
    m_pMenuArea->SetPosition(CVector2D(m_menuAX - m_iXOff, m_menuAY - m_iYOff) + BODGE_FACTOR_5, false);
    m_pMenuArea->SetSize(CVector2D(m_menuBX - m_menuAX, m_menuBY - m_menuAY) + BODGE_FACTOR_6, false);
    m_pMenuArea->SetAlpha(0);
    m_pMenuArea->SetZOrderingEnabled(false);
    m_pMenuArea->SetClickHandler(GUI_CALLBACK(&CMainMenu::OnMenuClick, this));
    m_pMenuArea->SetMouseEnterHandler(GUI_CALLBACK(&CMainMenu::OnMenuEnter, this));
    m_pMenuArea->SetMouseLeaveHandler(GUI_CALLBACK(&CMainMenu::OnMenuExit, this));

    float fDrawSizeX = (365 / NATIVE_RES_X) * m_iMenuSizeX;            // Right aligned
    float fDrawSizeY = (52 / NATIVE_RES_Y) * m_iMenuSizeY;
    float fDrawPosX = 0.83f * m_iMenuSizeX - fDrawSizeX;
    float fDrawPosY = 0.60f * m_iMenuSizeY;
    m_pLatestNews = reinterpret_cast<CGUIStaticImage*>(pManager->CreateStaticImage());
    m_pLatestNews->LoadFromFile(CORE_MTA_LATEST_NEWS);
    m_pLatestNews->SetParent(m_pCanvas);
    m_pLatestNews->SetPosition(CVector2D(fDrawPosX, fDrawPosY), false);
    m_pLatestNews->SetSize(CVector2D(fDrawSizeX, fDrawSizeY), false);
    m_pLatestNews->SetProperty("InheritsAlpha", "False");
    m_pLatestNews->SetVisible(false);

    // Create news item stuff
    fDrawPosX -= 25;
    fDrawPosY += fDrawSizeY - 8;
    for (uint i = 0; i < CORE_MTA_NEWS_ITEMS; i++)
    {
        fDrawPosY += 20;
        // Create our shadow and item
        CGUILabel* pItemShadow = reinterpret_cast<CGUILabel*>(m_pManager->CreateLabel(m_pCanvas, " "));
        CGUILabel* pItem = reinterpret_cast<CGUILabel*>(m_pManager->CreateLabel(m_pCanvas, " "));

        pItem->SetFont("sans");
        pItemShadow->SetFont("sans");
        pItem->SetHorizontalAlign(CGUI_ALIGN_RIGHT);
        pItemShadow->SetHorizontalAlign(CGUI_ALIGN_RIGHT);

        pItem->SetSize(CVector2D(fDrawSizeX, 14), false);
        pItemShadow->SetSize(CVector2D(fDrawSizeX, 15), false);

        pItem->SetPosition(CVector2D(fDrawPosX, fDrawPosY), false);
        pItemShadow->SetPosition(CVector2D(fDrawPosX + 1, fDrawPosY + 1), false);

        pItemShadow->SetTextColor(112, 112, 112);

        // Set the handlers
        pItem->SetClickHandler(GUI_CALLBACK(&CMainMenu::OnNewsButtonClick, this));

        // Store the item in the array
        m_pNewsItemLabels[i] = pItem;
        m_pNewsItemShadowLabels[i] = pItemShadow;

        // Create our date label
        fDrawPosY += 15;
        CGUILabel* pItemDate = reinterpret_cast<CGUILabel*>(m_pManager->CreateLabel(m_pCanvas, " "));

        pItemDate->SetFont("default-small");
        pItemDate->SetHorizontalAlign(CGUI_ALIGN_RIGHT);

        pItemDate->SetSize(CVector2D(fDrawSizeX, 13), false);
        pItemDate->SetPosition(CVector2D(fDrawPosX, fDrawPosY), false);

        m_pNewsItemDateLabels[i] = pItemDate;

        // Create 'NEW' sticker
        CGUILabel*& pLabel = m_pNewsItemNEWLabels[i];
        pLabel = reinterpret_cast<CGUILabel*>(pManager->CreateLabel(m_pCanvas, "NEW"));
        pLabel->SetFont("default-small");
        pLabel->SetTextColor(255, 0, 0);
        pLabel->AutoSize(pLabel->GetText().c_str());
        pLabel->SetAlpha(0.7f);
        pLabel->SetVisible(false);
    }

    m_pLogo->MoveToBack();

    // Submenus
    m_QuickConnect.SetVisible(false);
    m_ServerBrowser.SetVisible(false);
    m_ServerInfo.Hide();
    m_Settings.SetVisible(false);
    m_Credits.SetVisible(false);
    m_pNewsBrowser->SetVisible(false);

    // We're not ingame
    SetIsIngame(false);

    // Store the pointer to the graphics subsystem
    m_pGraphics = CGraphics::GetSingletonPtr();

    // Load the server lists
    CXMLNode* pConfig = CCore::GetSingletonPtr()->GetConfig();
    m_ServerBrowser.LoadServerList(pConfig->FindSubNode(CONFIG_NODE_SERVER_FAV), CONFIG_FAVOURITE_LIST_TAG, m_ServerBrowser.GetFavouritesList());
    m_ServerBrowser.LoadServerList(pConfig->FindSubNode(CONFIG_NODE_SERVER_REC), CONFIG_RECENT_LIST_TAG, m_ServerBrowser.GetRecentList());
    m_ServerBrowser.LoadServerList(pConfig->FindSubNode(CONFIG_NODE_SERVER_HISTORY), CONFIG_HISTORY_LIST_TAG, m_ServerBrowser.GetHistoryList());

    // Remove unused node
    if (CXMLNode* pOldNode = pConfig->FindSubNode(CONFIG_NODE_SERVER_INT))
        pConfig->DeleteSubNode(pOldNode);

#ifdef CI_BUILD
    // Add feature branch alert
    m_pFeatureBranchAlertTexture.reset(reinterpret_cast<CGUITexture*>(m_pManager->CreateTexture()));
    std::int32_t buffer = 0xFFFF0000;
    m_pFeatureBranchAlertTexture->LoadFromMemory(&buffer, 1, 1);            // HACK: Load red dot

    m_pFeatureBranchAlertImage.reset(reinterpret_cast<CGUIStaticImage*>(m_pManager->CreateStaticImage(m_pBackground)));
    m_pFeatureBranchAlertImage->LoadFromTexture(m_pFeatureBranchAlertTexture.get());
    m_pFeatureBranchAlertImage->SetPosition({0.0f, 0.0f}, false);
    m_pFeatureBranchAlertImage->SetSize({ScreenSize.fX, 35.0f});

    m_pFeatureBranchAlertLabel.reset(reinterpret_cast<CGUILabel*>(m_pManager->CreateLabel(m_pFeatureBranchAlertImage.get())));
    m_pFeatureBranchAlertLabel->SetText(
        _("You are using a feature-branch build! This is a test build only which cannot be used to connect to public servers!"));
    m_pFeatureBranchAlertLabel->SetPosition({0.0f, 0.0f}, false);
    m_pFeatureBranchAlertLabel->SetSize({ScreenSize.fX, 35.0f});
    m_pFeatureBranchAlertLabel->SetFont("clear-normal");
    m_pFeatureBranchAlertLabel->SetHorizontalAlign(CGUI_ALIGN_HORIZONTALCENTER);
    m_pFeatureBranchAlertLabel->SetVerticalAlign(CGUI_ALIGN_VERTICALCENTER);
#endif
}