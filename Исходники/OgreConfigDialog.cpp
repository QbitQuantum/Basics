    BOOL ConfigDialog::DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
#endif
    {
        HWND hwndDlgItem;
        static RenderSystemList* lstRend;
        RenderSystemList::iterator pRend;
        static ConfigOptionMap opts;
        String err;

        int i, sel, savedSel;

        switch (iMsg)
        {

        case WM_INITDIALOG:
            // Load saved settings
            dlg->mSelectedRenderSystem = Root::getSingleton().getRenderSystem();
            // Get all render systems
            lstRend = Root::getSingleton().getAvailableRenderers();
            pRend = lstRend->begin();            
            i = 0;
            while (pRend != lstRend->end())
            {
                hwndDlgItem = GetDlgItem(hDlg, IDC_CBO_RENDERSYSTEM);

                SendMessage(hwndDlgItem, CB_ADDSTRING, 0,
                    (LPARAM)(char*)(*pRend)->getName().c_str());

                if (*pRend == dlg->mSelectedRenderSystem)
                {
                    // Select
                    SendMessage(hwndDlgItem, CB_SETCURSEL, (WPARAM)i, 0);
                    // Refresh Options
                    // Get options from render system
                    opts = (*pRend)->getConfigOptions();
                    // Reset list box
                    hwndDlgItem = GetDlgItem(hDlg, IDC_LST_OPTIONS);
                    //SendMessage(hwndDlgItem, LB_RESETCONTENT, 0, 0);
                    // Iterate through options
                    ConfigOptionMap::iterator pOpt = opts.begin();
                    String strLine;
                    while( pOpt!= opts.end() )
                    {
                        strLine = pOpt->second.name + ": " + pOpt->second.currentValue;
                        SendMessage(hwndDlgItem, LB_ADDSTRING, 0, (LPARAM)strLine.c_str());
                        ++pOpt;
                    }
                }

                ++pRend;
                ++i;
            }

            // Center myself
            int x, y, screenWidth, screenHeight;
            RECT rcDlg;
            GetWindowRect(hDlg, &rcDlg);
            screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
            screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

            x = (screenWidth / 2) - ((rcDlg.right - rcDlg.left) / 2);
            y = (screenHeight / 2) - ((rcDlg.bottom - rcDlg.top) / 2);

            MoveWindow(hDlg, x, y, (rcDlg.right - rcDlg.left),
                (rcDlg.bottom - rcDlg.top), TRUE);

            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case IDC_CBO_RENDERSYSTEM:
                hwndDlgItem = GetDlgItem(hDlg, IDC_CBO_RENDERSYSTEM);
                sel = SendMessage( hwndDlgItem, CB_GETCOUNT, 0, 0 );

                if (HIWORD(wParam) == CBN_SELCHANGE )
                {
                    // RenderSystem selected
                    // Get selected index
                    hwndDlgItem = GetDlgItem(hDlg, IDC_CBO_RENDERSYSTEM);
                    sel = SendMessage(hwndDlgItem, CB_GETCURSEL,0,0);
                    if (sel != -1)
                    {
                        // Get RenderSystem selected
                        pRend = lstRend->begin();
                        dlg->mSelectedRenderSystem = pRend[sel];
                        // refresh options
                        // Get options from render system
                        opts = pRend[sel]->getConfigOptions();
                        // Reset list box
                        hwndDlgItem = GetDlgItem(hDlg, IDC_LST_OPTIONS);
                        SendMessage(hwndDlgItem, LB_RESETCONTENT, 0, 0);
                        // Iterate through options
                        ConfigOptionMap::iterator pOpt = opts.begin();
                        String strLine;
                        while (pOpt!=opts.end())
                        {
                            strLine = pOpt->second.name + ": " + pOpt->second.currentValue;
                            SendMessage(hwndDlgItem, LB_ADDSTRING, 0, (LPARAM)strLine.c_str());
                            ++pOpt;
                        }
                    }                    
                }

                return TRUE;

            case IDC_LST_OPTIONS:
                if (HIWORD(wParam) == LBN_SELCHANGE)
                {
                    // Selection in list box of options changed
                    // Update combo and label in edit section
                    hwndDlgItem = GetDlgItem(hDlg, IDC_LST_OPTIONS);
                    sel = SendMessage(hwndDlgItem, LB_GETCURSEL, 0, 0);
                    if (sel != -1)
                    {
                        ConfigOptionMap::iterator pOpt = opts.begin();
                        for (i = 0; i < sel; i++)
                            ++pOpt;
                        // Set label text
                        hwndDlgItem = GetDlgItem(hDlg, IDC_LBL_OPTION);
                        SetWindowText(hwndDlgItem, pOpt->second.name.c_str());
                        // Set combo options
                        hwndDlgItem = GetDlgItem(hDlg, IDC_CBO_OPTION);
                        SendMessage(hwndDlgItem, CB_RESETCONTENT, 0, 0);
                        StringVector::iterator pPoss = pOpt->second.possibleValues.begin();
                        i = 0;
                        while (pPoss!=pOpt->second.possibleValues.end())
                        {
                            SendMessage(hwndDlgItem, CB_ADDSTRING, 0, (LPARAM)pPoss[0].c_str());
                            if (pPoss[0] == pOpt->second.currentValue)
                                // Select current value
                                SendMessage(hwndDlgItem, CB_SETCURSEL, (WPARAM)i, 0);
                            ++pPoss;
                            ++i;
                        }
                        // Enable/disable combo depending on (not)immutable
                        EnableWindow(hwndDlgItem, !(pOpt->second.immutable));
                    }
                }

                return TRUE;

            case IDC_CBO_OPTION:
                if (HIWORD(wParam) == CBN_SELCHANGE)
                {
                    // Updated an option
                    // Get option
                    hwndDlgItem = GetDlgItem(hDlg, IDC_LST_OPTIONS);
                    sel = SendMessage(hwndDlgItem, LB_GETCURSEL, 0, 0);
                    savedSel = sel;
                    ConfigOptionMap::iterator pOpt = opts.begin();
                    for (i = 0; i < sel; i++)
                        ++pOpt;
                    // Get selected value
                    hwndDlgItem = GetDlgItem(hDlg, IDC_CBO_OPTION);
                    sel = SendMessage(hwndDlgItem, CB_GETCURSEL, 0, 0);

                    if (sel != -1)
                    {
                        StringVector::iterator pPoss = pOpt->second.possibleValues.begin();

                        // Set option
                        dlg->mSelectedRenderSystem->setConfigOption(
                            pOpt->second.name, pPoss[sel]);
                        // Re-retrieve options
                        opts = dlg->mSelectedRenderSystem->getConfigOptions();

                        // Reset options list box
                        hwndDlgItem = GetDlgItem(hDlg, IDC_LST_OPTIONS);
                        SendMessage(hwndDlgItem, LB_RESETCONTENT, 0, 0);
                        // Iterate through options
                        pOpt = opts.begin();
                        String strLine;
                        while (pOpt!=opts.end())
                        {
                            strLine = pOpt->second.name + ": " + pOpt->second.currentValue;
                            SendMessage(hwndDlgItem, LB_ADDSTRING, 0, (LPARAM)strLine.c_str());
                            ++pOpt;
                        }
                        // Select previously selected item
                        SendMessage(hwndDlgItem, LB_SETCURSEL, savedSel, 0);
                    }

                }
                return TRUE;

            case IDOK:
                // Set render system
                if (!dlg->mSelectedRenderSystem)
                {
                    MessageBox(NULL, "Please choose a rendering system.", "OGRE", MB_OK | MB_ICONEXCLAMATION);
                    return TRUE;
                }
                err = dlg->mSelectedRenderSystem->validateConfigOptions();
                if (err.length() > 0)
                {
                    // refresh options incase updated by validation
                    // Get options from render system
                    opts = dlg->mSelectedRenderSystem->getConfigOptions();
                    // Reset list box
                    hwndDlgItem = GetDlgItem(hDlg, IDC_LST_OPTIONS);
                    SendMessage(hwndDlgItem, LB_RESETCONTENT, 0, 0);
                    // Iterate through options
                    ConfigOptionMap::iterator pOpt = opts.begin();
                    String strLine;
                    while (pOpt!=opts.end())
                    {
                        strLine = pOpt->second.name + ": " + pOpt->second.currentValue;
                        SendMessage(hwndDlgItem, LB_ADDSTRING, 0, (LPARAM)strLine.c_str());
                        ++pOpt;
                    }
                    MessageBox(NULL, err.c_str(), "OGRE", MB_OK | MB_ICONEXCLAMATION);
                    return TRUE;
                }

                Root::getSingleton().setRenderSystem(dlg->mSelectedRenderSystem);

                EndDialog(hDlg, TRUE);
                return TRUE;

            case IDCANCEL:
                EndDialog(hDlg, FALSE);
                return TRUE;
            }
        }

        return FALSE;
    }