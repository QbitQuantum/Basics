void Menu_AddImage(HBITMAP hBitmap, COLORREF crTrans)
{
    HBITMAP hbm, hbmGray;
    COLORREF crBack;

    hbm     = Paint_Bitmap_CopyBitmap(hBitmap);
    ImageList_AddMasked(hImageListHot, hbm, crTrans);
    DeleteObject(hbm);

    crBack  = crTrans;
    
    hbm     = Paint_Bitmap_CopyBitmap(hBitmap);
    hbmGray = Paint_Bitmap_GrayScale(hbm, 4.5, &crBack);

    ImageList_AddMasked(hImageListCold, hbmGray, crBack);

    /* Clear up the mess =\ */
    DeleteObject(hbm);
    DeleteObject(hbmGray);
}