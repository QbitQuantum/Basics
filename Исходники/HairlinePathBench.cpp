    void onDraw(const int loops, SkCanvas* canvas) override {
        SkPaint paint(fPaint);
        this->setupPaint(&paint);

        paint.setAntiAlias(fFlags & kAA_Flag ? true : false);

        SkPath path;
        this->makePath(&path);
        if (fFlags & kBig_Flag) {
            const SkMatrix m = SkMatrix::MakeScale(SkIntToScalar(3), SkIntToScalar(3));
            path.transform(m);
        }

        for (int i = 0; i < loops; i++) {
            for (int j = 0; j < 100; ++j) {
                canvas->drawPath(path, paint);
            }
        }
    }