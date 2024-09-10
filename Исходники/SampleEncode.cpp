    virtual void onDrawContent(SkCanvas* canvas) {
        if (fBitmapCount == 0) {
            return;
        }

        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setTextAlign(SkPaint::kCenter_Align);

        canvas->translate(SkIntToScalar(10), SkIntToScalar(20));

        SkScalar x = 0, y = 0, maxX = 0;
        const int SPACER = 10;

        for (int i = 0; i < fBitmapCount; i++) {
            canvas->drawText(gConfigLabels[i], strlen(gConfigLabels[i]),
                             x + SkIntToScalar(fBitmaps[i].width()) / 2, 0,
                             paint);
            y = paint.getTextSize();

            canvas->drawBitmap(fBitmaps[i], x, y);

            SkScalar yy = y;
            for (size_t j = 0; j < SK_ARRAY_COUNT(gTypes); j++) {
                yy += SkIntToScalar(fBitmaps[i].height() + 10);

                SkBitmap bm;
                SkData* encoded = NULL;
                if (SkImageEncoder::kJPEG_Type == gTypes[j]) {
                    encoded = fEncodedJPEGs[i].get();
                } else if (SkImageEncoder::kPNG_Type == gTypes[j]) {
                    encoded = fEncodedPNGs[i].get();
                }
                if (encoded) {
                    if (!SkInstallDiscardablePixelRef(
                            SkDecodingImageGenerator::Create(encoded,
                                SkDecodingImageGenerator::Options()),
                            &bm, NULL)) {
                    SkDebugf("[%s:%d] failed to decode %s%s\n",
                             __FILE__, __LINE__,gConfigLabels[i], gExt[j]);
                    }
                    canvas->drawBitmap(bm, x, yy);
                }
            }

            x += SkIntToScalar(fBitmaps[i].width() + SPACER);
            if (x > maxX) {
                maxX = x;
            }
        }

        y = (paint.getTextSize() + SkIntToScalar(fBitmaps[0].height())) * 3 / 2;
        x = maxX + SkIntToScalar(10);
        paint.setTextAlign(SkPaint::kLeft_Align);

        for (size_t j = 0; j < SK_ARRAY_COUNT(gExt); j++) {
            canvas->drawText(gExt[j], strlen(gExt[j]), x, y, paint);
            y += SkIntToScalar(fBitmaps[0].height() + SPACER);
        }
    }