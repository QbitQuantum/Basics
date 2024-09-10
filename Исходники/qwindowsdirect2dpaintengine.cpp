    ComPtr<ID2D1Brush> to_d2d_brush(const QBrush &newBrush, bool *needsEmulation)
    {
        HRESULT hr;
        ComPtr<ID2D1Brush> result;

        Q_ASSERT(needsEmulation);

        *needsEmulation = false;

        switch (newBrush.style()) {
        case Qt::NoBrush:
            break;

        case Qt::SolidPattern:
        {
            ComPtr<ID2D1SolidColorBrush> solid;

            hr = dc()->CreateSolidColorBrush(to_d2d_color_f(newBrush.color()), &solid);
            if (FAILED(hr)) {
                qWarning("%s: Could not create solid color brush: %#x", __FUNCTION__, hr);
                break;
            }

            hr = solid.As(&result);
            if (FAILED(hr))
                qWarning("%s: Could not convert solid color brush: %#x", __FUNCTION__, hr);
        }
            break;

        case Qt::Dense1Pattern:
        case Qt::Dense2Pattern:
        case Qt::Dense3Pattern:
        case Qt::Dense4Pattern:
        case Qt::Dense5Pattern:
        case Qt::Dense6Pattern:
        case Qt::Dense7Pattern:
        case Qt::HorPattern:
        case Qt::VerPattern:
        case Qt::CrossPattern:
        case Qt::BDiagPattern:
        case Qt::FDiagPattern:
        case Qt::DiagCrossPattern:
        {
            ComPtr<ID2D1BitmapBrush1> bitmapBrush;
            D2D1_BITMAP_BRUSH_PROPERTIES1 bitmapBrushProperties = {
                D2D1_EXTEND_MODE_WRAP,
                D2D1_EXTEND_MODE_WRAP,
                interpolationMode()
            };

            QImage brushImg = qt_imageForBrush(newBrush.style(), false);
            brushImg.setColor(0, newBrush.color().rgba());
            brushImg.setColor(1, qRgba(0, 0, 0, 0));

            QWindowsDirect2DBitmap bitmap;
            bool success = bitmap.fromImage(brushImg, Qt::AutoColor);
            if (!success) {
                qWarning("%s: Could not create Direct2D bitmap from Qt pattern brush image", __FUNCTION__);
                break;
            }

            hr = dc()->CreateBitmapBrush(bitmap.bitmap(),
                                         bitmapBrushProperties,
                                         &bitmapBrush);
            if (FAILED(hr)) {
                qWarning("%s: Could not create Direct2D bitmap brush for Qt pattern brush: %#x", __FUNCTION__, hr);
                break;
            }

            hr = bitmapBrush.As(&result);
            if (FAILED(hr))
                qWarning("%s: Could not convert Direct2D bitmap brush for Qt pattern brush: %#x", __FUNCTION__, hr);
        }
            break;

        case Qt::LinearGradientPattern:
        case Qt::RadialGradientPattern:
        case Qt::ConicalGradientPattern:
            *needsEmulation = true;
            break;

        case Qt::TexturePattern:
        {
            ComPtr<ID2D1BitmapBrush1> bitmapBrush;
            D2D1_BITMAP_BRUSH_PROPERTIES1 bitmapBrushProperties = {
                D2D1_EXTEND_MODE_WRAP,
                D2D1_EXTEND_MODE_WRAP,
                interpolationMode()
            };

            QWindowsDirect2DPlatformPixmap *pp = static_cast<QWindowsDirect2DPlatformPixmap *>(newBrush.texture().handle());
            QWindowsDirect2DBitmap *bitmap = pp->bitmap();
            hr = dc()->CreateBitmapBrush(bitmap->bitmap(),
                                         bitmapBrushProperties,
                                         &bitmapBrush);

            if (FAILED(hr)) {
                qWarning("%s: Could not create texture brush: %#x", __FUNCTION__, hr);
                break;
            }

            hr = bitmapBrush.As(&result);
            if (FAILED(hr))
                qWarning("%s: Could not convert texture brush: %#x", __FUNCTION__, hr);
        }
            break;
        }

        if (result && !newBrush.transform().isIdentity())
            result->SetTransform(to_d2d_matrix_3x2_f(newBrush.transform()));

        return result;
    }