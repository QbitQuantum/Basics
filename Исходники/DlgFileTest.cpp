INT_PTR FileTestDialog(HWND hParent, TFileTestData * pData)
{
    HACCEL hAccelTable = LoadAccelerators(g_hInst, MAKEINTRESOURCE(IDR_ACCELERATORS));
    HWND hDlg;
    MSG msg;

    // Create the property sheet
    pData->bEnableResizing = TRUE;
    hDlg = CreateDialogParam(g_hInst,
                             MAKEINTRESOURCE(IDD_FILE_TEST),
                             hParent,
                             DialogProc,
                             (LPARAM)pData);
    
    // Perform the modal loop
    if(hDlg != NULL)
    {
        // Show the dialog
        ShowWindow(hDlg, SW_SHOW);

        // Get the message. Stop processing if WM_QUIT has arrived
        while(IsWindow(hDlg) && GetMessage(&msg, NULL, 0, 0))
        {
            // We need an alertable sleep to make APCs to work.
            // Uncomment this if you want to use the asynchronous "ApcRoutine"
            // parameter(s) in some native API
//          MsgWaitForMultipleObjectsEx(0,
//                                      NULL,
//                                      INFINITE,
//                                      QS_ALLEVENTS | QS_ALLINPUT | QS_ALLPOSTMESSAGE,
//                                      MWMO_WAITALL | MWMO_ALERTABLE | MWMO_INPUTAVAILABLE);

            if(!IsMyDialogMessage(hDlg, &msg))
            {
                // Process the accelerator table
                if(!TranslateAccelerator(hDlg, hAccelTable, &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }
    }

    if(hAccelTable != NULL)
        DestroyAcceleratorTable(hAccelTable);
    return IDOK;
}