void KGIniListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    LPKGLISTITEM pItem = (LPKGLISTITEM)GetItemData(lpDrawItemStruct->itemID);
    USER_ITEM_DATA itemData;

    KGListCtrl::DrawItem(lpDrawItemStruct);

    KG_PROCESS_ERROR(pItem);

    pItem->GetStructData(&itemData, sizeof(itemData));

    if (itemData.dwValueType == VALUE_COLOR)
    {
        COLORREF colorRef = (COLORREF)atoi(itemData.szPropertyValue);
        CRect rect;
        GetSubItemRect(
            lpDrawItemStruct->itemID, 1, LVIR_BOUNDS, rect
        );
        rect.left += 12;
        rect.top  += 2;
        rect.bottom -= 1;
        rect.right = rect.left + rect.Height();
        pDC->FillRect(&rect, &CBrush(colorRef));
        pDC->Draw3dRect(&rect, RGB(100, 100, 100), RGB(100, 100, 100));
    }

Exit0:
    return;
}