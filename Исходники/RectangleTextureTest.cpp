DEF_GPUTEST_FOR_GL_RENDERING_CONTEXTS(RectangleTexture, reporter, ctxInfo) {
    GrContext* context = ctxInfo.grContext();
    GrProxyProvider* proxyProvider = context->contextPriv().proxyProvider();
    sk_gpu_test::GLTestContext* glContext = ctxInfo.glContext();
    static const int kWidth = 13;
    static const int kHeight = 13;

    GrColor pixels[kWidth * kHeight];
    for (int y = 0; y < kHeight; ++y) {
        for (int x = 0; x < kWidth; ++x) {
            pixels[y * kWidth + x] = y * kWidth + x;
        }
    }

    for (auto origin : { kBottomLeft_GrSurfaceOrigin, kTopLeft_GrSurfaceOrigin }) {
        bool useBLOrigin = kBottomLeft_GrSurfaceOrigin == origin;

        GrGLuint rectTexID = glContext->createTextureRectangle(kWidth, kHeight, GR_GL_RGBA,
                                                               GR_GL_RGBA, GR_GL_UNSIGNED_BYTE,
                                                               pixels);

        if (!rectTexID) {
            return;
        }

        // Let GrContext know that we messed with the GL context directly.
        context->resetContext();

        // Wrap the rectangle texture ID in a GrTexture
        GrGLTextureInfo rectangleInfo;
        rectangleInfo.fID = rectTexID;
        rectangleInfo.fTarget = GR_GL_TEXTURE_RECTANGLE;

        GrBackendTexture rectangleTex(kWidth, kHeight, kRGBA_8888_GrPixelConfig, rectangleInfo);

        GrColor refPixels[kWidth * kHeight];
        for (int y = 0; y < kHeight; ++y) {
            for (int x = 0; x < kWidth; ++x) {
                int y0 = useBLOrigin ? kHeight - y - 1 : y;
                refPixels[y * kWidth + x] = pixels[y0 * kWidth + x];
            }
        }

        sk_sp<GrTextureProxy> rectProxy = proxyProvider->wrapBackendTexture(rectangleTex, origin);

        if (!rectProxy) {
            ERRORF(reporter, "Error creating proxy for rectangle texture.");
            GR_GL_CALL(glContext->gl(), DeleteTextures(1, &rectTexID));
            continue;
        }

        SkASSERT(rectProxy->texPriv().doesNotSupportMipMaps());
        SkASSERT(rectProxy->priv().peekTexture()->surfacePriv().doesNotSupportMipMaps());

        SkASSERT(rectProxy->texPriv().isClampOnly());
        SkASSERT(rectProxy->priv().peekTexture()->surfacePriv().isClampOnly());

        test_basic_draw_as_src(reporter, context, rectProxy, refPixels);

        // Test copy to both a texture and RT
        test_copy_from_surface(reporter, context, rectProxy.get(), refPixels,
                               false, "RectangleTexture-copy-from");

        sk_sp<GrSurfaceContext> rectContext = context->contextPriv().makeWrappedSurfaceContext(
                                                                            std::move(rectProxy));
        SkASSERT(rectContext);

        test_read_pixels(reporter, rectContext.get(), refPixels, "RectangleTexture-read");

        test_copy_to_surface(reporter, context->contextPriv().proxyProvider(),
                              rectContext.get(), "RectangleTexture-copy-to");

        test_write_pixels(reporter, rectContext.get(), true, "RectangleTexture-write");

        test_clear(reporter, rectContext.get());

        GR_GL_CALL(glContext->gl(), DeleteTextures(1, &rectTexID));
    }
}