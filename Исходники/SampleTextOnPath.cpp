static void textPathMatrix(SkCanvas* canvas) {
    SkPaint paint;
    SkPath  path;
    SkMatrix matrix;

    path.moveTo(SkIntToScalar(050), SkIntToScalar(200));
    path.quadTo(SkIntToScalar(250), SkIntToScalar(000),
                SkIntToScalar(450), SkIntToScalar(200));

    paint.setAntiAlias(true);

    paint.setStyle(SkPaint::kStroke_Style);
    canvas->drawPath(path, paint);
    paint.setStyle(SkPaint::kFill_Style);
    paint.setTextSize(SkIntToScalar(48));
    paint.setTextAlign(SkPaint::kRight_Align);

    const char* text = "Reflection";
    size_t      len = strlen(text);

    SkPathMeasure   meas(path, false);
    SkScalar pathLen = meas.getLength();

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