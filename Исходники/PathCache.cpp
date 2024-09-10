PathTexture* PathCache::getArc(float width, float height,
        float startAngle, float sweepAngle, bool useCenter, const SkPaint* paint) {
    PathDescription entry(kShapeArc, paint);
    entry.shape.arc.mWidth = width;
    entry.shape.arc.mHeight = height;
    entry.shape.arc.mStartAngle = startAngle;
    entry.shape.arc.mSweepAngle = sweepAngle;
    entry.shape.arc.mUseCenter = useCenter;

    PathTexture* texture = get(entry);

    if (!texture) {
        SkPath path;
        SkRect r;
        r.set(0.0f, 0.0f, width, height);
        if (useCenter) {
            path.moveTo(r.centerX(), r.centerY());
        }
        path.arcTo(r, startAngle, sweepAngle, !useCenter);
        if (useCenter) {
            path.close();
        }

        texture = addTexture(entry, &path, paint);
    }

    return texture;
}