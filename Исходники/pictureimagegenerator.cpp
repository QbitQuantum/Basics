static void draw_vector_logo(SkCanvas* canvas, const SkRect& viewBox) {
    constexpr char kSkiaStr[] = "SKIA";
    constexpr SkScalar kGradientPad = .1f;
    constexpr SkScalar kVerticalSpacing = 0.25f;
    constexpr SkScalar kAccentScale = 1.20f;

    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setSubpixelText(true);
    paint.setFakeBoldText(true);
    sk_tool_utils::set_portable_typeface(&paint);

    SkPath path;
    SkRect iBox, skiBox, skiaBox;
    paint.getTextPath("SKI", 3, 0, 0, &path);
    TightBounds(path, &skiBox);
    paint.getTextPath("I", 1, 0, 0, &path);
    TightBounds(path, &iBox);
    iBox.offsetTo(skiBox.fRight - iBox.width(), iBox.fTop);

    const size_t textLen = strlen(kSkiaStr);
    paint.getTextPath(kSkiaStr, textLen, 0, 0, &path);
    TightBounds(path, &skiaBox);
    skiaBox.outset(0, 2 * iBox.width() * (kVerticalSpacing + 1));

    const SkScalar accentSize = iBox.width() * kAccentScale;
    const SkScalar underlineY = iBox.bottom() +
        (kVerticalSpacing + SkScalarSqrt(3) / 2) * accentSize;
    SkMatrix m;
    m.setRectToRect(skiaBox, viewBox, SkMatrix::kFill_ScaleToFit);
    SkAutoCanvasRestore acr(canvas, true);
    canvas->concat(m);

    canvas->drawCircle(iBox.centerX(),
                       iBox.y() - (0.5f + kVerticalSpacing) * accentSize,
                       accentSize / 2,
                       paint);

    path.reset();
    path.moveTo(iBox.centerX() - accentSize / 2, iBox.bottom() + kVerticalSpacing * accentSize);
    path.rLineTo(accentSize, 0);
    path.lineTo(iBox.centerX(), underlineY);
    canvas->drawPath(path, paint);

    SkRect underlineRect = SkRect::MakeLTRB(iBox.centerX() - iBox.width() * accentSize * 3,
                                            underlineY,
                                            iBox.centerX(),
                                            underlineY + accentSize / 10);
    const SkPoint pts1[] = { SkPoint::Make(underlineRect.x(), 0),
                             SkPoint::Make(iBox.centerX(), 0) };
    const SkScalar pos1[] = { 0, 0.75f };
    const SkColor colors1[] = { SK_ColorTRANSPARENT, SK_ColorBLACK };
    SkASSERT(SK_ARRAY_COUNT(pos1) == SK_ARRAY_COUNT(colors1));
    paint.setShader(SkGradientShader::MakeLinear(pts1, colors1, pos1, SK_ARRAY_COUNT(pos1),
                                                 SkShader::kClamp_TileMode));
    canvas->drawRect(underlineRect, paint);

    const SkPoint pts2[] = { SkPoint::Make(iBox.x() - iBox.width() * kGradientPad, 0),
                             SkPoint::Make(iBox.right() + iBox.width() * kGradientPad, 0) };
    const SkScalar pos2[] = { 0, .01f, 1.0f/3, 1.0f/3, 2.0f/3, 2.0f/3, .99f, 1 };
    const SkColor colors2[] = {
        SK_ColorBLACK,
        0xffca5139,
        0xffca5139,
        0xff8dbd53,
        0xff8dbd53,
        0xff5460a5,
        0xff5460a5,
        SK_ColorBLACK
    };
    SkASSERT(SK_ARRAY_COUNT(pos2) == SK_ARRAY_COUNT(colors2));
    paint.setShader(SkGradientShader::MakeLinear(pts2, colors2, pos2, SK_ARRAY_COUNT(pos2),
                                                 SkShader::kClamp_TileMode));
    canvas->drawText(kSkiaStr, textLen, 0, 0, paint);
}