/*!
    \internal
*/
void QProxyScreen::configure()
{
    if (!realScreen)
        return;

    d = realScreen->depth();
    w = realScreen->width();
    h = realScreen->height();
    dw = realScreen->deviceWidth();
    dh = realScreen->deviceHeight();
    lstep = realScreen->linestep();
    data = realScreen->base();
    lstep = realScreen->linestep();
    size = realScreen->screenSize();
    physWidth = realScreen->physicalWidth();
    physHeight = realScreen->physicalHeight();
    pixeltype = realScreen->pixelType();
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
    setFrameBufferLittleEndian(realScreen->frameBufferLittleEndian());
#endif

    setOffset(realScreen->offset());
    setPixelFormat(realScreen->pixelFormat());

#ifdef QT_QWS_CLIENTBLIT
    setSupportsBlitInClients(realScreen->supportsBlitInClients());
#endif
}