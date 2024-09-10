static void test_layout(void)
{
    HWND hRebar;
    REBARBANDINFOA rbi;
    HIMAGELIST himl;
    REBARINFO ri;

    rbsize_results_init();

    hRebar = create_rebar_control();
    check_sizes();
    rbi.cbSize = REBARBANDINFOA_V6_SIZE;
    rbi.fMask = RBBIM_SIZE | RBBIM_CHILDSIZE | RBBIM_CHILD;
    rbi.cx = 200;
    rbi.cxMinChild = 100;
    rbi.cyMinChild = 30;
    rbi.hwndChild = NULL;
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
    check_sizes();

    rbi.fMask |= RBBIM_STYLE;
    rbi.fStyle = RBBS_CHILDEDGE;
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
    check_sizes();

    rbi.fStyle = 0;
    rbi.cx = 200;
    rbi.cxMinChild = 30;
    rbi.cyMinChild = 30;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
    check_sizes();

    rbi.fStyle = RBBS_CHILDEDGE;
    rbi.cx = 68;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
    check_sizes();

    SetWindowLongA(hRebar, GWL_STYLE, GetWindowLongA(hRebar, GWL_STYLE) | RBS_BANDBORDERS);
    check_sizes();      /* a style change won't start a relayout */
    rbi.fMask = RBBIM_SIZE;
    rbi.cx = 66;
    SendMessageA(hRebar, RB_SETBANDINFOA, 3, (LPARAM)&rbi);
    check_sizes();      /* here it will be relayouted */

    /* this will force a new row */
    rbi.fMask = RBBIM_SIZE | RBBIM_CHILDSIZE | RBBIM_CHILD;
    rbi.cx = 200;
    rbi.cxMinChild = 400;
    rbi.cyMinChild = 30;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, 1, (LPARAM)&rbi);
    check_sizes();

    rbi.fMask = RBBIM_STYLE;
    rbi.fStyle = RBBS_HIDDEN;
    SendMessageA(hRebar, RB_SETBANDINFOA, 2, (LPARAM)&rbi);
    check_sizes();

    SendMessageA(hRebar, RB_DELETEBAND, 2, 0);
    check_sizes();
    SendMessageA(hRebar, RB_DELETEBAND, 0, 0);
    check_sizes();
    SendMessageA(hRebar, RB_DELETEBAND, 1, 0);
    check_sizes();

    DestroyWindow(hRebar);

    hRebar = create_rebar_control();
    add_band_w(hRebar, "ABC",     70,  40, 100);
    add_band_w(hRebar, NULL,      40,  70, 100);
    add_band_w(hRebar, NULL,     170, 240, 100);
    add_band_w(hRebar, "MMMMMMM", 60,  60, 100);
    add_band_w(hRebar, NULL,     200, 200, 100);
    check_sizes();
    SendMessageA(hRebar, RB_MAXIMIZEBAND, 1, TRUE);
    check_sizes();
    SendMessageA(hRebar, RB_MAXIMIZEBAND, 1, TRUE);
    check_sizes();
    SendMessageA(hRebar, RB_MAXIMIZEBAND, 2, FALSE);
    check_sizes();
    SendMessageA(hRebar, RB_MINIMIZEBAND, 2, 0);
    check_sizes();
    SendMessageA(hRebar, RB_MINIMIZEBAND, 0, 0);
    check_sizes();

    /* an image will increase the band height */
    himl = ImageList_LoadImageA(GetModuleHandleA("comctl32"), MAKEINTRESOURCEA(121), 24, 2,
            CLR_NONE, IMAGE_BITMAP, LR_DEFAULTCOLOR);
    ri.cbSize = sizeof(ri);
    ri.fMask = RBIM_IMAGELIST;
    ri.himl = himl;
    ok(SendMessageA(hRebar, RB_SETBARINFO, 0, (LPARAM)&ri), "RB_SETBARINFO failed\n");
    rbi.fMask = RBBIM_IMAGE;
    rbi.iImage = 1;
    SendMessageA(hRebar, RB_SETBANDINFOA, 1, (LPARAM)&rbi);
    check_sizes();

    /* after removing it everything is back to normal*/
    rbi.iImage = -1;
    SendMessageA(hRebar, RB_SETBANDINFOA, 1, (LPARAM)&rbi);
    check_sizes();

    /* Only -1 means that the image is not present. Other invalid values increase the height */
    rbi.iImage = -2;
    SendMessageA(hRebar, RB_SETBANDINFOA, 1, (LPARAM)&rbi);
    check_sizes();

    DestroyWindow(hRebar);

    /* VARHEIGHT resizing test on a horizontal rebar */
    hRebar = create_rebar_control();
    SetWindowLongA(hRebar, GWL_STYLE, GetWindowLongA(hRebar, GWL_STYLE) | RBS_AUTOSIZE);
    check_sizes();
    rbi.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_SIZE | RBBIM_STYLE;
    rbi.fStyle = RBBS_VARIABLEHEIGHT;
    rbi.cxMinChild = 50;
    rbi.cyMinChild = 10;
    rbi.cyIntegral = 11;
    rbi.cyChild = 70;
    rbi.cyMaxChild = 200;
    rbi.cx = 90;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);

    rbi.cyChild = 50;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);

    rbi.cyMinChild = 40;
    rbi.cyChild = 50;
    rbi.cyIntegral = 5;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
    check_sizes();

    DestroyWindow(hRebar);

    /* VARHEIGHT resizing on a vertical rebar */
    hRebar = create_rebar_control();
    SetWindowLongA(hRebar, GWL_STYLE, GetWindowLongA(hRebar, GWL_STYLE) | CCS_VERT | RBS_AUTOSIZE);
    check_sizes();
    rbi.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_SIZE | RBBIM_STYLE;
    rbi.fStyle = RBBS_VARIABLEHEIGHT;
    rbi.cxMinChild = 50;
    rbi.cyMinChild = 10;
    rbi.cyIntegral = 11;
    rbi.cyChild = 70;
    rbi.cyMaxChild = 90;
    rbi.cx = 90;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
    check_sizes();

    rbi.cyChild = 50;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
    check_sizes();

    rbi.cyMinChild = 40;
    rbi.cyChild = 50;
    rbi.cyIntegral = 5;
    rbi.hwndChild = build_toolbar(0, hRebar);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
    check_sizes();

    rbsize_results_free();
    DestroyWindow(hRebar);
    ImageList_Destroy(himl);
}