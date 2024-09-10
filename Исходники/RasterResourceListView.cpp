void CRasterResourceListCtrl::_OnInitListView(int cItems)
{
    // Put an imagelist in the view, for our pic previews.

    // Destroy any old list
    if (_himlPics)
    {
        ImageList_Destroy(_himlPics);
        _himlPics = NULL;
    }

    CSize sizeImages(VIEW_IMAGE_SIZE, VIEW_IMAGE_SIZE);
    // Note: this color depth must match that which we get back from the ViewResource
    // Also: ILC_MASK must be specified, because of the overlay
    _himlPics = ImageList_Create(sizeImages.cx, sizeImages.cy, ILC_COLOR8 | ILC_MASK, cItems, 30);
    
    if (_himlPics)
    {
        CImageList *pTemp = CImageList::FromHandle(_himlPics);
        if (pTemp)
        {
            HIMAGELIST himlOld = (HIMAGELIST)SetImageList(pTemp, LVSIL_NORMAL);
        }
        // pTemp is a temporary object that we don't need to delete.

        // Load an overlay image to use for "unused" items
        HBITMAP hbmOverlay = LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_OVERLAYOLD40));
        if (hbmOverlay)
        {
            int iOverlayImageIndex = ImageList_AddMasked(_himlPics, hbmOverlay, RGB(255, 0, 255));
            ImageList_SetOverlayImage(_himlPics, iOverlayImageIndex, OVERLAYINDEX_UNUSED);
            DeleteObject(hbmOverlay);
        }

        HBITMAP hbmCorrupt = LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_CORRUPTRESOURCE));
        if (hbmCorrupt)
        {
            _iCorruptBitmapIndex = ImageList_Add(_himlPics, hbmCorrupt, NULL);
            DeleteObject(hbmCorrupt);
        }
    }

    // Adjust the icon spacing so things don't look too spread out.
    CSize sizeSpacing(sizeImages.cx + 20, sizeImages.cy + 30);
    SetIconSpacing(sizeSpacing);

    // LVS_EX_BORDERSELECT, supported on IE 4.0 or later. -> Removed, as it causes problems in details view
    // LVS_EX_DOUBLEBUFFER, supported on XP or later.
    SetExtendedStyle(GetExtendedStyle() | 0x00010000 | LVS_EX_INFOTIP);

}