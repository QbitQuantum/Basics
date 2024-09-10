    virtual void onDraw(SkCanvas* canvas) {
        SkPaint paint;
        this->setupPaint(&paint);

        for (int i = 0; i < N; ++i) {
            SkAAClip clip;
            if (fDoPath) {
                clip.setPath(fPath, &fRegion, fDoAA);
            } else {
                clip.setRect(fRect, fDoAA);
            }
        }
    }