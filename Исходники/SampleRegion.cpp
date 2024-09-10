    void drawBG(SkCanvas* canvas)
    {
        canvas->drawColor(0xFFDDDDDD);
        return;

#if 0
        SkColorTable    ct;
        SkPMColor       colors[] = { SK_ColorRED, SK_ColorBLUE };
        ct.setColors(colors, 2);
        ct.setFlags(ct.getFlags() | SkColorTable::kColorsAreOpaque_Flag);

        SkBitmap        bm;
        bm.setConfig(SkBitmap::kIndex8_Config, 20, 20, 21);
        bm.setColorTable(&ct);
        bm.allocPixels();
        sk_memset16((uint16_t*)bm.getAddr8(0, 0), 0x0001, bm.rowBytes() * bm.height() / 2);
#endif
#if 0
        SkBitmap        bm;
        bm.setConfig(SkBitmap::kRGB_565_Config, 20, 20, 42);
        bm.allocPixels();
        sk_memset32((uint32_t*)bm.getAddr16(0, 0), 0x0000FFFF, bm.rowBytes() * bm.height() / 4);
#endif
#if 1
        SkBitmap        bm;
        bm.setConfig(SkBitmap::kARGB_8888_Config, 20, 20);
        bm.allocPixels();
        sk_memset32((uint32_t*)bm.getAddr32(0, 0), 0xFFDDDDDD, bm.rowBytes() * bm.height() / 4);
#endif

        SkPaint paint;

//        SkShader* shader = SkShader::CreateBitmapShader(bm, false, SkPaint::kBilinear_FilterType, SkShader::kRepeat_TileMode);
        SkPoint pts[] = { 0, 0, SkIntToScalar(100), SkIntToScalar(0) };
        SkColor colors[] = { SK_ColorBLACK, SK_ColorWHITE };
        SkShader* shader = SkGradientShader::CreateLinear(pts, colors, NULL, 2, SkShader::kMirror_TileMode);
        paint.setShader(shader)->unref();

        canvas->drawPaint(paint);
    }