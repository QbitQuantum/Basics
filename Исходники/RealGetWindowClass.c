void Test_RealGetWindowClass()
{
    int testNo;
    UINT Result;
    CHAR Buffer[1024];

    Result = RealGetWindowClass( NULL, Buffer, ARRAY_SIZE(Buffer) );
    ok(Result == 0, "Result = %d\n", Result);
    ok(GetLastError() == ERROR_INVALID_WINDOW_HANDLE, "GetLastError() = %ld\n", GetLastError());

    for (testNo = 0; testNo < ARRAY_SIZE(RealClassTestData); testNo++)
    {
        ATOM atom;
        WNDCLASSA cls;
        HWND hWnd;

        /* Register classes, "derived" from built-in dialog, with and without the DLGWINDOWEXTRA flag set */
        GetClassInfoA(0, "#32770", &cls);
        if (RealClassTestData[testNo].OverrideWndProc)
            cls.lpfnWndProc = DefWindowProcA;
        cls.lpszClassName = RealClassTestData[testNo].ClassName;
        cls.cbWndExtra &= ~RealClassTestData[testNo].WndExtra;
        atom = RegisterClassA (&cls);
        if (atom == 0) return;

        /* Create a window */
        hWnd = CreateWindowEx( WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR |
                               WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW,
                               RealClassTestData[testNo].ClassName,
                               RealClassTestData[testNo].ClassName,
                               WS_POPUPWINDOW | WS_CLIPSIBLINGS | WS_DLGFRAME | WS_OVERLAPPED |
                               WS_MINIMIZEBOX | WS_MAXIMIZEBOX | DS_3DLOOK | DS_SETFONT | DS_MODALFRAME,
                               CW_USEDEFAULT, CW_USEDEFAULT, 100, 100,
                               NULL, NULL, 0, 0);

        /* Do we expect a HWND at all? */
        if (RealClassTestData[testNo].ExpectsHwnd)
        {
            ok(hWnd != NULL, "\n");

            if (hWnd != NULL)
            {
                /* Get the "real" class name */
                Result = RealGetWindowClass( hWnd, Buffer, ARRAY_SIZE(Buffer) );
                printf("Buffer: %s\nExpectedClassNameBefore(%d): %s\n", Buffer, testNo, RealClassTestData[testNo].ExpectedClassNameBefore);
                ok( Result != 0, "\n" );
                ok( strcmp( Buffer, RealClassTestData[testNo].ExpectedClassNameBefore ) == 0, "\n" );

                /* Call a function that requires a dialog window */
                DefDlgProcA( hWnd, DM_SETDEFID, IDCANCEL, 0 );

                /* Get the "real" class name again */
                Result = RealGetWindowClass( hWnd, Buffer, ARRAY_SIZE(Buffer) );
                printf("Buffer: %s\nExpectedClassNameAfter(%d): %s\n", Buffer, testNo, RealClassTestData[testNo].ExpectedClassNameAfter);
                ok( Result != 0, "\n" );
                ok( strcmp( Buffer, RealClassTestData[testNo].ExpectedClassNameAfter ) == 0, "\n" );
            }
        }
        else
        {
            ok(hWnd == NULL, "\n");
        }

        /* Cleanup */
        DestroyWindow(hWnd);
        UnregisterClass(RealClassTestData[testNo].ClassName, 0);
    }

}