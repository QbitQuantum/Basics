int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR, int	nCmdShow)
{
    MSG msg;
    WNDCLASS wndclass, wndclass2;
    RECT windRECT;
    HINSTANCE boeSoundsDLL;

    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNWINDOW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(10));
    wndclass.hCursor = NULL;
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = MAKEINTRESOURCE(1);
    wndclass.lpszClassName = szAppName;

    RegisterClass(&wndclass);

    wndclass2.style = CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNWINDOW;
    wndclass2.lpfnWndProc = WndProc;
    wndclass2.cbClsExtra = 0;
    wndclass2.cbWndExtra = 0;
    wndclass2.hInstance = hInstance;
    wndclass2.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(10));
    wndclass2.hCursor = NULL;
    wndclass2.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass2.lpszMenuName = NULL;
    wndclass2.lpszClassName = szWinName;

    RegisterClass(&wndclass2);

    mainPtr = CreateWindow (szAppName, "Classic Blades of Exile",
                            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                            0,
                            0,
                            588,
                            478,
                            NULL,
                            NULL,
                            hInstance,
                            NULL);

    if (!hPrevInstance)
    {   // initialize
        Get_Path(file_path_name);

        store_hInstance = hInstance;
        accel = LoadAccelerators(hInstance, MAKEINTRESOURCE(1));

        boeSoundsDLL = LoadLibrary("./boesounds.dll");

        if (!boeSoundsDLL)
        {
            MessageBox(mainPtr, "BOESOUNDS.DLL not found", "Error", MB_OK | MB_ICONEXCLAMATION);
            return (-1);
        }

        load_sounds(boeSoundsDLL);
        loadFonts();
        loadCursors();

        SetCursor(sword_curs);
        current_cursor = 124;
        /* cursors loaded */

        data_store = new piles_of_stuff_dumping_type;
        data_store3 = new piles_of_stuff_dumping_type3;
        data_store4 = new piles_of_stuff_dumping_type4;
        data_store5 = new piles_of_stuff_dumping_type5;
        scen_item_list = new scen_item_data_type;

        srand(GetCurrentTime());

        get_reg_data();

        if (display_mode != 5)
            max_window(mainPtr);
        else {
            GetWindowRect(GetDesktopWindow(),&windRECT);
            MoveWindow(mainPtr,(windRECT.right - (588 + 10)) / 2,
                       (windRECT.bottom - (425 + 52)) / 2 ,
                       588 + 10,425 + 52,true);
        }

        shop_sbar = CreateWindow("scrollbar",NULL,
                                 WS_CHILD | WS_TABSTOP | SBS_VERT, shop_sbar_rect.left,shop_sbar_rect.top,shop_sbar_rect.right,shop_sbar_rect.bottom,
                                 mainPtr,(HMENU) 3, store_hInstance,NULL);
        lpsi.fMask = SIF_RANGE;
        lpsi.nMax = 16;
        SetScrollInfo(shop_sbar,SB_CTL,&lpsi,false);
//		SetScrollRange(shop_sbar,SB_CTL,0,16,false);

        ShowWindow(mainPtr, nCmdShow);

        plop_fancy_startup();

        init_screen_locs();

        FlushEvents(2);

        SetTimer(mainPtr,1,620,NULL);
        SetTimer(mainPtr,2,200,NULL);

        file_initialize();

        if (GetDeviceCaps(main_dc,BITSPIXEL) * GetDeviceCaps(main_dc,PLANES) < 8)
        {
            MessageBox(mainPtr,"Blades of Exile is designed for 256 colors. The current graphics device is set for less. Exile 3 is playable with less colors, but will look somewhat odd."	,
                       "Not 256 colors!",MB_OK | MB_ICONEXCLAMATION);
            MessageBox(mainPtr,"For tips on how to get 256 colors, hit F1 for help, and then select 'Getting 256 Colors' from the table of contents."	,
                       "Not 256 colors!",MB_OK | MB_ICONEXCLAMATION);
        }

        menu_activate(0);
        cursor_stay();
        showcursor(true);
        reset_text_bar();

        adjust_window_mode();

        cd_init_dialogs();

        if (game_run_before == false) {
            FCD(986,0);
            WritePrivateProfileString("Blades of Exile", "game_run_before", "1", "./blades.ini");
        }
        else if (give_intro_hint == true) tip_of_day();

    }
    event_handled = false;

    while(GetMessage(&msg,NULL,0,0))
    {
        if (event_handled == false)
        {
            if (!TranslateAccelerator(mainPtr, accel, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    delete scen_item_list;
    delete data_store5;
    delete data_store4;
    delete data_store3;
    if(data_store2 != NULL)
        delete[] data_store2;
    if(scen_headers != NULL)
        delete[] scen_headers;
    delete data_store;

    lose_graphics();

    FreeLibrary((HMODULE) boeSoundsDLL);

    return msg.wParam;
}