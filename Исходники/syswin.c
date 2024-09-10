void winopen()
{
    HMENU menu;

    int sizew = gli_wmarginx * 2 + gli_cellw * gli_cols;
    int sizeh = gli_wmarginy * 2 + gli_cellh * gli_rows;

    sizew += GetSystemMetrics(SM_CXFRAME) * 2;
    sizeh += GetSystemMetrics(SM_CYFRAME) * 2;
    sizeh += GetSystemMetrics(SM_CYCAPTION);

    hwndframe = CreateWindow("XxFrame",
        NULL, // window caption
        WS_CAPTION|WS_THICKFRAME|
        WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX|
        WS_CLIPCHILDREN,
        CW_USEDEFAULT, // initial x position
        CW_USEDEFAULT, // initial y position
        sizew, // initial x size
        sizeh, // initial y size
        NULL, // parent window handle
        NULL, // window menu handle
        0, //hInstance, // program instance handle
        NULL); // creation parameters

    hwndview = CreateWindow("XxView",
        NULL,
        WS_VISIBLE | WS_CHILD,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        hwndframe,
        NULL, NULL, 0);

    hdc = NULL;

    menu = GetSystemMenu(hwndframe, 0);
    AppendMenu(menu, MF_SEPARATOR, 0, NULL);
    AppendMenu(menu, MF_STRING, ID_ABOUT, "About Gargoyle...");
    AppendMenu(menu, MF_STRING, ID_CONFIG, "Options...");
    // AppendMenu(menu, MF_STRING, ID_TOGSCR, "Toggle scrollbar");

    wintitle();

    ShowWindow(hwndframe, SW_SHOW);
}