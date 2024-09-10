static void draw_sweep(SkCanvas* c, int width, int height, SkScalar angle) {
    SkRect  r;
    SkPaint p;
    
    p.setAntiAlias(true);
//    p.setDither(true);
    p.setStrokeWidth(SkIntToScalar(width/10));
    p.setStyle(SkPaint::kStroke_Style);

    r.set(0, 0, SkIntToScalar(width), SkIntToScalar(height));
    
    //    SkColor colors[] = { SK_ColorRED, SK_ColorBLUE, SK_ColorGREEN, SK_ColorCYAN };
    SkColor colors[] = { 0x4c737373, 0x4c737373, 0xffffd300 };
    SkShader* s = SkGradientShader::CreateSweep(r.centerX(), r.centerY(),
                                                colors, NULL, SK_ARRAY_COUNT(colors));
    p.setShader(s)->unref();
    
    SkAutoCanvasRestore acr(c, true);

    c->translate(r.centerX(), r.centerY());
    c->rotate(angle);
    c->translate(-r.centerX(), -r.centerY());

    SkRect bounds = r;
    r.inset(p.getStrokeWidth(), p.getStrokeWidth());
    SkRect innerBounds = r;

    if (true) {
        c->drawOval(r, p);
    } else {
        SkScalar x = r.centerX();
        SkScalar y = r.centerY();
        SkScalar radius = r.width() / 2;
        SkScalar thickness = p.getStrokeWidth();
        SkScalar sweep = SkFloatToScalar(360.0f);
        SkPath path;
        
        path.moveTo(x + radius, y);
        // outer top
        path.lineTo(x + radius + thickness, y);
        // outer arc
        path.arcTo(bounds, 0, sweep, false);
        // inner arc
        path.arcTo(innerBounds, sweep, -sweep, false);
        path.close();
    }
}