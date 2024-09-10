    void onDrawContent(SkCanvas* canvas) override {
        const char* str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        SkPaint paint;
        SkScalar    x = SkIntToScalar(10);
        SkScalar    y = SkIntToScalar(20);

        paint.setFlags(0x105);

        paint.setARGB(fByte, 0xFF, 0xFF, 0xFF);

        paint.setMaskFilter(SkBlurMaskFilter::Create(kNormal_SkBlurStyle,
                                    SkBlurMask::ConvertRadiusToSigma(SkIntToScalar(3))));
        paint.getMaskFilter()->unref();

        SkRandom rand;

        for (int ps = 6; ps <= 35; ps++) {
            paint.setColor(rand.nextU() | (0xFF << 24));
            paint.setTextSize(SkIntToScalar(ps));
            paint.setTextSize(SkIntToScalar(24));
            canvas->drawText(str, strlen(str), x, y, paint);
            y += paint.getFontMetrics(nullptr);
        }
    }