void draw(SkCanvas* canvas) {
    auto debugster = [](const char* prefix, const SkPath& path) -> void {
            const SkRect& bounds = path.getBounds();
            SkDebugf("%s bounds = %g, %g, %g, %g\n", prefix,
                     bounds.fLeft, bounds.fTop, bounds.fRight, bounds.fBottom);
    };
    SkPath path;
    debugster("empty", path);
    path.addCircle(50, 45, 25);
    debugster("circle", path);
    SkMatrix matrix;
    matrix.setRotate(45, 50, 45);
    path.transform(matrix);
    debugster("rotated circle", path);
}