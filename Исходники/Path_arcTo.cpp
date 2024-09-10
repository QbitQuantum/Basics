void draw(SkCanvas* canvas) {
    SkPaint paint;
    SkPath path;
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(4);
    path.moveTo(0, 0);
    path.arcTo({20, 20, 120, 120}, -90, 90, false);
    canvas->drawPath(path, paint);
    path.rewind();
    path.arcTo({120, 20, 220, 120}, -90, 90, false);
    canvas->drawPath(path, paint);
    path.rewind();
    path.moveTo(0, 0);
    path.arcTo({20, 120, 120, 220}, -90, 90, true);
    canvas->drawPath(path, paint);
}