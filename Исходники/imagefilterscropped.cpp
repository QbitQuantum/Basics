static void draw_text(SkCanvas* canvas, const SkRect& r, sk_sp<SkImageFilter> imf) {
    SkPaint paint;
    paint.setImageFilter(std::move(imf));
    paint.setColor(SK_ColorGREEN);
    paint.setAntiAlias(true);
    sk_tool_utils::set_portable_typeface(&paint);
    paint.setTextSize(r.height()/2);
    paint.setTextAlign(SkPaint::kCenter_Align);
    canvas->drawText("Text", 4, r.centerX(), r.centerY(), paint);
}