void CIconSelectMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // TODO :  指定された項目を描画するためのコードを追加してください。
    MENUITEM* pItem = reinterpret_cast< MENUITEM*>( lpDrawItemStruct->itemData);
    if( NULL != pItem)
    {
        CDC cDC;
        if( cDC.Attach( lpDrawItemStruct->hDC))
        {
            int nSaveID = cDC.SaveDC();

            if( 0 < nSaveID)
            {
                COLORREF clrFore;
                COLORREF clrBack;
                if( ODS_SELECTED & lpDrawItemStruct->itemState)
                {
                    clrFore = ::GetSysColor( COLOR_HIGHLIGHTTEXT);
                    clrBack = ::GetSysColor( COLOR_HIGHLIGHT);
                }
                else
                {
                    clrFore = ::GetSysColor( COLOR_MENUTEXT);
                    clrBack = ::GetSysColor( COLOR_MENU);
                }

                cDC.SetBkColor( clrBack);
                cDC.SetTextColor( clrFore);
                cDC.FillSolidRect( &lpDrawItemStruct->rcItem, clrBack);

                int nXSpace = ::GetSystemMetrics( SM_CXFRAME);

                int nLeft = 12;//( ( lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left) - pItem->nWidth) / 2;

                CDC cMemDC;
                cMemDC.CreateCompatibleDC( &cDC);
                cMemDC.SelectObject( pItem->hBitmap);
                cDC.BitBlt( nLeft + lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top, _ICON_WIDTH, _ICON_HEIGHT, &cMemDC, 0, 0, SRCCOPY);
                cDC.TextOut( nLeft + lpDrawItemStruct->rcItem.left + _ICON_WIDTH + nXSpace, lpDrawItemStruct->rcItem.top, pItem->szItemName);


                cDC.RestoreDC( nSaveID);
            }
            cDC.Detach();
        }
    }
}