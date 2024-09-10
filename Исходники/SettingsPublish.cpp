INT_PTR SettingsPublish::ProcMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hwndTemp;

    switch(message)
    {
        case WM_INITDIALOG:
            {
                LocalizeWindow(hwnd);

                RECT serviceRect, saveToFileRect;
                GetWindowRect(GetDlgItem(hwnd, IDC_SERVICE), &serviceRect);
                GetWindowRect(GetDlgItem(hwnd, IDC_SAVEPATH), &saveToFileRect);

                data.fileControlOffset = saveToFileRect.top-serviceRect.top;

                //--------------------------------------------

                hwndTemp = GetDlgItem(hwnd, IDC_MODE);
                SendMessage(hwndTemp, CB_ADDSTRING, 0, (LPARAM)Str("Settings.Publish.Mode.LiveStream"));
                SendMessage(hwndTemp, CB_ADDSTRING, 0, (LPARAM)Str("Settings.Publish.Mode.FileOnly"));

                int mode = LoadSettingComboInt(hwndTemp, TEXT("Publish"), TEXT("Mode"), 0, 2);
                data.mode = mode;

                //--------------------------------------------

                hwndTemp = GetDlgItem(hwnd, IDC_SERVICE);
                int itemId = (int)SendMessage(hwndTemp, CB_ADDSTRING, 0, (LPARAM)TEXT("Custom"));
                SendMessage(hwndTemp, CB_SETITEMDATA, itemId, 0);

                UINT numServices = 0;

                XConfig serverData;
                if(serverData.Open(TEXT("services.xconfig")))
                {
                    XElement *services = serverData.GetElement(TEXT("services"));
                    if(services)
                    {
                        numServices = services->NumElements();

                        for(UINT i=0; i<numServices; i++)
                        {
                            XElement *service = services->GetElementByID(i);
                            itemId = (int)SendMessage(hwndTemp, CB_ADDSTRING, 0, (LPARAM)service->GetName());
                            SendMessage(hwndTemp, CB_SETITEMDATA, itemId, service->GetInt(TEXT("id")));
                        }
                    }
                }

                int serviceID = AppConfig->GetInt(TEXT("Publish"), TEXT("Service"), 0);

                if(mode != 0) ShowWindow(hwndTemp, SW_HIDE);

                //--------------------------------------------

                hwndTemp = GetDlgItem(hwnd, IDC_PLAYPATH);
                LoadSettingEditString(hwndTemp, TEXT("Publish"), TEXT("PlayPath"), NULL);
                if(mode != 0) ShowWindow(hwndTemp, SW_HIDE);

                if(serviceID == 0) //custom
                {
                    ShowWindow(GetDlgItem(hwnd, IDC_SERVERLIST), SW_HIDE);
                    hwndTemp = GetDlgItem(hwnd, IDC_URL);
                    LoadSettingEditString(hwndTemp, TEXT("Publish"), TEXT("URL"), NULL);
                    SendDlgItemMessage(hwnd, IDC_SERVICE, CB_SETCURSEL, 0, 0);
                }
                else
                {
                    ShowWindow(GetDlgItem(hwnd, IDC_URL), SW_HIDE);
                    hwndTemp = GetDlgItem(hwnd, IDC_SERVERLIST);

                    XElement *services = serverData.GetElement(TEXT("services"));
                    if(services)
                    {
                        XElement *service = NULL;
                        numServices = services->NumElements();
                        for(UINT i=0; i<numServices; i++)
                        {
                            XElement *curService = services->GetElementByID(i);
                            if(curService->GetInt(TEXT("id")) == serviceID)
                            {
                                SendDlgItemMessage(hwnd, IDC_SERVICE, CB_SETCURSEL, i+1, 0);
                                service = curService;
                                break;
                            }
                        }

                        if(service)
                        {
                            XElement *servers = service->GetElement(TEXT("servers"));
                            if(servers)
                            {
                                UINT numServers = servers->NumDataItems();
                                for(UINT i=0; i<numServers; i++)
                                {
                                    XDataItem *server = servers->GetDataItemByID(i);
                                    SendMessage(hwndTemp, CB_ADDSTRING, 0, (LPARAM)server->GetName());
                                }
                            }
                        }
                    }

                    LoadSettingComboString(hwndTemp, TEXT("Publish"), TEXT("URL"), NULL);
                }

                if(mode != 0) ShowWindow(hwndTemp, SW_HIDE);

                //--------------------------------------------

                hwndTemp = GetDlgItem(hwnd, IDC_LOWLATENCYMODE);

                BOOL bLowLatencyMode = AppConfig->GetInt(TEXT("Publish"), TEXT("LowLatencyMode"), 0);
                SendMessage(hwndTemp, BM_SETCHECK, bLowLatencyMode ? BST_CHECKED : BST_UNCHECKED, 0);

                //--------------------------------------------

                hwndTemp = GetDlgItem(hwnd, IDC_AUTORECONNECT);

                BOOL bAutoReconnect = AppConfig->GetInt(TEXT("Publish"), TEXT("AutoReconnect"), 1);
                SendMessage(hwndTemp, BM_SETCHECK, bAutoReconnect ? BST_CHECKED : BST_UNCHECKED, 0);

                if(mode != 0) ShowWindow(hwndTemp, SW_HIDE);

                hwndTemp = GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT);
                EnableWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT_EDIT), bAutoReconnect);
                EnableWindow(hwndTemp, bAutoReconnect);

                int retryTime = AppConfig->GetInt(TEXT("Publish"), TEXT("AutoReconnectTimeout"), 10);
                if(retryTime > 60)      retryTime = 60;
                else if(retryTime < 0)  retryTime = 0;

                SendMessage(hwndTemp, UDM_SETRANGE32, 0, 60);
                SendMessage(hwndTemp, UDM_SETPOS32, 0, retryTime);

                if(mode != 0) ShowWindow(hwndTemp, SW_HIDE);

                //--------------------------------------------

                hwndTemp = GetDlgItem(hwnd, IDC_DELAY);

                int delayTime = AppConfig->GetInt(TEXT("Publish"), TEXT("Delay"), 0);

                SendMessage(hwndTemp, UDM_SETRANGE32, 0, 900);
                SendMessage(hwndTemp, UDM_SETPOS32, 0, delayTime);

                //--------------------------------------------

                if(mode != 0)
                {
                    ShowWindow(GetDlgItem(hwnd, IDC_SERVICE_STATIC), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_PLAYPATH_STATIC), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_URL_STATIC), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_SERVER_STATIC), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_LOWLATENCYMODE), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT_STATIC), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT_EDIT), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_DELAY_STATIC), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_DELAY_EDIT), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_DELAY), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_KEEPRECORDING), SW_HIDE);
                    //ShowWindow(GetDlgItem(hwnd, IDC_DASHBOARDLINK), SW_HIDE);
                    //ShowWindow(GetDlgItem(hwnd, IDC_DASHBOARDLINK_STATIC), SW_HIDE);
                    ShowWindow(GetDlgItem(hwnd, IDC_SAVETOFILE), SW_HIDE);

                    AdjustWindowPos(GetDlgItem(hwnd, IDC_SAVEPATH_STATIC), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_SAVEPATH), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_BROWSE), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY_STATIC), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY_STATIC), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STARTSTREAM), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY_STATIC), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY_STATIC), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STARTRECORDING), 0, -data.fileControlOffset);
                    AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STOPRECORDING), 0, -data.fileControlOffset);
                }

                //--------------------------------------------

                DWORD startHotkey = AppConfig->GetInt(TEXT("Publish"), TEXT("StartStreamHotkey"));
                SendMessage(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY), HKM_SETHOTKEY, startHotkey, 0);

                //--------------------------------------------

                DWORD stopHotkey = AppConfig->GetInt(TEXT("Publish"), TEXT("StopStreamHotkey"));
                SendMessage(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY), HKM_SETHOTKEY, stopHotkey, 0);

                //--------------------------------------------

                startHotkey = AppConfig->GetInt(TEXT("Publish"), TEXT("StartRecordingHotkey"));
                SendMessage(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY), HKM_SETHOTKEY, startHotkey, 0);

                //--------------------------------------------

                stopHotkey = AppConfig->GetInt(TEXT("Publish"), TEXT("StopRecordingHotkey"));
                SendMessage(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY), HKM_SETHOTKEY, stopHotkey, 0);

                //--------------------------------------------

                BOOL bKeepRecording = AppConfig->GetInt(TEXT("Publish"), TEXT("KeepRecording"));
                SendMessage(GetDlgItem(hwnd, IDC_KEEPRECORDING), BM_SETCHECK, bKeepRecording ? BST_CHECKED : BST_UNCHECKED, 0);

                BOOL bSaveToFile = AppConfig->GetInt(TEXT("Publish"), TEXT("SaveToFile"));
                SendMessage(GetDlgItem(hwnd, IDC_SAVETOFILE), BM_SETCHECK, bSaveToFile ? BST_CHECKED : BST_UNCHECKED, 0);

                CTSTR lpSavePath = AppConfig->GetStringPtr(TEXT("Publish"), TEXT("SavePath"));
                SetWindowText(GetDlgItem(hwnd, IDC_SAVEPATH), lpSavePath);

                EnableWindow(GetDlgItem(hwnd, IDC_KEEPRECORDING), bSaveToFile || (mode != 0));

                EnableWindow(GetDlgItem(hwnd, IDC_SAVEPATH), bSaveToFile || (mode != 0));
                EnableWindow(GetDlgItem(hwnd, IDC_BROWSE),   bSaveToFile || (mode != 0));

                //--------------------------------------------

                //SetWindowText(GetDlgItem(hwnd, IDC_DASHBOARDLINK), App->strDashboard);

                //--------------------------------------------

                SetWarningInfo();

                ShowWindow(GetDlgItem(hwnd, IDC_INFO), SW_HIDE);
                SetChangedSettings(false);

                return TRUE;
            }

        case WM_CTLCOLORSTATIC:
            {
                switch (GetDlgCtrlID((HWND)lParam))
                {
                    case IDC_WARNINGS:
                        SetTextColor((HDC)wParam, RGB(255, 0, 0));
                        SetBkColor((HDC)wParam, COLORREF(GetSysColor(COLOR_3DFACE)));
                        return (INT_PTR)GetSysColorBrush(COLOR_BTNFACE);
                }
            }
            break;

        case WM_DESTROY:
            {
            }
            break;

        case WM_NOTIFY:
            {
                NMHDR *nmHdr = (NMHDR*)lParam;

                if(nmHdr->idFrom == IDC_AUTORECONNECT_TIMEOUT)
                {
                    if(nmHdr->code == UDN_DELTAPOS)
                        SetChangedSettings(true);
                }

                break;
            }

        case WM_COMMAND:
            {
                bool bDataChanged = false;

                switch(LOWORD(wParam))
                {
                    case IDC_MODE:
                        {
                            if(HIWORD(wParam) != CBN_SELCHANGE)
                                break;

                            int mode = (int)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                            int swShowControls = (mode == 0) ? SW_SHOW : SW_HIDE;

                            ShowWindow(GetDlgItem(hwnd, IDC_SERVICE), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_PLAYPATH), swShowControls);

                            int serviceID = (int)SendMessage(GetDlgItem(hwnd, IDC_SERVICE), CB_GETCURSEL, 0, 0);
                            if(serviceID == 0)
                            {
                                ShowWindow(GetDlgItem(hwnd, IDC_SERVERLIST), SW_HIDE);
                                ShowWindow(GetDlgItem(hwnd, IDC_URL), swShowControls);
                            }
                            else
                            {
                                ShowWindow(GetDlgItem(hwnd, IDC_SERVERLIST), swShowControls);
                                ShowWindow(GetDlgItem(hwnd, IDC_URL), SW_HIDE);
                            }

                            BOOL bSaveToFile = SendMessage(GetDlgItem(hwnd, IDC_SAVETOFILE), BM_GETCHECK, 0, 0) != BST_UNCHECKED;
                            EnableWindow(GetDlgItem(hwnd, IDC_KEEPRECORDING), bSaveToFile || (mode != 0));
                            EnableWindow(GetDlgItem(hwnd, IDC_SAVEPATH), bSaveToFile || (mode != 0));
                            EnableWindow(GetDlgItem(hwnd, IDC_BROWSE),   bSaveToFile || (mode != 0));

                            if(mode == 0 && data.mode == 1)
                            {
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_SAVEPATH_STATIC), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_SAVEPATH), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_BROWSE), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY_STATIC), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY_STATIC), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STARTSTREAM), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY_STATIC), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY_STATIC), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STARTRECORDING), 0, data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STOPRECORDING), 0, data.fileControlOffset);

                            }
                            else if(mode == 1 && data.mode == 0)
                            {
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_SAVEPATH_STATIC), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_SAVEPATH), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_BROWSE), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY_STATIC), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY_STATIC), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STARTSTREAM), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY_STATIC), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY_STATIC), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STARTRECORDING), 0, -data.fileControlOffset);
                                AdjustWindowPos(GetDlgItem(hwnd, IDC_CLEARHOTKEY_STOPRECORDING), 0, -data.fileControlOffset);
                            }

                            data.mode = mode;

                            ShowWindow(GetDlgItem(hwnd, IDC_SERVICE_STATIC), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_PLAYPATH_STATIC), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_URL_STATIC), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_SERVER_STATIC), swShowControls);
                            //ShowWindow(GetDlgItem(hwnd, IDC_DASHBOARDLINK), swShowControls);
                            //ShowWindow(GetDlgItem(hwnd, IDC_DASHBOARDLINK_STATIC), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_LOWLATENCYMODE), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT_STATIC), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT_EDIT), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_DELAY_STATIC), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_DELAY_EDIT), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_DELAY), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_SAVETOFILE), swShowControls);
                            ShowWindow(GetDlgItem(hwnd, IDC_KEEPRECORDING), swShowControls);

                            SetWarningInfo();

                            bDataChanged = true;
                            break;
                        }

                    case IDC_SERVICE:
                        if(HIWORD(wParam) == CBN_SELCHANGE)
                        {
                            int serviceID = (int)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);

                            if(serviceID == 0)
                            {
                                ShowWindow(GetDlgItem(hwnd, IDC_SERVERLIST), SW_HIDE);
                                ShowWindow(GetDlgItem(hwnd, IDC_URL), SW_SHOW);

                                SetWindowText(GetDlgItem(hwnd, IDC_URL), NULL);
                                //SetWindowText(GetDlgItem(hwnd, IDC_DASHBOARDLINK), NULL);
                            }
                            else
                            {
                                ShowWindow(GetDlgItem(hwnd, IDC_URL), SW_HIDE);

                                hwndTemp = GetDlgItem(hwnd, IDC_SERVERLIST);
                                ShowWindow(hwndTemp, SW_SHOW);
                                SendMessage(hwndTemp, CB_RESETCONTENT, 0, 0);

                                XConfig serverData;
                                if(serverData.Open(TEXT("services.xconfig")))
                                {
                                    XElement *services = serverData.GetElement(TEXT("services"));
                                    if(services)
                                    {
                                        XElement *service = services->GetElementByID(serviceID-1);
                                        if(service)
                                        {
                                            XElement *servers = service->GetElement(TEXT("servers"));
                                            if(servers)
                                            {
                                                UINT numServers = servers->NumDataItems();
                                                for(UINT i=0; i<numServers; i++)
                                                {
                                                    XDataItem *server = servers->GetDataItemByID(i);
                                                    SendMessage(hwndTemp, CB_ADDSTRING, 0, (LPARAM)server->GetName());
                                                }
                                            }
                                        }
                                    }
                                }

                                SendMessage(hwndTemp, CB_SETCURSEL, 0, 0);
                            }

                            SetWindowText(GetDlgItem(hwnd, IDC_PLAYPATH), NULL);

                            bDataChanged = true;
                        }

                        SetWarningInfo();

                        break;

                    case IDC_AUTORECONNECT:
                        if(HIWORD(wParam) == BN_CLICKED)
                        {
                            BOOL bAutoReconnect = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;

                            EnableWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT),       bAutoReconnect);
                            EnableWindow(GetDlgItem(hwnd, IDC_AUTORECONNECT_TIMEOUT_EDIT),  bAutoReconnect);

                            SetChangedSettings(true);
                        }
                        break;

                    case IDC_AUTORECONNECT_TIMEOUT_EDIT:
                        if(HIWORD(wParam) == EN_CHANGE)
                            SetChangedSettings(true);
                        break;

                    case IDC_DELAY_EDIT:
                        if(HIWORD(wParam) == EN_CHANGE)
                            bDataChanged = true;
                        break;

                    case IDC_SAVETOFILE:
                        if(HIWORD(wParam) == BN_CLICKED)
                        {
                            BOOL bSaveToFile = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;

                            EnableWindow(GetDlgItem(hwnd, IDC_KEEPRECORDING), bSaveToFile);

                            EnableWindow(GetDlgItem(hwnd, IDC_SAVEPATH), bSaveToFile);
                            EnableWindow(GetDlgItem(hwnd, IDC_BROWSE),   bSaveToFile);

                            bDataChanged = true;
                        }
                        break;

                    case IDC_KEEPRECORDING:
                        if(HIWORD(wParam) == BN_CLICKED)
                        {
                            BOOL bKeepRecording = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
                            App->bKeepRecording = bKeepRecording != 0;

                            bDataChanged = true;
                        }
                        break;

                    case IDC_BROWSE:
                        {
                            TCHAR lpFile[512];
                            OPENFILENAME ofn;
                            zero(&ofn, sizeof(ofn));
                            ofn.lStructSize = sizeof(ofn);
                            ofn.hwndOwner = hwnd;
                            ofn.lpstrFile = lpFile;
                            ofn.nMaxFile = 511;
                            ofn.lpstrFile[0] = 0;
                            ofn.lpstrFilter = TEXT("MP4 File (*.mp4)\0*.mp4\0Flash Video File (*.flv)\0*.flv\0");
                            ofn.lpstrFileTitle = NULL;
                            ofn.nMaxFileTitle = 0;
                            ofn.nFilterIndex = 1;
                            ofn.lpstrInitialDir = AppConfig->GetStringPtr(TEXT("Publish"), TEXT("LastSaveDir"));

                            ofn.Flags = OFN_PATHMUSTEXIST;

                            TCHAR curDirectory[512];
                            GetCurrentDirectory(511, curDirectory);

                            BOOL bChoseFile = GetSaveFileName(&ofn);
                            SetCurrentDirectory(curDirectory);

                            if(*lpFile && bChoseFile)
                            {
                                String strFile = lpFile;
                                strFile.FindReplace(TEXT("\\"), TEXT("/"));

                                String strExtension = GetPathExtension(strFile);
                                if(strExtension.IsEmpty() || (!strExtension.CompareI(TEXT("flv")) && /*!strExtension.CompareI(TEXT("avi")) &&*/ !strExtension.CompareI(TEXT("mp4"))))
                                {
                                    switch(ofn.nFilterIndex)
                                    {
                                        case 1:
                                            strFile << TEXT(".mp4"); break;
                                        case 2:
                                            strFile << TEXT(".flv"); break;
                                        /*case 3:
                                            strFile << TEXT(".avi"); break;*/
                                    }
                                }

                                String strFilePath = GetPathDirectory(strFile).FindReplace(TEXT("/"), TEXT("\\")) << TEXT("\\");
                                AppConfig->SetString(TEXT("Publish"), TEXT("LastSaveDir"), strFilePath);

                                strFile.FindReplace(TEXT("/"), TEXT("\\"));
                                SetWindowText(GetDlgItem(hwnd, IDC_SAVEPATH), strFile);
                                bDataChanged = true;
                            }

                            break;
                        }

                    case IDC_LOWLATENCYMODE:
                        if(HIWORD(wParam) == BN_CLICKED)
                            bDataChanged = true;
                        break;

                    case IDC_STARTSTREAMHOTKEY:
                    case IDC_STOPSTREAMHOTKEY:
                    //case IDC_DASHBOARDLINK:
                    case IDC_STARTRECORDINGHOTKEY:
                    case IDC_STOPRECORDINGHOTKEY:
                        if(HIWORD(wParam) == EN_CHANGE)
                            SetChangedSettings(true);
                        break;

                    case IDC_PLAYPATH:
                    case IDC_URL:
                    case IDC_SAVEPATH:
                        if(HIWORD(wParam) == EN_CHANGE)
                            bDataChanged = true;
                        break;

                    case IDC_CLEARHOTKEY_STARTSTREAM:
                        if(HIWORD(wParam) == BN_CLICKED)
                        {
                            if(SendMessage(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY), HKM_GETHOTKEY, 0, 0))
                            {
                                SendMessage(GetDlgItem(hwnd, IDC_STARTSTREAMHOTKEY), HKM_SETHOTKEY, 0, 0);
                                SetChangedSettings(true);
                            }
                        }
                        break;

                    case IDC_CLEARHOTKEY:
                        if(HIWORD(wParam) == BN_CLICKED)
                        {
                            if(SendMessage(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY), HKM_GETHOTKEY, 0, 0))
                            {
                                SendMessage(GetDlgItem(hwnd, IDC_STOPSTREAMHOTKEY), HKM_SETHOTKEY, 0, 0);
                                SetChangedSettings(true);
                            }
                        }
                        break;

                    case IDC_CLEARHOTKEY_STARTRECORDING:
                        if (HIWORD(wParam) == BN_CLICKED)
                        {
                            if (SendMessage(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY), HKM_GETHOTKEY, 0, 0))
                            {
                                SendMessage(GetDlgItem(hwnd, IDC_STARTRECORDINGHOTKEY), HKM_SETHOTKEY, 0, 0);
                                SetChangedSettings(true);
                            }
                        }
                        break;

                    case IDC_CLEARHOTKEY_STOPRECORDING:
                        if (HIWORD(wParam) == BN_CLICKED)
                        {
                            if (SendMessage(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY), HKM_GETHOTKEY, 0, 0))
                            {
                                SendMessage(GetDlgItem(hwnd, IDC_STOPRECORDINGHOTKEY), HKM_SETHOTKEY, 0, 0);
                                SetChangedSettings(true);
                            }
                        }
                        break;

                    case IDC_SERVERLIST:
                        if(HIWORD(wParam) == CBN_EDITCHANGE || HIWORD(wParam) == CBN_SELCHANGE)
                            bDataChanged = true;
                        break;
                }

                if(bDataChanged)
                {
                    ShowWindow(GetDlgItem(hwnd, IDC_INFO), SW_SHOW);
                    SetChangedSettings(true);
                }
                break;
            }
    }
    return FALSE;
}