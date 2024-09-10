static IPictureDisp *QPixmapToIPicture(const QPixmap &pixmap)
{
#if defined(Q_OS_WINCE)
    Q_UNUSED(pixmap);
    return 0;
#else
    IPictureDisp *pic = 0;
    
    PICTDESC desc;
    desc.cbSizeofstruct = sizeof(PICTDESC);
    desc.picType = PICTYPE_BITMAP;
    
    desc.bmp.hbitmap = 0;
    desc.bmp.hpal = QColormap::hPal();
    
    if (!pixmap.isNull()) {
        desc.bmp.hbitmap = pixmap.toWinHBITMAP();
        Q_ASSERT(desc.bmp.hbitmap);
    }

    HRESULT res = OleCreatePictureIndirect(&desc, IID_IPictureDisp, true, (void**)&pic);
    if (res != S_OK) {
        if (pic) pic->Release();
        pic = 0;
#if defined(QT_CHECK_STATE)
        qWarning("QPixmapToIPicture: Failed to create IPicture");
#endif
    }
    return pic;
#endif
}