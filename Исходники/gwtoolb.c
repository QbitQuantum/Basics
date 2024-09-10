void gw_create_toolbar (GUI_WINDOW *gwp)

{
    RECT        rect;
#if _MSC_VER <= 900
    int         i;
#endif
    
    /* check that we can do it. */
    if (!o_toolbar (gwp))
        return;
    if (gwp->toolbarHWnd != NULL)
        return;

    /* get borders size */
    cxborder = GetSystemMetrics (SM_CXBORDER);
    cyborder = GetSystemMetrics (SM_CYBORDER);

    /* create the toolbar */
#if _MSC_VER > 900
    gwp->toolbarHWnd = CreateToolbarEx (gwp->frameHWnd,
                                       WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS,
                                       1, 15, hInst, IDT_ELVIS,
                                       buttons, 21, 16, 15, 15, 14,
                                       sizeof (TBBUTTON));
#else
    gwp->toolbarHWnd = CreateToolbar (gwp->frameHWnd,
                                     WS_CHILD | WS_VISIBLE,
                                     1, 15, hInst, IDT_ELVIS,
                                     buttons, 1);
    for (i = 1; i < 21; i++)
        SendMessage (gwp->toolbarHWnd, TB_ADDBUTTONS, 1, (LPARAM)&buttons[i]);
#endif

    /* size the toolbar */
    GetClientRect (gwp->frameHWnd, &rect);
    gw_size_toolbar (gwp, &rect);
}