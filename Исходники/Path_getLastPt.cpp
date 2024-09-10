void draw(SkCanvas* canvas) {
    SkPath path;
    path.moveTo(100, 100);
    path.quadTo(100, 20, 20, 100);
    SkMatrix matrix;
    matrix.setRotate(36, 100, 100);
    path.transform(matrix);
    SkPoint last;
    path.getLastPt(&last);
    SkDebugf("last point: %g, %g\n", last.fX, last.fY);
}