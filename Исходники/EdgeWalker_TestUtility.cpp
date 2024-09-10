static int scaledDrawTheSame(const SkPath& one, const SkPath& two,
        int a, int b, bool drawPaths, SkBitmap& bitmap, SkCanvas* canvas) {
    SkMatrix scale;
    scale.reset();
    float aScale = 1.21f;
    float bScale = 1.11f;
    scale.preScale(a * aScale, b * bScale);
    SkPath scaledOne, scaledTwo;
    one.transform(scale, &scaledOne);
    two.transform(scale, &scaledTwo);
    int errors = pathsDrawTheSame(scaledOne, scaledTwo, bitmap, canvas);
    if (errors == 0) {
        return 0;
    }
    while (!drawAsciiPaths(scaledOne, scaledTwo, drawPaths)) {
        scale.reset();
        aScale *= 0.5f;
        bScale *= 0.5f;
        scale.preScale(a * aScale, b * bScale);
        one.transform(scale, &scaledOne);
        two.transform(scale, &scaledTwo);
    }
    return errors;
}