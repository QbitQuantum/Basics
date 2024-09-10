    void ShellUi::AddMenu()
    {
        xassert(_hwnd);

        // create shell icon
        _ShellIconCreate();

        // create popup menu
        _menu = CreatePopupMenu();

        // add exit option
        InsertMenu( _menu, 0, MF_BYPOSITION | MF_STRING, ID_EXIT, L"E&xit" );
        SetMenuDefaultItem( _menu, ID_EXIT, FALSE );
    }