SkPath make_star(const SkRect& bounds, int numPts, int step) {
    SkPath path;
    path.setFillType(SkPath::kEvenOdd_FillType);
    path.moveTo(0,-1);
    for (int i = 1; i < numPts; ++i) {
        int idx = i*step;
        SkScalar theta = idx * 2*SK_ScalarPI/numPts + SK_ScalarPI/2;
        SkScalar x = SkScalarCos(theta);
        SkScalar y = -SkScalarSin(theta);
        path.lineTo(x, y);
    }
    path.transform(SkMatrix::MakeRectToRect(path.getBounds(), bounds, SkMatrix::kFill_ScaleToFit));
    return path;
}