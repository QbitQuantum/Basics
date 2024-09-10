    virtual void onDraw(SkCanvas* canvas) {
        SkPath path;
        SkRandom rand;

        int scale = 300;
        for (int i = 0; i < 4; ++i) {
            path.lineTo(rand.nextUScalar1() * scale, rand.nextUScalar1() * scale);
            path.quadTo(rand.nextUScalar1() * scale, rand.nextUScalar1() * scale,
                        rand.nextUScalar1() * scale, rand.nextUScalar1() * scale);
            path.cubicTo(rand.nextUScalar1() * scale, rand.nextUScalar1() * scale,
                         rand.nextUScalar1() * scale, rand.nextUScalar1() * scale,
                         rand.nextUScalar1() * scale, rand.nextUScalar1() * scale);
        }

        path.setFillType(SkPath::kEvenOdd_FillType);
        path.offset(SkIntToScalar(20), SkIntToScalar(20));

        test_hittest(canvas, path);

        canvas->translate(SkIntToScalar(scale), 0);
        path.setFillType(SkPath::kWinding_FillType);

        test_hittest(canvas, path);
    }