    virtual void onDraw(SkCanvas* canvas) {
        // explicitly add spaces, to test a prev. bug
        const char* text = "Ham bur ge fons";
        int len = SkToInt(strlen(text));
        SkPath path;

        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setTextSize(SkIntToScalar(48));

        canvas->translate(SkIntToScalar(10), SkIntToScalar(64));

        canvas->drawText(text, len, 0, 0, paint);
        paint.getTextPath(text, len, 0, 0, &path);
        strokePath(canvas, path);
        path.reset();

        SkAutoTArray<SkPoint>  pos(len);
        SkAutoTArray<SkScalar> widths(len);
        paint.getTextWidths(text, len, &widths[0]);

        SkLCGRandom rand;
        SkScalar x = SkIntToScalar(20);
        SkScalar y = SkIntToScalar(100);
        for (int i = 0; i < len; ++i) {
            pos[i].set(x, y + rand.nextSScalar1() * 24);
            x += widths[i];
        }

        canvas->translate(0, SkIntToScalar(64));

        canvas->drawPosText(text, len, &pos[0], paint);
        paint.getPosTextPath(text, len, &pos[0], &path);
        strokePath(canvas, path);
    }