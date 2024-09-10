void draw(SkCanvas* canvas) {
    SkRRect rrect;
    SkPaint p;
    p.setStyle(SkPaint::kStroke_Style);
    p.setStrokeWidth(10);
    canvas->drawRRect(rrect, p);
    rrect.setRect({10, 10, 100, 50});
    canvas->drawRRect(rrect, p);
}