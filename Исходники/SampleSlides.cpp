static void textonpath_slide(SkCanvas* canvas) {
    const char* text = "Displacement";
    size_t len =strlen(text);
    SkPath path;
    path.moveTo(100, 300);
    path.quadTo(300, 100, 500, 300);
    path.offset(0, -100);

    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setTextSize(40);

    paint.setStyle(SkPaint::kStroke_Style);
    canvas->drawPath(path, paint);
    paint.setStyle(SkPaint::kFill_Style);

    SkScalar x = 50;
    paint.setColor(0xFF008800);
    canvas->drawTextOnPathHV(text, len, path,
                             x, paint.getTextSize()*2/3, paint);
    paint.setColor(SK_ColorRED);
    canvas->drawTextOnPathHV(text, len, path,
                             x + 60, 0, paint);
    paint.setColor(SK_ColorBLUE);
    canvas->drawTextOnPathHV(text, len, path,
                             x + 120, -paint.getTextSize()*2/3, paint);

    path.offset(0, 200);
    paint.setTextAlign(SkPaint::kRight_Align);

    text = "Matrices";
    len = strlen(text);
    SkScalar pathLen = getpathlen(path);
    SkMatrix matrix;

    paint.setColor(SK_ColorBLACK);
    paint.setStyle(SkPaint::kStroke_Style);
    canvas->drawPath(path, paint);
    paint.setStyle(SkPaint::kFill_Style);

    paint.setTextSize(50);
    canvas->drawTextOnPath(text, len, path, NULL, paint);

    paint.setColor(SK_ColorRED);
    matrix.setScale(-SK_Scalar1, SK_Scalar1);
    matrix.postTranslate(pathLen, 0);
    canvas->drawTextOnPath(text, len, path, &matrix, paint);

    paint.setColor(SK_ColorBLUE);
    matrix.setScale(SK_Scalar1, -SK_Scalar1);
    canvas->drawTextOnPath(text, len, path, &matrix, paint);

    paint.setColor(0xFF008800);
    matrix.setScale(-SK_Scalar1, -SK_Scalar1);
    matrix.postTranslate(pathLen, 0);
    canvas->drawTextOnPath(text, len, path, &matrix, paint);
}