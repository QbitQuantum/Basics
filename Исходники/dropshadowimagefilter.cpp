static void draw_text(SkCanvas* canvas, const SkRect& r, SkImageFilter* imf) {
    SkPaint paint;
    paint.setImageFilter(imf);
    paint.setColor(SK_ColorGREEN);
    paint.setAntiAlias(true);
    paint.setTextSize(r.height()/2);
    paint.setTextAlign(SkPaint::kCenter_Align);
    canvas->save();
    canvas->clipRect(r);
    canvas->drawText("Text", 4, r.centerX(), r.centerY(), paint);
    canvas->restore();
}