void InitMenuPopup(HMENU menu)
{
    HWND win;
    BOOL mf_state;
    BOOL x_state;
    int selstart, selend;
    SetWindowMenu();
    SetMenuCheckedState(menu, DID_PROJWND, IDM_VIEWPROJECT);
    SetMenuCheckedState(menu, DID_PROPSWND, IDM_VIEWPROPS);
    SetMenuCheckedState(menu, DID_INFOWND, IDM_VIEWINFO);
    SetMenuCheckedState(menu, DID_ERRWND, IDM_VIEWERR);
    SetMenuCheckedState(menu, DID_BROWSEWND, IDM_VIEWBROWSE);
    SetMenuCheckedState(menu, DID_STACKWND, IDM_VIEWSTACK);
    SetMenuCheckedState(menu, DID_THREADWND, IDM_VIEWTHREAD);
    {
        MENUITEMINFO info;
    
        info.cbSize = sizeof(MENUITEMINFO);
        info.fMask = MIIM_STATE;
        GetMenuItemInfo(menu, IDM_VIEWASM, MF_BYCOMMAND, &info);
        info.fState = (info.fState &~MFS_CHECKED) | (hwndASM ?
            MFS_CHECKED : 0);
        SetMenuItemInfo(menu, IDM_VIEWASM, MF_BYCOMMAND, &info);
    }
    SetMenuCheckedState(menu, DID_MEMWND, IDM_VIEWMEM);
    SetMenuCheckedState(menu, DID_MEMWND+1, IDM_VIEWMEM2);
    SetMenuCheckedState(menu, DID_MEMWND+2, IDM_VIEWMEM3);
    SetMenuCheckedState(menu, DID_MEMWND+3, IDM_VIEWMEM4);
    SetMenuCheckedState(menu, DID_REGWND, IDM_VIEWREGISTER);
    SetMenuCheckedState(menu, DID_WATCHWND, IDM_VIEWWATCH);
    SetMenuCheckedState(menu, DID_WATCHWND+1, IDM_VIEWWATCH2);
    SetMenuCheckedState(menu, DID_WATCHWND+2, IDM_VIEWWATCH3);
    SetMenuCheckedState(menu, DID_WATCHWND+3, IDM_VIEWWATCH4);
    SetMenuCheckedState(menu, DID_LOCALSWND, IDM_VIEWLOCALS);
    SetMenuCheckedState(menu, DID_BREAKWND, IDM_VIEWBP);

    win = (HWND)SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0);
    mf_state = MF_GRAYED;
    if (editWindows && IsWindow(win) && (IsEditWindow(win) || IsResourceWindow(win)))
    {
        mf_state = MF_ENABLED;
    }
    EnableMenuItem(menu, IDM_SAVEAS, mf_state);
    EnableMenuItem(menu, IDM_SAVE, mf_state);
    EnableMenuItem(menu, IDM_CUT, mf_state);
    EnableMenuItem(menu, IDM_COPY, mf_state);
    EnableMenuItem(menu, IDM_PASTE, mf_state);
    EnableMenuItem(menu, IDM_CLOSEWINDOW, mf_state);
    EnableMenuItem(menu, IDM_CLOSE, mf_state);
    mf_state = MF_GRAYED;
    if (editWindows && IsWindow(win) && IsEditWindow(win))
    {
        mf_state = MF_ENABLED;
        SendMessage(GetDlgItem(win, ID_EDITCHILD), EM_GETSEL, (WPARAM)
            &selstart, (LPARAM) &selend);
    }
    EnableMenuItem(menu, IDM_COPYWINDOW, mf_state);
    EnableMenuItem(menu, IDM_PRINT, mf_state);
    EnableMenuItem(menu, IDM_TOUPPER, (mf_state == MF_ENABLED &&
        selstart != selend) ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(menu, IDM_TOLOWER, (mf_state == MF_ENABLED &&
        selstart != selend) ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(menu, IDM_INDENT, (mf_state == MF_ENABLED &&
        selstart != selend) ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(menu, IDM_UNINDENT, (mf_state == MF_ENABLED &&
        selstart != selend) ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(menu, IDM_COMMENT, (mf_state == MF_ENABLED &&
        selstart != selend) ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(menu, IDM_UNCOMMENT, (mf_state == MF_ENABLED &&
        selstart != selend) ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(menu, IDM_SELECTALL, mf_state);
    EnableMenuItem(menu, IDM_FIND, mf_state);

    x_state = mf_state;
    if (!AnyBookmarks())
        x_state = MF_GRAYED;
    EnableMenuItem(menu,IDM_NEXTBOOKMARK,x_state) ;
    EnableMenuItem(menu,IDM_PREVBOOKMARK,x_state) ;
    EnableMenuItem(menu,IDM_NEXTBOOKMARKFILE,x_state) ;
    EnableMenuItem(menu,IDM_PREVBOOKMARKFILE,x_state) ;
    EnableMenuItem(menu,IDM_BOOKMARKWINDOW,x_state) ;
    EnableMenuItem(menu,IDM_REMOVEBOOKMARKS,x_state) ;
    EnableMenuItem(menu, IDM_FIND, mf_state);
    //      EnableMenuItem(menu,IDM_FINDINFILES,mf_state) ;
    EnableMenuItem(menu, IDM_FINDNEXT, mf_state);
    EnableMenuItem(menu, IDM_REPLACE, mf_state);
    x_state = mf_state;
    if (win == hwndASM)
        x_state = MF_ENABLED;
    EnableMenuItem(menu, IDM_GOTO, x_state);
    if (defaultWorkArea || !PropGetBool(NULL, "BROWSE_INFORMATION")) 
        mf_state = MF_GRAYED;   
    EnableMenuItem(menu, IDM_BROWSETODECLARATION, mf_state);
    EnableMenuItem(menu, IDM_BROWSETODEFINITION, mf_state);

    if (defaultWorkArea || !PropGetBool(NULL, "BROWSE_INFORMATION")) 
        mf_state = MF_GRAYED;   
    else
        mf_state = MF_ENABLED;
    EnableMenuItem(menu, IDM_VIEWBROWSE, mf_state);
    EnableMenuItem(menu,IDM_BROWSETO,mf_state) ;
    EnableMenuItem(menu,IDM_BROWSEBACK,mf_state) ;
    EnableMenuItem(menu, IDM_BOOKMARK, mf_state);
    if (!making && IsEditWindow(win))
    {
        if (!FindItemByWind(win))
            mf_state = MF_GRAYED;
        else
            mf_state = MF_ENABLED;
    }
    else
        mf_state = MF_GRAYED;

    EnableMenuItem(menu, IDM_COMPILEFILE, mf_state);
    mf_state = MF_GRAYED;
    if (SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0))
        mf_state = MF_ENABLED;
    EnableMenuItem(menu, IDM_CLOSEALLWINDOWS, mf_state);
    EnableMenuItem(menu, IDM_CASCADE, mf_state);
    EnableMenuItem(menu, IDM_TILEHORIZ, mf_state);
    EnableMenuItem(menu, IDM_TILEVERT, mf_state);
    EnableMenuItem(menu, IDM_ARRANGE, mf_state);
    EnableMenuItem(menu, IDM_SAVEALL, mf_state);
    EnableMenuItem(menu, IDM_SAVEALL2, mf_state);

    EnableMenuItem(menu, IDM_NEWPROJECT, MF_ENABLED);
    EnableMenuItem(menu, IDM_VIEWPROJECT, MF_ENABLED);
    if (making || hwndGeneralProps)
        mf_state = MF_GRAYED;
    else
        mf_state = MF_ENABLED;
    EnableMenuItem(menu, IDM_CLOSEWS, mf_state);
    EnableMenuItem(menu, IDM_GENMAKE, mf_state);
    EnableMenuItem(menu, IDM_MAKE, mf_state);
    EnableMenuItem(menu, IDM_BUILDALL, mf_state);
    EnableMenuItem(menu, IDM_BUILDSELECTED, mf_state);
    mf_state = MF_GRAYED;
    if (!making && !hwndGeneralProps)
        mf_state = MF_ENABLED;
    EnableMenuItem(menu, IDM_GENERALPROPERTIES, mf_state);
    EnableMenuItem(menu, IDM_SELECTPROFILE, mf_state);
    EnableMenuItem(menu, IDM_BUILDRULES, mf_state);
    
    if (!activeProject)
        mf_state = MF_GRAYED;
    EnableMenuItem(menu, IDM_ACTIVEPROJECTPROPERTIES, mf_state);
    EnableMenuItem(menu, IDM_PROJECTPROPERTIES, mf_state);
    EnableMenuItem(menu, IDM_PROJECTDEPENDS, mf_state);
    EnableMenuItem(menu, IDM_RUNNODEBUG, mf_state);
    if (making)
        mf_state = MF_ENABLED;
    else
        mf_state = MF_GRAYED;
    EnableMenuItem(menu, IDM_STOPBUILD, mf_state);

    if (IsWindow(win))
    {
            EnableMenuItem(menu, IDM_UNDO, SendMessage(win, EM_CANUNDO,
                0, 0) ? MF_ENABLED : MF_GRAYED);
            EnableMenuItem(menu, IDM_REDO, SendMessage(win, EM_CANREDO,
                0, 0) ? MF_ENABLED : MF_GRAYED);
    }
    if (uState == notDebugging)
        mf_state = MF_ENABLED;
    else
        mf_state = MF_GRAYED;
    EnableMenuItem(menu, IDM_OPENWS, mf_state);
    EnableMenuItem(menu, IDM_CLOSEWS, mf_state);
    EnableMenuItem(menu, IDM_NEWWS, mf_state);
    EnableMenuItem(menu, IDM_REOPENWS, mf_state);
    EnableMenuItem(menu, IDM_IMPORTWS, mf_state);

    mf_state = ((uState == notDebugging || uState == atException || uState == atBreakpoint) && !making && activeProject) ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(menu, IDM_RUN, mf_state);

    mf_state = (uState != notDebugging && (uState == atException || uState == atBreakpoint)  && !making && activeProject) ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(menu, IDM_STOPDEBUGGING, mf_state);
    EnableMenuItem(menu, IDM_RUNTO, mf_state);
    EnableMenuItem(menu, IDM_SCROLLTOBP, mf_state);
//    EnableMenuItem(menu, IDM_VIEWBP, mf_state);
    EnableMenuItem(menu, IDM_VIEWASM, mf_state);
    EnableMenuItem(menu, IDM_VIEWMEM, mf_state);
    EnableMenuItem(menu, IDM_VIEWMEM2, mf_state);
    EnableMenuItem(menu, IDM_VIEWMEM3, mf_state);
    EnableMenuItem(menu, IDM_VIEWMEM4, mf_state);
    EnableMenuItem(menu, IDM_VIEWREGISTER, mf_state);
    EnableMenuItem(menu, IDM_VIEWSTACK, mf_state);
    EnableMenuItem(menu, IDM_VIEWWATCH, mf_state);
    EnableMenuItem(menu, IDM_VIEWWATCH2, mf_state);
    EnableMenuItem(menu, IDM_VIEWWATCH3, mf_state);
    EnableMenuItem(menu, IDM_VIEWWATCH4, mf_state);
    EnableMenuItem(menu, IDM_VIEWLOCALS, mf_state);
    EnableMenuItem(menu, IDM_VIEWTHREAD, mf_state);
    EnableMenuItem(menu, IDM_HBREAK, mf_state);
    EnableMenuItem(menu, IDM_DATABREAKPOINT, mf_state);
    EnableMenuItem(menu, IDM_FUNCTIONBREAKPOINT, mf_state);
    
    mf_state = uState == Running ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(menu, IDM_STOP, mf_state);

    {
        BOOL state = TagAnyDisabledBreakpoints() || hbpAnyDisabledBreakpoints() || databpAnyDisabledBreakpoints();
        ModifyMenu(menu, IDM_DISABLEALLBREAKPOINTS, MF_BYCOMMAND | MF_STRING, IDM_DISABLEALLBREAKPOINTS, state ? "E&nable All Breakpoints" : "D&isable All Breakpoints");
        
    }
    mf_state = (TagAnyBreakpoints() || hbpAnyBreakpoints() || databpAnyBreakpoints()) ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(menu, IDM_REMOVEALLBREAKPOINTS, mf_state);
    EnableMenuItem(menu, IDM_DISABLEALLBREAKPOINTS, mf_state);

    mf_state = MF_GRAYED;
    if (activeProject && GetResData(activeProject))
        mf_state = MF_ENABLED;       
    EnableMenuItem(menu, IDM_NEWRESOURCE, mf_state);
    mf_state = MF_GRAYED;
    if (IsWindow(win) && IsResourceWindow(win))
    {
        struct resRes *res = (struct resRes *)GetWindowLong(win, 0);
        if (res->resource->itype == RESTYPE_DIALOG)
            mf_state = MF_ENABLED;
    }
    EnableMenuItem(menu, IDM_CREATIONORDER, mf_state);
    EnableMenuItem(menu, IDM_SETTABSTOPS, mf_state);
    EnableMenuItem(menu, IDM_SETGROUPFLAGS, mf_state);
    EnableMenuItem(menu, IDM_GRIDMENU, mf_state);
    EnableMenuItem(menu, IDM_SHOWGRID, mf_state);
    EnableMenuItem(menu, IDM_SNAPTOGRID, mf_state);
    if (mf_state == MF_ENABLED)
    {
        if (snapToGrid)
        {
            CheckMenuItem( menu, IDM_SNAPTOGRID, MF_BYCOMMAND | MF_CHECKED);
        }
        else
        {
            CheckMenuItem( menu, IDM_SNAPTOGRID, MF_BYCOMMAND);
        }
        if (showGrid)
        {
            CheckMenuItem( menu, IDM_SHOWGRID, MF_BYCOMMAND | MF_CHECKED);
        }
        else
        {
            CheckMenuItem( menu, IDM_SHOWGRID, MF_BYCOMMAND);
        }
    }
    mf_state = MF_GRAYED;
    if (IsWindow(win) && IsResourceWindow(win))
    {
        struct resRes *res = (struct resRes *)GetWindowLong(win, 0);
        if (res->resource->itype == RESTYPE_BITMAP || res->resource->itype == RESTYPE_CURSOR || res->resource->itype == RESTYPE_ICON)
            mf_state = MF_ENABLED;
    }
    EnableMenuItem(menu, IDM_FLIPMENU, mf_state);
    EnableMenuItem(menu, IDM_ROTATEMENU, mf_state);
    EnableMenuItem(menu, IDM_CLEAR, mf_state);
    EnableMenuItem(menu, IDM_CLEARSELECTION, mf_state);

    //         mf_state = uState == atBreakpoint || uState == atException ? MF_ENABLED : MF_GRAYED ;
    //         EnableMenuItem(menu,IDM_HBREAK, mf_state ) ;

    mf_state = PropGetInt(NULL, "MSDN_HELP_MODE") == 0 ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(menu,IDM_CONFIGWEBHELP, mf_state ) ;


}