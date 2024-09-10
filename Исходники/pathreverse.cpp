    void onDraw(SkCanvas* canvas) override {
        SkRect r = { 10, 10, 100, 60 };

        SkPath path;

        path.addRect(r); test_rev(canvas, path);

        canvas->translate(0, 100);
        path.offset(20, 20);
        path.addRect(r); test_rev(canvas, path);

        canvas->translate(0, 100);
        path.reset();
        path.moveTo(10, 10); path.lineTo(30, 30);
        path.addOval(r);
        r.offset(50, 20);
        path.addOval(r);
        test_rev(canvas, path);

        path = hiragino_maru_goth_pro_e();
        canvas->translate(0, 100);
        test_rev(canvas, path);
    }