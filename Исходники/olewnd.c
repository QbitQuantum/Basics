void HTMLDocument_ShowContextMenu(HTMLDocument *This, DWORD dwID, POINT *ppt)
{
    HMENU menu_res, menu;
    HRESULT hres;

    hres = IDocHostUIHandler_ShowContextMenu(This->hostui, dwID, ppt,
            (IUnknown*)CMDTARGET(This), (IDispatch*)HTMLDOC(This));
    if(hres == S_OK)
        return;

    menu_res = LoadMenuW(hInst, MAKEINTRESOURCEW(IDR_BROWSE_CONTEXT_MENU));
    menu = GetSubMenu(menu_res, dwID);

    TrackPopupMenu(menu, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
            ppt->x, ppt->y, 0, This->hwnd, NULL);

    DestroyMenu(menu_res);
}