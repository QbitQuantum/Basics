static SkSurface* createSurface(GraphicsContext3D* context3D, const IntSize& size)
{
    ASSERT(!context3D->webContext()->isContextLost());
    GrContext* gr = context3D->grContext();
    if (!gr)
        return 0;
    gr->resetContext();
    SkImage::Info info;
    info.fWidth = size.width();
    info.fHeight = size.height();
    info.fColorType = SkImage::kPMColor_ColorType;
    info.fAlphaType = SkImage::kPremul_AlphaType;
    return SkSurface::NewRenderTarget(gr, info);
}