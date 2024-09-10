    void onDraw(int loops, SkCanvas*) override {
        SkPath dst;
        for (int i = 0; i < loops; ++i) {
            SkStrokeRec rec(SkStrokeRec::kHairline_InitStyle);

            fPE->filterPath(&dst, fPath, &rec, nullptr);
            dst.rewind();
        }
    }