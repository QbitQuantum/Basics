// ---------------------------------------------------------------------------
// CWinMenubar::AboutProc()
// Dialog Window proc for About dialog
// ---------------------------------------------------------------------------
BOOL CALLBACK CWinMenubar::AboutProc(HWND hDlg, UINT message, 
                                     WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam); // unless SDK_REGISTRATION is defined
    switch (message) 
    {
    case WM_INITDIALOG:
        {
        TCHAR text[128];
        CWinMenubar* menubar = (CWinMenubar*)lParam;
        HINSTANCE hMod = menubar->ModuleHandle();
        GetWindowText(GetParent(hDlg), text, sizeof(text)/sizeof(text[0]));
        SetWindowText(hDlg, text);

        HBITMAP hBitmap = NULL;
        UINT textScrollID = IDC_ABOUT_TEXT_SCROLL;
        UINT textNoScrollID = IDC_ABOUT_TEXT_NO_SCROLL;
        UINT setTextMsg = WM_SETTEXT;
        WPARAM setTextParam = 0;
        SETTEXTEX setText;
        setText.flags = ST_SELECTION;
        setText.codepage = CP_ACP;

        char* aboutText = NULL;
        if (menubar->iRichEdit)
        {
            aboutText = ReadTextFile(ABOUTBOX_RTF_FILE);
        }
        if (aboutText)
        {
            setTextMsg = EM_SETTEXTEX;
            textScrollID = textNoScrollID = IDC_ABOUT_RICHTEXT;
            setTextParam = (WPARAM)&setText;
            hBitmap = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_JAVA_POWERED));

#ifdef HAVE_WLIB

            HWND hText = GetDlgItem(hDlg, IDC_ABOUT_RICHTEXT);
            SendMessage(hText, EM_SETEVENTMASK, 0, 
            SendMessage(hText, EM_GETEVENTMASK, 0,0) | ENM_LINK);
            SendMessage(hText, EM_AUTOURLDETECT, TRUE, 0);

#endif // HAVE_WLIB

        }

        if (!aboutText && menubar->iRichEdit)
        {
            // Load default about text from the resource
            void* ptr = NULL;
            UINT size = 0;
            HGLOBAL hg = 0;
            HRSRC hr = FindResourceA(hMod,MAKEINTRESOURCEA(IDR_ABOUT_RTF),"RTF");
            if (hr)
            {
                size = SizeofResource(ModuleHandle(), hr);
                hg = LoadResource(ModuleHandle(), hr);
                ptr = LockResource(hg);
            }
            if (ptr)
            {
                aboutText = (char*)Alloc(size+1);
                if (aboutText)
                {
                    memcpy(aboutText, ptr, size);
                    aboutText[size] = 0;
                    setTextMsg = EM_SETTEXTEX;
                    textScrollID = IDC_ABOUT_RICHTEXT;
                    textNoScrollID = IDC_ABOUT_RICHTEXT;
                    hBitmap = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_JAVA_POWERED));
                    setTextParam = (WPARAM)&setText;
                }
                UnlockResource(hg);
            }
        }
        if (aboutText)
        {   
            // Check if we need the scrollbar. 12 lines of text
            // will fit into the edit control.
            HWND hText = GetDlgItem(hDlg, textNoScrollID);
            SendMessageA(hText,setTextMsg,setTextParam,(LPARAM)aboutText);
            if (SendMessageA(hText, EM_GETLINECOUNT,0,0) <= 12)
            {
                // No need for the scrollbar, show the edit
                // control without the WS_VSCROLL style
                ShowWindow(hText, SW_SHOWNORMAL);
            }
            else 
            {
                // We need the vertical scrollbar, show the edit control
                // with the WS_VSCROLL style. Note that  textScrollID and
                // textNoScrollID may point to the same window, so reset
                // the text in the control (bug #DPEV-6JUJSQ)
                hText = GetDlgItem(hDlg, textScrollID);
                SendMessageA(hText,WM_SETTEXT,0,(LPARAM)"");
                SendMessageA(hText,setTextMsg,setTextParam,(LPARAM)aboutText);
                ShowWindow(hText, SW_SHOWNORMAL);
            }            
            
            // Add full SDK name to the RichEdit control by replacing <sdk_name> tag with the 
            // name defined in SdkProductInfo.h. Note that decision between MIDP and C++ SDK 
            // product names is made using CWinMenubar iMidpSdk member.
            static const TCHAR keywordHeading[] = TEXT("<sdk_name>");
            static const UINT keywordHeadingLen = COUNT(keywordHeading)-1;
            
            FINDTEXT findHeading;
            ZeroMemory(&findHeading, sizeof(findHeading));
            findHeading.chrg.cpMax = -1;
            findHeading.lpstrText = (LPTSTR)keywordHeading;
            // Select whole content
            SendMessage(hText, EM_SETSEL, 0, 0);
            // Find from selection
            int pos = SendMessage(hText,EM_FINDTEXT, FR_MATCHCASE|FR_DOWN,
                (LPARAM)&findHeading);
            if (pos >= 0) {       
                // Sdk name tag found         
                IRichEditOle* re = NULL;
                SendMessage(hText, EM_GETOLEINTERFACE, 0, (LPARAM)&re);
                if (re) {
                    // Select SDK name tag and replace it with the full SDK name
                    SendMessage(hText, EM_SETSEL, pos, pos+keywordHeadingLen);
                    if(menubar->iMidpSDK)
                        SendMessage(hText, EM_REPLACESEL, true, (LPARAM)TEXT(SDK_FULL_PRODUCT_NAME_MIDP));
                    else
                        SendMessage(hText, EM_REPLACESEL, true, (LPARAM)TEXT(SDK_FULL_PRODUCT_NAME_CPP));
                    re->Release();
                }
            }
            
            if (hBitmap)
            {
                static const TCHAR keyword[] = TEXT("<java logo>");
                static const UINT keywordLen = COUNT(keyword)-1;

                FINDTEXT find;
                ZeroMemory(&find, sizeof(find));
                find.chrg.cpMax = -1;
                find.lpstrText = (LPTSTR)keyword;
                SendMessage(hText, EM_SETSEL, 0, 0);
                int pos = SendMessage(hText,EM_FINDTEXT, FR_MATCHCASE|FR_DOWN,
                    (LPARAM)&find);
                if (pos >= 0) {
                    IRichEditOle* re = NULL;
                    SendMessage(hText, EM_GETOLEINTERFACE, 0, (LPARAM)&re);
                    if (re) {
                        CImageDataObject* bmp = new CImageDataObject(hBitmap);
                        if (bmp) {
                            SendMessage(hText,EM_SETSEL,pos,pos+keywordLen);
                            bmp->Insert(re);
                            bmp->Release();
                        }
                        re->Release();
                    }
                }
            }
            Free(aboutText);
        }

#ifdef SDK_REGISTRATION

        // Show product key
        if (gRegProductContext)
        {
            HWND hProductKey = GetDlgItem(hDlg, IDC_PRODUCT_KEY);
            const char* szKey = REG_ProductKey(gRegProductContext);
            SetWindowTextA(hProductKey, szKey);
            // The control is created invisible, show it
            ShowWindow(hProductKey, SW_SHOWNORMAL);
            if (REG_ProductStatus(gRegProductContext) != RegRegistered)
            {
                // Show the Register button
                ShowWindow(GetDlgItem(hDlg, IDC_REGISTER), SW_SHOWNORMAL);
            }
        }
                    
#endif // SDK_REGISTRATION

        // Subclass the product name control
        HWND hName = GetDlgItem(hDlg, IDC_PRODUCT_NAME);
        HINSTANCE hInst = (HINSTANCE)GetWindowLong(hDlg,GWL_HINSTANCE);
        if (hName)
        {
            // Allocate TitleData structure. It will be deallocated
            // by TitleWndProc when it receives WM_DESTROY message
            TitleData* data = (TitleData*)malloc(sizeof(TitleData));
            if (data)
            {
                LOGFONTA logFont;
                ZeroMemory(data, sizeof(*data));
                ZeroMemory(&logFont, sizeof(logFont));
                logFont.lfHeight = 24;
                logFont.lfWeight = FW_BOLD;
                logFont.lfCharSet = ANSI_CHARSET;
                logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
                logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
                logFont.lfQuality = ANTIALIASED_QUALITY;
                logFont.lfPitchAndFamily = VARIABLE_PITCH;

                // Try Nokia font first
                strcpy(logFont.lfFaceName, "Nokia Sans");
                data->hFont = CreateFontIndirectA(&logFont);
                if (!data->hFont)
                {
                    // No Nokia font, try Arial then
                    strcpy(logFont.lfFaceName, "Arial");
                    data->hFont = CreateFontIndirectA(&logFont);
                }
                
                // Load bitmaps
                data->hBitmap = LoadBitmapA(hInst, 
                    MAKEINTRESOURCEA(IDB_ABOUT_TOP));

                // load product name from the file
                data->productName = ReadTextFile(PRODUCTNAME_FILE);
                data->productId = menubar->GetProductId();

                // Request initial bitmap
                data->bRepaint = TRUE;

#ifdef SDK_REGISTRATION

                data->hGradientBitmap = LoadBitmapA(hInst, 
                    MAKEINTRESOURCEA(IDB_ABOUT_GRADIENT));

                if (gRegProductContext)
                {
                    data->scrollText = TitleCreateScrollData(hName,
                        gRegProductContext);
                    if (data->scrollText)
                    {
                        // Initial delay
                        SetTimer(hName, SCROLL_DELAY_TIMER, 
                            SCROLL_TIMER_DELAY, NULL);
                    }
                }
#endif // SDK_REGISTRATION
        
                // Subclass the window
                data->superProc = (WNDPROC)GetWindowLong(hName,GWL_WNDPROC);
                SetWindowLong(hName, GWL_USERDATA, (LONG)data);
                SetWindowLong(hName, GWL_WNDPROC, (LONG)TitleWndProc);
            }
        }

#ifdef HAVE_WLIB
        WIN32_CenterWindow(hDlg, NULL);
#endif // HAVE_WLIB
        return TRUE;
        }
        
    case WM_COMMAND:
        switch (wParam)
        {

#ifdef SDK_REGISTRATION

        case IDC_REGISTER:
            if (REG_RegisterNow(gRegProductContext, hDlg))
            {
                TitleStopScroller(hDlg);

                // Update the scroller
                HWND hTitle = GetDlgItem(hDlg, IDC_PRODUCT_NAME);
                ScrollTextData* scroll = TitleCreateScrollData(
                    hTitle, gRegProductContext);

                if (scroll)
                {
                    TitleData* data;
                    data = (TitleData*)GetWindowLong(hTitle,GWL_USERDATA);
                    TitleDeleteScrollData(data->scrollText);
                    data->scrollText = scroll;
                }
            }
            if (REG_ProductStatus(gRegProductContext) == RegRegistered)
            {
                // The button has served its purpose. Hide it
                ShowWindow(GetDlgItem(hDlg, IDC_REGISTER), SW_HIDE);
            }
            return TRUE;

#endif // SDK_REGISTRATION

        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, wParam);
            return TRUE;
        default:
            return FALSE;
        }

#ifdef HAVE_WLIB // Need wlib to use WIN32_BrowseURL

    case WM_NOTIFY:
        if (((LPNMHDR)lParam)->idFrom == IDC_ABOUT_RICHTEXT)
        {
            char url[256];
            ENLINK* link = (ENLINK*)lParam;
            if (link->msg == WM_LBUTTONDOWN &&
                (link->chrg.cpMax - link->chrg.cpMin) <
                (COUNT(url)/2-1)) // EM_GETTEXTRANGE may think it's in WCHARs
            {
                // Visual effect
                HWND hText = link->nmhdr.hwndFrom;
                SendMessage(hText,EM_SETSEL,link->chrg.cpMin,link->chrg.cpMax);

                // It's not very clear what EM_GETTEXTRANGE message writes
                // into the buffer. Since we use SendMessageA (ANSI API),
                // I would expect that it returns ANSI string as most other
                // text-related messages do. Yet, at least some versions of
                // RichEdit control seem to return UCS-2 characters. Internet
                // search produces conflicting results. Let's be prepared for
                // anything. After all, there are only two possiblities. It's
                // either UCS-2 or ASCII.
                TEXTRANGEA range;
                range.chrg = link->chrg;
                range.lpstrText = url;
                url[0] = url[1] = 0;
                SendMessageA(hText, EM_GETTEXTRANGE, 0, (LPARAM)&range);
                url[COUNT(url)-1] = url[COUNT(url)-2] = 0;
                if (!_wcsnicmp((WCHAR*)url,L"http://",7))
                {
                    // Looks like UCS-2 string to me. Convert it to ASCII
                    LPWSTR w = (WCHAR*)url;
                    LPSTR p = url;
                    do { *p++ =  (char)*w++; } while (*w);
                    *p = 0;
                }

                // Start the default browser
                WIN32_BrowseURL(url);
            }
        }
        // Usually, the return value is ignored
        return FALSE;

#endif // HAVE_WLIB

#ifdef SDK_REGISTRATION

    case WM_CTLCOLORSTATIC:
        // We don't want the product key edit control to erase its
        // background because it's drawn on top of the product name
        // bitmap (white cloud).
        {
            int nDlgCtrlID = GetDlgCtrlID((HWND)lParam);
            switch (nDlgCtrlID) 
            {
            case IDC_PRODUCT_KEY:
                // Return transparent brush for the product key control
                return (BOOL)GetStockObject(HOLLOW_BRUSH);
            }
        }
        return FALSE;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
        // Stop scrolling on mouse click
        TitleStopScroller(hDlg);
        return FALSE;

#endif // SDK_REGISTRATION

    default:
        return FALSE;
    }
}