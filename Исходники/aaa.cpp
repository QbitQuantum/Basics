    void onDraw(SkCanvas* canvas) override {
        SkPaint p;
        p.setColor(SK_ColorRED);
        p.setAntiAlias(true);

        canvas->clear(0xFFFFFFFF);

        canvas->save();
        canvas->rotate(1);
        const SkScalar R = 115.2f, C = 128.0f;
        SkPath path;
        path.moveTo(C + R, C);
        for (int i = 1; i < 8; ++i) {
            SkScalar a = 2.6927937f * i;
            SkScalar cosine;
            SkScalar sine = SkScalarSinCos(a, &cosine);
            path.lineTo(C + R * cosine, C + R * sine);
        }
        canvas->drawPath(path, p);
        canvas->restore();

        canvas->save();
        canvas->translate(200, 0);
        canvas->rotate(1);
        p.setStyle(SkPaint::kStroke_Style);
        p.setStrokeWidth(5);
        canvas->drawPath(path, p);
        canvas->restore();


        // The following two paths test if we correctly cumulates the alpha on the middle pixel
        // column where the left rect and the right rect abut.
        p.setStyle(SkPaint::kFill_Style);
        canvas->translate(0, 300);
        path.reset();
        path.addRect({20, 20, 100.4999f, 100});
        path.addRect({100.5001f, 20, 200, 100});
        canvas->drawPath(path, p);

        canvas->translate(300, 0);
        path.reset();
        path.addRect({20, 20, 100.1f, 100});
        path.addRect({100.9f, 20, 200, 100});
        canvas->drawPath(path, p);
    }