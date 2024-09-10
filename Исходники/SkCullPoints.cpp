bool SkHitTestPath(const SkPath& path, SkRect& target, bool hires) {
    if (target.isEmpty()) {
        return false;
    }

    bool isInverse = path.isInverseFillType();
    if (path.isEmpty()) {
        return isInverse;
    }

    SkRect bounds = path.getBounds();

    bool sects = SkRect::Intersects(target, bounds);
    if (isInverse) {
        if (!sects) {
            return true;
        }
    } else {
        if (!sects) {
            return false;
        }
        if (target.contains(bounds)) {
            return true;
        }
    }

    SkPath devPath;
    const SkPath* pathPtr;
    SkRect        devTarget;

    if (hires) {
        const SkScalar coordLimit = SkIntToScalar(16384);
        const SkRect limit = { 0, 0, coordLimit, coordLimit };
        
        SkMatrix matrix;
        matrix.setRectToRect(bounds, limit, SkMatrix::kFill_ScaleToFit);

        path.transform(matrix, &devPath);
        matrix.mapRect(&devTarget, target);

        pathPtr = &devPath;
    } else {
        devTarget = target;
        pathPtr = &path;
    }

    SkIRect iTarget;
    devTarget.round(&iTarget);
    if (iTarget.isEmpty()) {
        iTarget.fLeft = SkScalarFloorToInt(devTarget.fLeft);
        iTarget.fTop = SkScalarFloorToInt(devTarget.fTop);
        iTarget.fRight = iTarget.fLeft + 1;
        iTarget.fBottom = iTarget.fTop + 1;
    }

    SkRegion clip(iTarget);
    SkRegion rgn;
    return rgn.setPath(*pathPtr, clip) ^ isInverse;
}