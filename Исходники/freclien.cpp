/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: WinMain

  Summary:  The Windows main entry point function for this application.
            Initializes the application, the OLE Libraries, and starts
            the main application message loop.

  Args:     HINSTANCE hInstance,
              Instance handle; a new one for each invocation of this app.
            HINSTANCE hPrevInstance,
              Instance handle of the previous instance. NULL in Win32.
            LPSTR lpCmdLine,
              Windows passes a pointer to the application's
              invocation command line.
            int nCmdShow)
              Bits telling the show state of the application.

  Returns:  int
              msg.wParam (upon exit of message loop).
              FALSE if this instance couldn't initialize and run.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern "C" int PASCAL WinMain(
    HINSTANCE hInstance,
    HINSTANCE ,
    LPSTR ,
    int nCmdShow)
{
    CMainWindow* pWin = NULL;
    MSG msg;
    HACCEL hAccel = NULL;
    int iRun = FALSE;

    // If we were compiled for UNICODE and the platform seems OK with this
    // then proceed.  Else we error and exit the app.
    if (UnicodeOk())
    {
        // Call to initialize the OLE COM Library.  Use the OLE SUCCEEDED macro
        // to detect success.  If fail then exit app with error message.
        // Tell COM that this client process and all subordinate threads
        // will live in a multi-threaded world. This means that all subsequent
        // COM objects created and functioned by this client must be coded
        // to be thread-safe. This is where we tell COM that we are using
        // the "Free-threading" model (rather than the default Apartment Model).
        if (SUCCEEDED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
        {
            // If we succeeded in initializing the COM Library we proceed to
            // initialize the application.  If we can't init the application
            // then we signal shut down with an error message exit.
            iRun = InitApplication(hInstance);
            if (iRun)
            {
                // Assume we'll set iRun to TRUE when initialization is done.
                iRun = FALSE;
                // We are still go for running so we try to create a nifty new
                // CMainWindow object for this app instance.
                pWin = new CMainWindow;
                if (NULL != pWin)
                {
                    // Now we initialize an instance of the new CMainWindow.
                    // This includes creating the main window.  Note: if
                    // InitInstance fails then it would have already deleted
                    // pWin so we wouldn't need to delete it here.
                    if (pWin->InitInstance(hInstance, nCmdShow))
                    {
                        // Load the keyboard accelerators from the resources.
                        hAccel = LoadAccelerators(hInstance, TEXT("AppAccel"));
                        if (NULL != hAccel)
                        {
                            // Signal App Initialization is successfully done.
                            iRun = TRUE;
                        }
                    }
                }
            }

            if (iRun)
            {
                // If we initialized the app instance properly then we are still
                // go for running.  We then start up the main message pump for
                // the application.
                while (GetMessage(&msg, NULL, 0, 0))
                {
                    if (!TranslateAccelerator(pWin->GetHwnd(), hAccel, &msg))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }

                // We also ask COM to unload any unused COM Servers, including our
                // friend, FRESERVE.
                CoFreeUnusedLibraries();

                // We'll pass to Windows the reason why we exited the message loop.
                iRun = (int) msg.wParam;
            }
            else
            {
                // We failed to initialize the application--issue an error
                // messagebox.
                TCHAR szMsg[MAX_STRING_LENGTH];

                // Load the error message string from the resources.
                if (LoadString(
                            hInstance,
                            IDS_APPINITFAILED,
                            szMsg,
                            MAX_STRING_LENGTH))
                {
                    // Put up error message box saying that application couldn't be
                    // initialized.  Parent window is desktop (ie, NULL).
                    MessageBox(
                        NULL,
                        szMsg,
                        TEXT(ERROR_TITLE_STR),
                        MB_OK | MB_ICONEXCLAMATION);
                }
                delete pWin;
            }

            // We're exiting this app (either normally or by init failure) so
            // shut down the OLE COM Library.
            CoUninitialize();
        }
        else
        {
            // We failed to Initialize the OLE COM Library.
            TCHAR szMsg[MAX_STRING_LENGTH];

            // Load the error message string from the resources.
            if (LoadString(
                        hInstance,
                        IDS_OLEINITFAILED,
                        szMsg,
                        MAX_STRING_LENGTH))
            {
                // Put up error message box saying that OLE COM Library
                // couldn't be initialized.  Parent window is desktop (ie, NULL).
                // And exit the failed application.
                MessageBox(
                    NULL,
                    szMsg,
                    TEXT(ERROR_TITLE_STR),
                    MB_OK | MB_ICONEXCLAMATION);
            }
        }
    }
    else
    {
        // If we were compiled for UNICODE but the platform has problems with
        // this then indicate an error and exit the app immediately.
        CHAR szMsg[MAX_STRING_LENGTH];

        if (LoadStringA(
                    hInstance,
                    IDS_NOUNICODE,
                    szMsg,
                    MAX_STRING_LENGTH))
        {
            MessageBoxA(
                NULL,
                szMsg,
                ERROR_TITLE_STR,
                MB_OK | MB_ICONEXCLAMATION);
        }
    }

    return iRun;
}