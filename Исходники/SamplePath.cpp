static void test_cubic2() {
    const char* str = "M2242 -590088L-377758 9.94099e+07L-377758 9.94099e+07L2242 -590088Z";
    SkPath path;
    SkParsePath::FromSVGString(str, &path);

    {
#ifdef SK_BUILD_FOR_WIN
        // windows doesn't have strtof
        float x = (float)strtod("9.94099e+07", NULL);
#else
        float x = strtof("9.94099e+07", NULL);
#endif
        int ix = (int)x;
        int fx = (int)(x * 65536);
        int ffx = SkScalarToFixed(x);
        printf("%g %x %x %x\n", x, ix, fx, ffx);

        SkRect r = path.getBounds();
        SkIRect ir;
        r.round(&ir);
        printf("[%g %g %g %g] [%x %x %x %x]\n",
               SkScalarToDouble(r.fLeft), SkScalarToDouble(r.fTop),
               SkScalarToDouble(r.fRight), SkScalarToDouble(r.fBottom),
               ir.fLeft, ir.fTop, ir.fRight, ir.fBottom);
    }

    SkBitmap bitmap;
    bitmap.setConfig(SkBitmap::kARGB_8888_Config, 300, 200);
    bitmap.allocPixels();

    SkCanvas canvas(bitmap);
    SkPaint paint;
    paint.setAntiAlias(true);
    canvas.drawPath(path, paint);
}