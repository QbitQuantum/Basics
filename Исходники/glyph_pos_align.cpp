DEF_SIMPLE_GM_BG(glyph_pos_align, canvas, kWidth, kHeight, SK_ColorBLACK) {
        SkPaint paint;
        paint.setTextSize(kTextHeight);
        paint.setFakeBoldText(true);
        const SkColor colors[] = { SK_ColorRED, SK_ColorGREEN, SK_ColorBLUE };
        const SkPoint pts[] = {{0, 0}, {kWidth, kHeight}};
        paint.setShader(SkGradientShader::MakeLinear(pts, colors, nullptr, SK_ARRAY_COUNT(colors),
                                                     SkShader::kMirror_TileMode));
        paint.setTextAlign(SkPaint::kRight_Align);
        drawTestCase(canvas, "Right Align", kTextHeight, paint);

        paint.setTextAlign(SkPaint::kCenter_Align);
        drawTestCase(canvas, "Center Align", 4 * kTextHeight, paint);

        paint.setTextAlign(SkPaint::kLeft_Align);
        drawTestCase(canvas, "Left Align", 7 * kTextHeight, paint);
}