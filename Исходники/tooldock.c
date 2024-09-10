VOID
TbdInitializeDocks(PTOOLBAR_DOCKS TbDocks,
                   HWND hWndParent,
                   PVOID Context,
                   PDOCKBAR_PARENTRESIZE ParentResizeProc)
{
    DWORD rbStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
                        CCS_NODIVIDER | CCS_NOPARENTALIGN | CCS_NOMOVEY | CCS_NOMOVEX  |
                        RBS_VARHEIGHT | RBS_AUTOSIZE;

    DOCK_POSITION Position;

    TbDocks->hParent = hWndParent;
    TbDocks->Context = Context;
    TbDocks->ParentResize = ParentResizeProc;

    for (Position = TOP_DOCK; Position < NO_DOCK; Position++)
    {
        switch (Position)
        {
            case LEFT_DOCK:
            case RIGHT_DOCK:
                rbStyle |= CCS_VERT;
                break;
            default:
                rbStyle &= ~CCS_VERT;
                break;
        }

        TbDocks->hRebar[Position] = CreateWindowEx(WS_EX_TOOLWINDOW,
                                                   REBARCLASSNAME,
                                                   NULL,
                                                   rbStyle,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   TbDocks->hParent,
                                                   NULL,
                                                   hInstance,
                                                   NULL);

        if (TbDocks->hRebar[Position] != NULL)
        {
            SetWindowSubclass(TbDocks->hRebar[Position],
                              RebarSubclassProc,
                              1,
                              (DWORD_PTR)TbDocks);
        }
    }
}