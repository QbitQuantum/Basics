static HRESULT WINAPI
NewMenu_ContextMenu3_HandleMenuMsg2(IContextMenu3 *iface, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *result)
{
    NewMenuImpl *This = impl_from_IContextMenu3(iface);

    TRACE("(%p)->(%u, %lx, %lx, %p)\n", This, uMsg, wParam, lParam, result);

    switch (uMsg)
    {
        case WM_MEASUREITEM:
        {
            MEASUREITEMSTRUCT *mis = (MEASUREITEMSTRUCT *)lParam;
            if (!mis || mis->CtlType != ODT_MENU)
                break;

            if (This->folder_cmd == mis->itemID)
            {
                mis->itemWidth = GetSystemMetrics(SM_CXSMICON);
                mis->itemHeight = GetSystemMetrics(SM_CYSMICON);
            }

            if (result) *result = TRUE;
            break;
        }

        case WM_DRAWITEM:
        {
            DRAWITEMSTRUCT *dis = (DRAWITEMSTRUCT *)lParam;
            HICON icon = 0;
            UINT x, y;

            if (!dis || dis->CtlType != ODT_MENU)
                break;

            if (This->folder_cmd == dis->itemID)
                icon = This->icon_folder;

            if (!icon)
                break;

            x = (dis->rcItem.right - dis->rcItem.left - GetSystemMetrics(SM_CXSMICON)) / 2;
            y = (dis->rcItem.bottom - dis->rcItem.top - GetSystemMetrics(SM_CYSMICON)) / 2;
            DrawStateW(dis->hDC, NULL, NULL, (LPARAM)icon, 0, x, y, 0, 0, DST_ICON | DSS_NORMAL);

            if (result) *result = TRUE;
            break;
        }
    }

    return S_OK;
}