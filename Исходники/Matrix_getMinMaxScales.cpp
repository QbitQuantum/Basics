void draw(SkCanvas* canvas) {
    SkMatrix matrix;
    matrix.setAll(1, 0, 0,  0, 1, 0,   0, 0, 0);
    if (matrix.invert(&matrix)) {
        SkScalar factor[2] = {2, 2};
        bool result = matrix.getMinMaxScales(factor);
        SkDebugf("matrix.getMinMaxScales() %s %g %g\n",
                result ? "true" : "false", factor[0], factor[1]);
    }
}