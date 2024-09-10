    virtual void onDrawContent(SkCanvas* canvas) {
        SkRect r = { 0, 0, SkIntToScalar(gWidth*2), SkIntToScalar(gHeight*2) };

        static const char* gConfigNames[] = { "8888", "565", "4444" };

        static const bool           gFilters[] = { false, true };
        static const char*          gFilterNames[] = {     "point",                     "bilinear" };

        static const SkShader::TileMode gModes[] = { SkShader::kClamp_TileMode, SkShader::kRepeat_TileMode, SkShader::kMirror_TileMode };
        static const char*          gModeNames[] = {    "C",                    "R",                   "M" };

        SkScalar y = SkIntToScalar(24);
        SkScalar x = SkIntToScalar(10);

        SkPictureRecorder recorder;
        SkCanvas* textCanvas = NULL;
        if (NULL == fTextPicture) {
            textCanvas = recorder.beginRecording(1000, 1000, NULL, 0);
        }

        if (NULL != textCanvas) {
            for (size_t kx = 0; kx < SK_ARRAY_COUNT(gModes); kx++) {
                for (size_t ky = 0; ky < SK_ARRAY_COUNT(gModes); ky++) {
                    SkPaint p;
                    SkString str;
                    p.setAntiAlias(true);
                    p.setDither(true);
                    p.setLooper(fLooper);
                    str.printf("[%s,%s]", gModeNames[kx], gModeNames[ky]);

                    p.setTextAlign(SkPaint::kCenter_Align);
                    textCanvas->drawText(str.c_str(), str.size(), x + r.width()/2, y, p);

                    x += r.width() * 4 / 3;
                }
            }
        }

        y += SkIntToScalar(16);

        for (size_t i = 0; i < SK_ARRAY_COUNT(gColorTypes); i++) {
            for (size_t j = 0; j < SK_ARRAY_COUNT(gFilters); j++) {
                x = SkIntToScalar(10);
                for (size_t kx = 0; kx < SK_ARRAY_COUNT(gModes); kx++) {
                    for (size_t ky = 0; ky < SK_ARRAY_COUNT(gModes); ky++) {
                        SkPaint paint;
                        setup(&paint, fTexture[i], gFilters[j], gModes[kx], gModes[ky]);
                        paint.setDither(true);

                        canvas->save();
                        canvas->translate(x, y);
                        canvas->drawRect(r, paint);
                        canvas->restore();

                        x += r.width() * 4 / 3;
                    }
                }
                if (NULL != textCanvas) {
                    SkPaint p;
                    SkString str;
                    p.setAntiAlias(true);
                    p.setLooper(fLooper);
                    str.printf("%s, %s", gConfigNames[i], gFilterNames[j]);
                    textCanvas->drawText(str.c_str(), str.size(), x, y + r.height() * 2 / 3, p);
                }

                y += r.height() * 4 / 3;
            }
        }

        if (NULL != textCanvas) {
            SkASSERT(NULL == fTextPicture);
            fTextPicture.reset(recorder.endRecording());
        }

        SkASSERT(NULL != fTextPicture);
        canvas->drawPicture(*fTextPicture);
    }