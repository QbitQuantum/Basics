BOOL
InitInstance
(
    HANDLE  hInstance,
    INT     nCmdShow
)
/*++

Routine Description:

    Saves instance handle and creates main window

    This function is called at initialization time for every instance of
    this application.  This function performs initialization tasks that
    cannot be shared by multiple instances.

    In this case, we save the instance handle in a static variable and
    create and display the main program window.


Arguments:

    hInstance   - Current instance identifier

    nComShow    - Param for first ShowWindow() call.



Return Value:

    TRUE/FALSE


--*/
{
    //
    // Save the instance handle in static variable, which will be used in
    // many subsequence calls from this application to Windows.
    //

    hInstApp = hInstance;

    //
    // Create a main window for this application instance.
    //

    hWndApp = CreateWindow( ClassName,
                            TitleName,
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            NULL,
                            NULL,
                            hInstance,
                            NULL
                          );
    if (NULL != hWndApp)
    {
        //
        // Make the window visible; update its client area;
        // and send WM_PAINT message
        //

        ShowWindow(hWndApp, nCmdShow);
        UpdateWindow(hWndApp);
    }

    return ((hWndApp) ? TRUE : FALSE);
}