void draw(SkCanvas* canvas) {
    auto debugster = [](const char* prefix, const SkPath& path) -> void {
        SkDebugf("%s path is %s" "finite\n", prefix, path.isFinite() ? "" : "not ");
    };
    SkPath path;
    debugster("initial", path);
    path.lineTo(SK_ScalarMax, SK_ScalarMax);
    debugster("after line", path);
    SkMatrix matrix;
    matrix.setScale(2, 2);
    path.transform(matrix);
    debugster("after scale", path);
}