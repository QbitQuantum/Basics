    virtual void onDrawContent(SkCanvas* canvas) {
        SkAutoCanvasRestore restore(canvas, false);
        {
            SkRect r;
            r.set(0, 0, SkIntToScalar(1000), SkIntToScalar(20));
       //     canvas->saveLayer(&r, NULL, SkCanvas::kHasAlphaLayer_SaveFlag);
        }

        SkPaint paint;
//        const uint16_t glyphs[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
        int         index = fHints % SK_ARRAY_COUNT(gHints);
        index = 1;
//        const char* style = gHints[index].fName;

//        canvas->translate(0, SkIntToScalar(50));

  //      canvas->drawText(style, strlen(style), SkIntToScalar(20), SkIntToScalar(20), paint);

        SkSafeUnref(paint.setTypeface(SkTypeface::CreateFromFile("/skimages/samplefont.ttf")));
        paint.setAntiAlias(true);
        paint.setFlags(paint.getFlags() | gHints[index].fFlags);

        SkRect clip;
        clip.set(SkIntToScalar(25), SkIntToScalar(34), SkIntToScalar(88), SkIntToScalar(155));

        const char* text = "Hamburgefons";
        size_t length = strlen(text);

        SkScalar y = SkIntToScalar(0);
        for (int i = 9; i <= 24; i++) {
            paint.setTextSize(SkIntToScalar(i) /*+ (gRand.nextU() & 0xFFFF)*/);
            for (SkScalar dx = 0; dx <= SkIntToScalar(3)/4;
                                            dx += SkIntToScalar(1) /* /4 */) {
                y += paint.getFontSpacing();
                DrawTheText(canvas, text, length, SkIntToScalar(20) + dx, y,
                            paint, fClickX, fMF);
            }
        }
        if (gHints[index].fFlushCache) {
//                SkGraphics::SetFontCacheUsed(0);
        }
    }