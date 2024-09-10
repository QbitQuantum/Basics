int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    HICON icon;

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = STKCLIENT;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mousee-pointer */
    /* Note: hIconSm is window title icon, hIcon is program icon */
    icon = (HICON)LoadImage(NULL, STK_CLIENT_ICO, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    wincl.hIcon = icon;
    wincl.hIconSm = icon;

    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(DEFAULT_RGB);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* Register chat window class*/
    //stk_chatwin_register();

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                     /* Extended possibilites for variation */
           STKCLIENT,           /* Classname */
           STKCLIENT,           /* Title Text */
           WS_POPUP | WS_SYSMENU | WS_MINIMIZEBOX, /* ÎÞ±êÌâÀ¸´°¿Ú */
           950,         /* Windows decides the position */
           80,         /* where the window ends up on the screen */
           STK_MAINWIN_WIDTH,     /* The programs width */
           STK_MAINWIN_HEIGHT,    /* and height in pixels */
           HWND_DESKTOP,          /* The window is a child-window to desktop */
           NULL,                  /* No menu */
           hThisInstance,         /* Program Instance handler */
           NULL                   /* No Window Creation data */
           );

    /* Store hwnd to global var */
	stkWidget.hins = hThisInstance;

    stkWidget.hwnd = hwnd;

    /* add tray */
    stkWidget.nid.cbSize = sizeof(stkWidget.nid);
    stkWidget.nid.hWnd = hwnd;
    stkWidget.nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    stkWidget.nid.uCallbackMessage = WMAPP_TRAY;
    stkWidget.nid.hIcon = icon;
    strcpy(stkWidget.nid.szTip, STKCLIENT);
    Shell_NotifyIcon(NIM_ADD, &stkWidget.nid);

    /* STK UI */
    stk_create_ui(hwnd);

    /* init global vars and socket thread */
	memset(&client, 0, sizeof(client));
    stk_init_running();
	socketThread = CreateThread(0, 0, stk_socket, (void*)&client, 0, NULL);

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nFunsterStil);

    /* Let socket know we have done the initialization*/
    stk_log("WinMain set STK_INITIALIZED\n");
    stk_set_running(STK_INITIALIZED);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);

        if (messages.message == WM_KEYDOWN && messages.wParam == VK_TAB)
        {
            if (stk_get_running() == STK_INITIALIZED) {
                /* Press Tab, switch focus */
                SetTabFocus(hwnd);
            }
        } else if (messages.message == WM_KEYDOWN && messages.wParam == VK_RETURN) {
            if (stk_get_running() == STK_INITIALIZED) {
                /* Press Enter, Login in */
                stk_loginbtn_pressed();
            }
        } else {
            /* Send message to WindowProcedure */
            DispatchMessage(&messages);
        }
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}