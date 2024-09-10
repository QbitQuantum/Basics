void DisplayView::PrepareCompatibleFiltersMenu(CMenu &menu, Pin *pin)
{
    /*
    	Enumerate output mediatypes and look for compatible
    	filters.
    */

    compatible_filters.filters.RemoveAll();

    // ignore invalid and connected pins
    if (!pin || !(pin->pin) || (pin->dir == PINDIR_INPUT)) return ;
    if (pin->connected) return ;

    // enumerate media types
    DSUtil::MediaTypes			mtypes;

    DSUtil::EnumMediaTypes(pin->pin, mtypes);
    if (mtypes.GetCount() <= 0) return ;

    // now try to enumerate compatible filters
    int ret = compatible_filters.EnumerateCompatible(mtypes, MERIT_UNLIKELY, false, render_params.exact_match_mode);
    if ((ret == 0) && (compatible_filters.filters.GetCount() > 0)) {

        CMenu		submenu;
        submenu.CreatePopupMenu();
        CMenu		&active_menu = submenu;

        for (int i=0; i<compatible_filters.filters.GetCount(); i++) {
            DSUtil::FilterTemplate	&filt = compatible_filters.filters[i];

            CString		merit;
            merit.Format(_T("%08x)"), filt.merit);
            merit = merit.MakeUpper();

            int idx = active_menu.GetMenuItemCount();

            CString		name = filt.name + _T("\t(0x") + merit;
            active_menu.InsertMenu(idx, MF_BYPOSITION | MF_STRING, ID_COMPATIBLE_FILTER + i, name);
        }

        // do insert the menu
        int		count = menu.GetMenuItemCount();
        menu.InsertMenu(count++, MF_BYPOSITION | MF_SEPARATOR);
        menu.InsertMenu(count, MF_BYPOSITION | MF_STRING, 0, _T("Compatible filters"));
        menu.ModifyMenu(count, MF_BYPOSITION | MF_POPUP | MF_STRING, (UINT_PTR)submenu.m_hMenu, _T("Compatible filters"));
        submenu.Detach();
    }
}