void CMyCombo::SetImages(int nImages, UINT ImageID)
{
    if (m_himlImages) {
        ImageList_Destroy(m_himlImages);
        m_himlImages = NULL;
    }

    HBITMAP hbm = LoadBitmap(MAKEINTRESOURCE(ImageID));
    BITMAP bm = {0};
    ::GetObject(hbm, sizeof(BITMAP), &bm);
    int iImageWidth  = bm.bmWidth / nImages;
    int iImageHeight = bm.bmHeight;
    COLORREF crMask = RGB(255, 0, 255);
    m_himlImages = ImageList_Create(iImageWidth, iImageHeight, ILC_COLOR32 | ILC_MASK, nImages, 0);
    ImageList_AddMasked(m_himlImages, hbm, crMask);
    ::DeleteObject(hbm);
}