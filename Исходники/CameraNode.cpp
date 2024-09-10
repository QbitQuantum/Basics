void CameraNode::open()
{
    m_pCamera->startCapture();
    setViewport(-32767, -32767, -32767, -32767);
    PixelFormat pf = getPixelFormat();
    IntPoint size = getMediaSize();
    bool bMipmap = getMaterial().getUseMipmaps();
    m_pTex = GLTexturePtr(new GLTexture(size, pf, bMipmap));
    m_pTex->enableStreaming();
    getSurface()->create(pf, m_pTex);

    BitmapPtr pBmp = m_pTex->lockStreamingBmp();
    if (pf == B8G8R8X8 || pf == B8G8R8A8) {
        FilterFill<Pixel32> Filter(Pixel32(0,0,0,255));
        Filter.applyInPlace(pBmp);
    } else if (pf == I8) {
        FilterFill<Pixel8> Filter(0);
        Filter.applyInPlace(pBmp);
    } 
    m_pTex->unlockStreamingBmp(true);
    setupFX(true);
}