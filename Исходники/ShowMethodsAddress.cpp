//-----------------------------------------------------------------------------
// Name: ModelessDialogThread
// Object: allow to act like a dialog box in modeless mode
// Parameters :
//     in  : PVOID lParam : HINSTANCE hInstance : application instance
//     out :
//     return : 
//-----------------------------------------------------------------------------
DWORD WINAPI CComShowMethodsAddress::ModelessDialogThread(PVOID lParam)
{
    CComShowMethodsAddress* pComShowMethodsAddress=new CComShowMethodsAddress();
    // force ole initialization for current thread
    OleInitialize(NULL);
    
    DialogBoxParam ((HINSTANCE)lParam,(LPCTSTR)IDD_DIALOG_SHOW_METHODS_ADDRESS,NULL,(DLGPROC)CComShowMethodsAddress::WndProc,(LPARAM)pComShowMethodsAddress);
    delete pComShowMethodsAddress->pTreeview;

    // uninitialize ole for current thread
    // OleUninitialize(); // too slow
    delete pComShowMethodsAddress;

    if (hSemaphoreOpenDialogs)
        ReleaseSemaphore(hSemaphoreOpenDialogs,1,NULL); // must be last instruction

    return 0;
}