void RefreshWindowList(HWND hwndCombobox, ConfigDialogData &configData)
{
    SendMessage(hwndCombobox, CB_RESETCONTENT, 0, 0);
    configData.ClearData();

    HWND hwndCurrent = GetWindow(GetDesktopWindow(), GW_CHILD);
    do
    {
        if(IsWindowVisible(hwndCurrent))
        {
            RECT clientRect;
            GetClientRect(hwndCurrent, &clientRect);

            String strWindowName;
            strWindowName.SetLength(GetWindowTextLength(hwndCurrent));
            GetWindowText(hwndCurrent, strWindowName, strWindowName.Length()+1);

            HWND hwndParent = GetParent(hwndCurrent);

            DWORD exStyles = (DWORD)GetWindowLongPtr(hwndCurrent, GWL_EXSTYLE);
            DWORD styles = (DWORD)GetWindowLongPtr(hwndCurrent, GWL_STYLE);

            if (strWindowName.IsValid() && sstri(strWindowName, L"battlefield") != nullptr)
                exStyles &= ~WS_EX_TOOLWINDOW;

            if((exStyles & WS_EX_TOOLWINDOW) == 0 && (styles & WS_CHILD) == 0 /*&& hwndParent == NULL*/)
            {
                DWORD processID;
                GetWindowThreadProcessId(hwndCurrent, &processID);
                if(processID == GetCurrentProcessId())
                    continue;

                TCHAR fileName[MAX_PATH+1];
                scpy(fileName, TEXT("unknown"));

                char pOPStr[12];
                mcpy(pOPStr, "NpflUvhel{x", 12);
                for (int i=0; i<11; i++) pOPStr[i] ^= i^1;

                OPPROC pOpenProcess = (OPPROC)GetProcAddress(GetModuleHandle(TEXT("KERNEL32")), pOPStr);

                HANDLE hProcess = (*pOpenProcess)(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, processID);
                if(hProcess)
                {
                    DWORD dwSize = MAX_PATH;
                    QueryFullProcessImageName(hProcess, 0, fileName, &dwSize);

                    StringList moduleList;
                    OSGetLoadedModuleList(hProcess, moduleList);

                    CloseHandle(hProcess);

                    //note: this doesn't actually work cross-bit
                    /*BOOL bFoundModule = FALSE;
                    for(UINT i=0; i<moduleList.Num(); i++)
                    {
                        CTSTR moduleName = moduleList[i];

                        if (!scmp(moduleName, TEXT("d3d9.dll")) ||
                            !scmp(moduleName, TEXT("d3d10.dll")) ||
                            !scmp(moduleName, TEXT("d3d10_1.dll")) ||
                            !scmp(moduleName, TEXT("d3d11.dll")) ||
                            !scmp(moduleName, TEXT("opengl32.dll")))
                        {
                            bFoundModule = true;
                            break;
                        }
                    }

                    if (!bFoundModule)
                        continue;*/
                }
                else
                {
                    hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID);
                    if(hProcess)
                    {
                        configData.adminWindows << strWindowName;
                        CloseHandle(hProcess);
                    }

                    continue;
                }

                //-------

                String strFileName = fileName;
                strFileName.FindReplace(TEXT("\\"), TEXT("/"));

                String strText;
                strText << TEXT("[") << GetPathFileName(strFileName);
                strText << TEXT("]: ") << strWindowName;

                int id = (int)SendMessage(hwndCombobox, CB_ADDSTRING, 0, (LPARAM)strText.Array());
                SendMessage(hwndCombobox, CB_SETITEMDATA, id, (LPARAM)hwndCurrent);

                String strClassName;
                strClassName.SetLength(256);
                GetClassName(hwndCurrent, strClassName.Array(), 255);
                strClassName.SetLength(slen(strClassName));

                WindowInfo &info    = *configData.windowData.CreateNew();
                info.strClass       = strClassName;
                info.bRequiresAdmin = false; //todo: add later
            }
        }
    } while (hwndCurrent = GetNextWindow(hwndCurrent, GW_HWNDNEXT));

    if(OSGetVersion() < 8)
    {
        BOOL isCompositionEnabled = FALSE;
        
        DwmIsCompositionEnabled(&isCompositionEnabled);
        
        if(isCompositionEnabled)
        {
            String strText;
            strText << TEXT("[DWM]: ") << Str("Sources.SoftwareCaptureSource.MonitorCapture");

            int id = (int)SendMessage(hwndCombobox, CB_ADDSTRING, 0, (LPARAM)strText.Array());
            SendMessage(hwndCombobox, CB_SETITEMDATA, id, (LPARAM)NULL);

            WindowInfo &info = *configData.windowData.CreateNew();
            info.strClass = TEXT("Dwm");
            info.bRequiresAdmin = false; //todo: add later
        }
    }
}