    void onDraw(SkCanvas* canvas) override {
        canvas->scale(SkIntToScalar(3)/2, SkIntToScalar(3)/2);

        const SkScalar w = SkIntToScalar(gWidth);
        const SkScalar h = SkIntToScalar(gHeight);
        SkRect r = { -w, -h, w*2, h*2 };

        constexpr SkShader::TileMode gModes[] = {
            SkShader::kClamp_TileMode, SkShader::kRepeat_TileMode, SkShader::kMirror_TileMode
        };
        const char* gModeNames[] = {
            "Clamp", "Repeat", "Mirror"
        };

        SkScalar y = SkIntToScalar(24);
        SkScalar x = SkIntToScalar(66);

        SkPaint p;
        p.setAntiAlias(true);
        sk_tool_utils::set_portable_typeface(&p);
        p.setTextAlign(SkPaint::kCenter_Align);

        for (size_t kx = 0; kx < SK_ARRAY_COUNT(gModes); kx++) {
            SkString str(gModeNames[kx]);
            canvas->drawText(str.c_str(), str.size(), x + r.width()/2, y, p);
            x += r.width() * 4 / 3;
        }

        y += SkIntToScalar(16) + h;
        p.setTextAlign(SkPaint::kRight_Align);

        for (size_t ky = 0; ky < SK_ARRAY_COUNT(gModes); ky++) {
            x = SkIntToScalar(16) + w;

            SkString str(gModeNames[ky]);
            canvas->drawText(str.c_str(), str.size(), x, y + h/2, p);

            x += SkIntToScalar(50);
            for (size_t kx = 0; kx < SK_ARRAY_COUNT(gModes); kx++) {
                SkPaint paint;
                paint.setShader(fProc(gModes[kx], gModes[ky]));

                canvas->save();
                canvas->translate(x, y);
                canvas->drawRect(r, paint);
                canvas->restore();

                x += r.width() * 4 / 3;
            }
            y += r.height() * 4 / 3;
        }
    }