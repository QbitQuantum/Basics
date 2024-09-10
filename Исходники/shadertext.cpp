    void onDraw(SkCanvas* canvas) override {
        const char text[] = "Shaded Text";
        const int textLen = SK_ARRAY_COUNT(text) - 1;
        const int pointSize = 36;

        const int w = pointSize * textLen;
        const int h = pointSize;

        SkPoint pts[2] = {
            { 0, 0 },
            { SkIntToScalar(w), SkIntToScalar(h) }
        };
        SkScalar textBase = SkIntToScalar(h/2);

        SkShader::TileMode tileModes[] = {
            SkShader::kClamp_TileMode,
            SkShader::kRepeat_TileMode,
            SkShader::kMirror_TileMode
        };

        static const int gradCount = SK_ARRAY_COUNT(gGradData) *
                                     SK_ARRAY_COUNT(gGradMakers);
        static const int bmpCount = SK_ARRAY_COUNT(tileModes) *
                                    SK_ARRAY_COUNT(tileModes);
        sk_sp<SkShader> shaders[gradCount + bmpCount];

        int shdIdx = 0;
        for (size_t d = 0; d < SK_ARRAY_COUNT(gGradData); ++d) {
            for (size_t m = 0; m < SK_ARRAY_COUNT(gGradMakers); ++m) {
                shaders[shdIdx++] = gGradMakers[m](pts,
                                                   gGradData[d],
                                                   SkShader::kClamp_TileMode);
            }
        }

        SkBitmap bm;
        makebm(&bm, w/16, h/4);
        for (size_t tx = 0; tx < SK_ARRAY_COUNT(tileModes); ++tx) {
            for (size_t ty = 0; ty < SK_ARRAY_COUNT(tileModes); ++ty) {
                shaders[shdIdx++] = SkShader::MakeBitmapShader(bm, tileModes[tx], tileModes[ty]);
            }
        }

        SkPaint paint;
        paint.setDither(true);
        paint.setAntiAlias(true);
        sk_tool_utils::set_portable_typeface(&paint);
        paint.setTextSize(SkIntToScalar(pointSize));

        canvas->save();
        canvas->translate(SkIntToScalar(20), SkIntToScalar(10));

        SkPath path;
        path.arcTo(SkRect::MakeXYWH(SkIntToScalar(-40), SkIntToScalar(15),
                                    SkIntToScalar(300), SkIntToScalar(90)),
                                    SkIntToScalar(225), SkIntToScalar(90),
                                    false);
        path.close();

        static const int testsPerCol = 8;
        static const int rowHeight = 60;
        static const int colWidth = 300;
        canvas->save();
        for (int s = 0; s < static_cast<int>(SK_ARRAY_COUNT(shaders)); s++) {
            canvas->save();
            int i = 2*s;
            canvas->translate(SkIntToScalar((i / testsPerCol) * colWidth),
                              SkIntToScalar((i % testsPerCol) * rowHeight));
            paint.setShader(shaders[s]);
            canvas->drawText(text, textLen, 0, textBase, paint);
            canvas->restore();
            canvas->save();
            ++i;
            canvas->translate(SkIntToScalar((i / testsPerCol) * colWidth),
                              SkIntToScalar((i % testsPerCol) * rowHeight));
            canvas->drawTextOnPath(text, textLen, path, nullptr, paint);
            canvas->restore();
        }
        canvas->restore();

    }