bool SkPathContainsPoint(const SkPath& originalPath, const FloatPoint& point, SkPath::FillType ft)
{
    SkRect bounds = originalPath.getBounds();

    // We can immediately return false if the point is outside the bounding
    // rect.  We don't use bounds.contains() here, since it would exclude
    // points on the right and bottom edges of the bounding rect, and we want
    // to include them.
    SkScalar fX = SkFloatToScalar(point.x());
    SkScalar fY = SkFloatToScalar(point.y());
    if (fX < bounds.fLeft || fX > bounds.fRight || fY < bounds.fTop || fY > bounds.fBottom)
        return false;

    // Scale the path to a large size before hit testing for two reasons:
    // 1) Skia has trouble with coordinates close to the max signed 16-bit values, so we scale larger paths down.
    //    TODO: when Skia is patched to work properly with large values, this will not be necessary.
    // 2) Skia does not support analytic hit testing, so we scale paths up to do raster hit testing with subpixel accuracy.
    // 3) Scale the x/y axis separately so an extreme large/small scale factor on one axis won't
    //    ruin the resolution of the other axis.
    SkScalar biggestCoordX = std::max(bounds.fRight, -bounds.fLeft);
    SkScalar biggestCoordY = std::max(bounds.fBottom, -bounds.fTop);
    if (SkScalarNearlyZero(biggestCoordX) || SkScalarNearlyZero(biggestCoordY))
        return false;

    biggestCoordX = std::max(biggestCoordX, std::fabs(fX) + 1);
    biggestCoordY = std::max(biggestCoordY, std::fabs(fY) + 1);

    const SkScalar kMaxCoordinate = SkIntToScalar(1 << 15);
    SkScalar scaleX = kMaxCoordinate / biggestCoordX;
    SkScalar scaleY = kMaxCoordinate / biggestCoordY;

    SkRegion rgn;
    SkRegion clip;
    SkMatrix m;
    SkPath scaledPath(originalPath);

    scaledPath.setFillType(ft);
    m.setScale(scaleX, scaleY);
    scaledPath.transform(m, 0);

    int x = static_cast<int>(floorf(0.5f + point.x() * scaleX));
    int y = static_cast<int>(floorf(0.5f + point.y() * scaleY));
    clip.setRect(x - 1, y - 1, x + 1, y + 1);

    return rgn.setPath(scaledPath, clip);
}