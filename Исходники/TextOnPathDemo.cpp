static void test_textpathmatrix(SkCanvas* canvas, int yOffset) {
    SkPaint paint;
    SkPath  path;
    SkMatrix matrix;

    path.moveTo(SkIntToScalar(200), SkIntToScalar(100));
    path.quadTo(SkIntToScalar(400), SkIntToScalar(-100),
                SkIntToScalar(600), SkIntToScalar(100+yOffset));

    paint.setAntiAlias(true);

    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStyle(SkPaint::kFill_Style);
    paint.setTextSize(SkIntToScalar(48));
    paint.setTextAlign(SkPaint::kRight_Align);
    paint.setAntiAlias(true);

    const char* text = "Reflection";
    size_t      len = strlen(text);
    SkScalar    pathLen = getpathlen(path);

    canvas->drawTextOnPath(text, len, path, NULL, paint);

    paint.setColor(SK_ColorRED);
    matrix.setScale(-SK_Scalar1, SK_Scalar1);
    matrix.postTranslate(pathLen, 0);
    canvas->drawTextOnPath(text, len, path, &matrix, paint);

    paint.setColor(SK_ColorBLUE);
    matrix.setScale(SK_Scalar1, -SK_Scalar1);
    canvas->drawTextOnPath(text, len, path, &matrix, paint);

    paint.setColor(SK_ColorGREEN);
    matrix.setScale(-SK_Scalar1, -SK_Scalar1);
    matrix.postTranslate(pathLen, 0);
    canvas->drawTextOnPath(text, len, path, &matrix, paint);
}