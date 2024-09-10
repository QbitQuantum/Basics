ImageBuffer::ImageBuffer(const IntSize& size, ColorSpace, RenderingMode renderingMode, bool& success)
    : m_data(size)
    , m_size(size)
    , m_accelerateRendering(false)
{
    OwnPtr<SkCanvas> canvas = adoptPtr(skia::TryCreateBitmapCanvas(size.width(), size.height(), false));
    if (!canvas) {
        success = false;
        return;
    }

    m_data.m_canvas = canvas.release();
    m_data.m_platformContext.setCanvas(m_data.m_canvas.get());
    m_context = adoptPtr(new GraphicsContext(&m_data.m_platformContext));
    m_context->platformContext()->setDrawingToImageBuffer(true);

    // Make the background transparent. It would be nice if this wasn't
    // required, but the canvas is currently filled with the magic transparency
    // color. Can we have another way to manage this?
    m_data.m_canvas->drawARGB(0, 0, 0, 0, SkXfermode::kClear_Mode);
    if (renderingMode == Accelerated) {
        GraphicsContext3D* context3D = SharedGraphicsContext3D::create(0);
        if (context3D) {
            context3D->makeContextCurrent();
            GrContext* gr = context3D->grContext();
            if (gr) {
                gr->resetContext();
                GrTextureDesc desc;
                desc.fFlags = kRenderTarget_GrTextureFlagBit;
                desc.fAALevel = kNone_GrAALevel;
                desc.fWidth = size.width();
                desc.fHeight = size.height();
                desc.fFormat = kRGBA_8888_GrPixelConfig;
                SkAutoTUnref<GrTexture> texture(gr->createUncachedTexture(desc, 0, 0));
                if (texture.get()) {
                    m_data.m_canvas->setDevice(new SkGpuDevice(gr, texture.get()))->unref();
                    m_context->platformContext()->setGraphicsContext3D(context3D);
                    m_accelerateRendering = true;
#if USE(ACCELERATED_COMPOSITING)
                    m_data.m_platformLayer = Canvas2DLayerChromium::create(context3D);
                    m_data.m_platformLayer->setTextureId(texture.get()->getTextureHandle());
#endif
                }
            }
        }
    }

    success = true;
}