//Function which takes input of An HTML Resource Id
BOOL CInfoDlg::ShowDialog(UINT idAboutHTMLID, HINSTANCE hInstance)
{
    //Load the IE Specific MSTML Interface DKK
    HINSTANCE hinstMSHTML = LoadLibrary(_T("MSHTML.DLL"));
    BOOL bSuccess = FALSE;
    if(hinstMSHTML)
    {
        SHOWHTMLDIALOGFN *pfnShowHTMLDialog;
        //Locate The Function ShowHTMLDialog in the Loaded MSHTML.DLL
        pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress(hinstMSHTML, "ShowHTMLDialog");
        if(pfnShowHTMLDialog)
        {
            LPTSTR lpszModule = new TCHAR[MAX_PATH];
            //Get The Application Path
            if (GetModuleFileName(hInstance, lpszModule, MAX_PATH))
            {
                //Add the IE Res protocol
                TCHAR strResourceURL[MAX_PATH*4];
                _stprintf_s(strResourceURL, _countof(strResourceURL), _T("res://%s/%u"), lpszModule, idAboutHTMLID);
                //Attempt to Create the URL Moniker to the specified in the URL String
                IMoniker *pmk;
                if(SUCCEEDED(CreateURLMoniker(NULL,strResourceURL,&pmk)))
                {
                    //Invoke the ShowHTMLDialog function by pointer
                    //passing the HWND of your Application , the Moniker,
                    //the remaining parameters can be set to NULL
                    pfnShowHTMLDialog(NULL,pmk,NULL,L"resizable:yes",NULL);
                    bSuccess = TRUE;
                }
            }
            delete [] lpszModule;
        }
        FreeLibrary(hinstMSHTML);
    }
    return bSuccess;
}