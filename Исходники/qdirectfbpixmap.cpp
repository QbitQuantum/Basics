void QDirectFBPixmapData::copy(const QPixmapData *data, const QRect &rect)
{
    if (data->classId() != DirectFBClass) {
        QPixmapData::copy(data, rect);
        return;
    }

    IDirectFBSurface *src = static_cast<const QDirectFBPixmapData*>(data)->surface;

    DFBSurfaceDescription description;
    description.flags = DFBSurfaceDescriptionFlags(DSDESC_WIDTH |
                                                   DSDESC_HEIGHT |
                                                   DSDESC_PIXELFORMAT);
    description.width = rect.width();
    description.height = rect.height();
    src->GetPixelFormat(src, &description.pixelformat);

    IDirectFB *fb = QDirectFBScreen::instance()->dfb();

    DFBResult result = fb->CreateSurface(fb, &description, &surface);
    if (result != DFB_OK) {
        DirectFBError("QDirectFBPixmapData::copy()", result);
        setSerialNumber(0);
        return;
    }

#ifndef QT_NO_DIRECTFB_PALETTE
    IDirectFBPalette *palette;
    src->GetPalette(src, &palette);
    surface->SetPalette(surface, palette);
#endif

    surface->SetBlittingFlags(surface, DSBLIT_NOFX);
    const DFBRectangle blitRect = { rect.x(), rect.y(),
                                    rect.width(), rect.height() };
    result = surface->Blit(surface, src, &blitRect, 0, 0);
    if (result != DFB_OK)
        DirectFBError("QDirectFBPixmapData::copy()", result);

    setSerialNumber(++global_ser_no);
}