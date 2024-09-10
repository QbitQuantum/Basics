void ProxyScreen::configure()
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

    setOffset(realScreen->offset());
    setPixelFormat(realScreen->pixelFormat());
}