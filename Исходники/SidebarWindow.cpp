BOOL SidebarWindow::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
    // we are interesting in catching TBN_DROPDOWN
    LPNMHDR notifyData = reinterpret_cast<LPNMHDR>(lParam);
    if (notifyData->code == TBN_DROPDOWN) {
        CMenu* sortSubMenu = sortMenu_.GetSubMenu(1);
        if (!sortSubMenu)
            throw Error("Failed to get sort submenu\n");

        //get all the menu items in the current culture
        for (unsigned int index = 0; index < sortSubMenu->GetMenuItemCount(); ++index) {
            ToolbarWindow::updateItem(sortSubMenu, index);
        }

        const UINT trackFlags = TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_RIGHTBUTTON;
        CRect sortButtonRect = settingsSortToolbar_.getItemRect(
                                   sortButtonIndex_);

        settingsSortToolbar_.MapWindowPoints(0, &sortButtonRect);

        sortSubMenu->CheckMenuRadioItem(ID_SORT_LAST_UPDATE_TIME, ID_SORT_NAME,
                                        sortModeToResID(activeSortMode_) , MF_BYCOMMAND);

        // Determine if MS Windows is right aligned and get position of the sort button
        // depending on it
        int x = isBiDi(LOCALE_SYSTEM_DEFAULT) ? sortButtonRect.right : sortButtonRect.left;
        const BOOL trackResult = sortSubMenu->TrackPopupMenu(trackFlags,
                                 x, sortButtonRect.top, this);

        if (FALSE == trackResult)
            throw Error("Failed to track sort menu\n");

        *pResult = TBDDRET_DEFAULT;

        return TRUE;
    }
    // catch the dynamic separator redraw
    if (notifyData->code == NM_CUSTOMDRAW) {
        return onToolbarCustomDraw((LPNMTBCUSTOMDRAW)(lParam),*pResult);
    }

    return CWnd::OnNotify(wParam, lParam, pResult);
}