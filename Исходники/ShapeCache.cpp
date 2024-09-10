PathTexture* ArcShapeCache::getArc(float width, float height,
        float startAngle, float sweepAngle, bool useCenter, SkPaint* paint) {
    ArcShapeCacheEntry entry(width, height, startAngle, sweepAngle, useCenter, paint);
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