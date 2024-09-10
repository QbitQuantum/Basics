    Direct2DRendererPrivate():
        VideoRendererPrivate()
      , d2d_factory(0)
      , render_target(0)
      , bitmap(0)
      , bitmap_width(0)
      , bitmap_height(0)
      , interpolation(D2D1_BITMAP_INTERPOLATION_MODE_LINEAR)
    {
        dll.setFileName(QStringLiteral("d2d1"));
        if (!dll.load()) {
            available = false;
            qWarning("Direct2D is disabled. Failed to load 'd2d1.dll': %s", dll.errorString().toUtf8().constData());
            return;
        }
        typedef HRESULT (WINAPI *D2D1CreateFactory_t)(D2D1_FACTORY_TYPE, REFIID, const D2D1_FACTORY_OPTIONS *, void **ppIFactory);
        D2D1CreateFactory_t D2D1CreateFactory;
        D2D1CreateFactory = (D2D1CreateFactory_t)dll.resolve("D2D1CreateFactory");
        if (!D2D1CreateFactory) {
            available = false;
            qWarning("Direct2D is disabled. Failed to resolve symble 'D2D1CreateFactory': %s", dll.errorString().toUtf8().constData());
            return;
        }

        D2D1_FACTORY_OPTIONS factory_opt = { D2D1_DEBUG_LEVEL_NONE };
        /*
         * d2d is accessed by AVThread and GUI thread, so we use D2D1_FACTORY_TYPE_MULTI_THREADED
         * and let d2d to deal with the thread safe problems. otherwise, if we use
         * D2D1_FACTORY_TYPE_SINGLE_THREADED, we must use lock when copying ID2D1Bitmap and calling EndDraw.
         */
        /// http://msdn.microsoft.com/en-us/library/windows/desktop/dd368104%28v=vs.85%29.aspx
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED
                                       , (REFIID)IID_ID2D1Factory
                                       , &factory_opt
                                       , (void**)&d2d_factory);
        if (FAILED(hr)) {
            available = false;
            qWarning("Direct2D is disabled. Create d2d factory failed");
            return;
        }
        FLOAT dpiX, dpiY;
        d2d_factory->GetDesktopDpi(&dpiX, &dpiY);
        //gcc: extended initializer lists only available with -std=c++11 or -std=gnu++11
        //vc: http://msdn.microsoft.com/zh-cn/library/t8xe60cf(v=vs.80).aspx
        /*pixel_format = {
            DXGI_FORMAT_B8G8R8A8_UNORM,
            D2D1_ALPHA_MODE_IGNORE
        };*/
        pixel_format.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        pixel_format.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;//D2D1_ALPHA_MODE_IGNORE;
        /*bitmap_properties = {
            pixel_format,
            dpiX,
            dpiY
        };*/
        bitmap_properties.pixelFormat = pixel_format;
        bitmap_properties.dpiX = dpiX;
        bitmap_properties.dpiY = dpiY;
    }