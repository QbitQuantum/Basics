void CMainFrame::InitializeRibbon()
{
    CString strTemp;
    strTemp.LoadString(IDS_RIBBON_FILE);

    // Load panel images:
    m_PanelImages.SetImageSize(CSize(16, 16));
    m_PanelImages.Load(IDB_BUTTONS);

    // Init main button:
    m_MainButton.SetImage(IDB_MAIN_AMT);
    m_MainButton.SetText(_T("\nf"));
    m_MainButton.SetToolTipText(strTemp);

    m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
    CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_AMT_FILESMALL, IDB_AMT_FILELARGE);

    strTemp.LoadString(IDS_RIBBON_NEW);
    pMainPanel->Add(new CMFCRibbonButton(ID_EDIT_REFRESH, _T("Refresh\nr"), 25, 14));
    pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

    strTemp.LoadString(IDS_RIBBON_PRINT);
    CMFCRibbonButton* pBtnPrint = new CMFCRibbonButton(ID_FILE_PRINT, strTemp, 6, 6);
    pBtnPrint->SetKeys(_T("p"), _T("w"));
    strTemp.LoadString(IDS_RIBBON_PRINT_LABEL);
    pBtnPrint->AddSubItem(new CMFCRibbonLabel(strTemp));
    strTemp.LoadString(IDS_RIBBON_PRINT);
    pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT, strTemp, 7, 7, TRUE));
    strTemp.LoadString(IDS_RIBBON_PRINT_SETUP);
    pBtnPrint->AddSubItem(new CMFCRibbonButton(ID_FILE_PRINT_SETUP, strTemp, 11, 11, TRUE));
    pMainPanel->Add(pBtnPrint);

    pMainPanel->Add(new CMFCRibbonSeparator(TRUE));
    pMainPanel->Add(new CMFCRibbonButton(ID_FILE_LOGOUT, _T("&Logout"), 0, 0, TRUE));
    //pMainPanel->Add(new CMFCRibbonSeparator(TRUE));

    //strTemp.LoadString(IDS_RIBBON_CLOSE);
    //pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));

    strTemp.LoadString(IDS_RIBBON_RECENT_DOCS);
    pMainPanel->AddRecentFilesList(strTemp);

    strTemp.LoadString(IDS_RIBBON_EXIT);
    pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));

    // Add "Home" category with "Clipboard" panel:
    strTemp.LoadString(IDS_RIBBON_HOME);
    CMFCRibbonCategory* pCategoryHome = m_wndRibbonBar.AddCategory(strTemp, IDB_AMT_WRITESMALL, IDB_AMT_WRITELARGE);

    // Create "Clipboard" panel:
    strTemp.LoadString(IDS_RIBBON_CLIPBOARD);
    CMFCRibbonPanel* pPanelClipboard = pCategoryHome->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

    strTemp.LoadString(IDS_RIBBON_PASTE);
    CMFCRibbonButton* pBtnPaste = new CMFCRibbonButton(ID_EDIT_PASTE, strTemp, 0, 0);
    pPanelClipboard->Add(pBtnPaste);

    strTemp.LoadString(IDS_RIBBON_CUT);
    pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_CUT, strTemp, 1));
    strTemp.LoadString(IDS_RIBBON_COPY);
    pPanelClipboard->Add(new CMFCRibbonButton(ID_EDIT_COPY, strTemp, 2));

    // Create "Filter" panel:
    CMFCRibbonPanel* pPanelFilter = pCategoryHome->AddPanel(_T("Filter"));
    pPanelFilter->Add(new CMFCRibbonButton(ID_EDIT_SHOW_ALL, _T("Show All\ns"), 16));
    pPanelFilter->AddSeparator();
    pPanelFilter->Add(new CMFCRibbonCheckBox(ID_EDIT_SHOW_ORPHANS, _T("Show Orphans\no")));
    pPanelFilter->Add(new CMFCRibbonCheckBox(ID_EDIT_SHOW_NOT_MATCHING, _T("Show Differences\nd")));
    pPanelFilter->Add(new CMFCRibbonCheckBox(ID_EDIT_SHOW_MATCHING, _T("Show Matching\nm")));

    CMFCRibbonPanel* pPanelSelection = pCategoryHome->AddPanel(_T("Selection"));
    strTemp.LoadString(IDS_RIBBON_SELECTALL);
    pPanelSelection->Add(new CMFCRibbonButton(ID_EDIT_SELECT_ALL, strTemp, 21));
    pPanelSelection->Add(new CMFCRibbonButton(ID_EDIT_CLEARALL, _T("Clear All\na"), 22));
    pPanelSelection->Add(new CMFCRibbonButton(ID_EDIT_EXPANDALL, _T("Expand All"), 23));
    pPanelSelection->AddSeparator();
    pPanelSelection->Add(new CMFCRibbonButton(ID_EDIT_ADDTOREP, _T("Migrate\nm"), 14));

    CMFCRibbonPanel* pPanelView = pCategoryHome->AddPanel(_T("View"));
    pPanelView->Add(new CMFCRibbonCheckBox(ID_VIEW_CRLF, _T("CR/LF")));
    pPanelView->Add(new CMFCRibbonCheckBox(ID_VIEW_WHITESPACE, _T("Whitespace")));

    CMFCRibbonPanel* pPanelDiferences = pCategoryHome->AddPanel(_T("Differences"));
    pPanelDiferences->Add(new CMFCRibbonButton(ID_DIFFERENCES_PREVIOUS, _T("Previous\nn")));
    pPanelDiferences->Add(new CMFCRibbonButton(ID_DIFFERENCES_NEXT, _T("Next\np")));

    CMFCRibbonPanel* pPanelDependees = pCategoryHome->AddPanel(_T("Dependees"));
    pPanelDependees->Add(new CMFCRibbonButton(ID_DEPENDEES_FINDSERVICES, _T("Find Services")));
    pPanelDependees->Add(new CMFCRibbonButton(ID_DEPENDEES_CALCULATEDEPENDENCIES, _T("Recalculate Cache")));
    pPanelDependees->Add(new CMFCRibbonButton(ID_DEPENDEES_CALCULATECROSSREFERENCE, _T("Calculate Crossreference")));
    pPanelDependees->AddSeparator();
    pPanelDependees->Add(new CMFCRibbonButton(ID_DEPENDEES_SYNCFROMSELECTION, _T("Sync From Selection")));
    pPanelDependees->Add(new CMFCRibbonButton(ID_DEPENDEES_SYNCTOSELECTION, _T("Sync To Selection")));
    pPanelDependees->Add(new CMFCRibbonButton(ID_DEPENDEES_COPYCROSSREFERENCE, _T("Copy Crossreference")));

    CMFCRibbonPanel* pPanelAdvanced = pCategoryHome->AddPanel(_T("Advanced"));
    pPanelAdvanced->Add(new CMFCRibbonCheckBox(ID_EDIT_MODULE_CHECKSUM, _T("Module Checksums\nu")));

    // Add elements to the right side of tabs:
    strTemp.LoadString(IDS_RIBBON_STYLE);
    CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(-1, strTemp, -1, -1);

    pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* No default command */, TRUE /* Right align */);

    strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
    pVisualStyleButton->SetToolTipText(strTemp);
    strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
    pVisualStyleButton->SetDescription(strTemp);
    m_wndRibbonBar.AddToTabs(pVisualStyleButton);

    // Add quick access toolbar commands:
    CList<UINT, UINT> lstQATCmds;

    lstQATCmds.AddTail(ID_EDIT_REFRESH);
    lstQATCmds.AddTail(ID_FILE_LOGOUT);
    lstQATCmds.AddTail(ID_FILE_PRINT);

    m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);
    m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon(0)));
}