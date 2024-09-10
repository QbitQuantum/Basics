void TextureMapperLayer::paintUsingOverlapRegions(const TextureMapperPaintOptions& options)
{
    Region overlapRegion;
    Region nonOverlapRegion;
    computeOverlapRegions(overlapRegion, nonOverlapRegion, ResolveSelfOverlapAlways);
    if (overlapRegion.isEmpty()) {
        paintSelfAndChildrenWithReplica(options);
        return;
    }

    // Having both overlap and non-overlap regions carries some overhead. Avoid it if the overlap area
    // is big anyway.
    if (overlapRegion.bounds().size().area() > nonOverlapRegion.bounds().size().area()) {
        overlapRegion.unite(nonOverlapRegion);
        nonOverlapRegion = Region();
    }

    nonOverlapRegion.translate(options.offset);
    Vector<IntRect> rects = nonOverlapRegion.rects();

    for (size_t i = 0; i < rects.size(); ++i) {
        IntRect rect = rects[i];
        if (!rect.intersects(options.textureMapper->clipBounds()))
            continue;

        options.textureMapper->beginClip(TransformationMatrix(), rects[i]);
        paintSelfAndChildrenWithReplica(options);
        options.textureMapper->endClip();
    }

    rects = overlapRegion.rects();
    static const size_t OverlapRegionConsolidationThreshold = 4;
    if (nonOverlapRegion.isEmpty() && rects.size() > OverlapRegionConsolidationThreshold) {
        rects.clear();
        rects.append(overlapRegion.bounds());
    }

    IntSize maxTextureSize = options.textureMapper->maxTextureSize();
    IntRect adjustedClipBounds(options.textureMapper->clipBounds());
    adjustedClipBounds.move(-options.offset);
    for (size_t i = 0; i < rects.size(); ++i) {
        IntRect rect = rects[i];
        for (int x = rect.x(); x < rect.maxX(); x += maxTextureSize.width()) {
            for (int y = rect.y(); y < rect.maxY(); y += maxTextureSize.height()) {
                IntRect tileRect(IntPoint(x, y), maxTextureSize);
                tileRect.intersect(rect);
                if (!tileRect.intersects(adjustedClipBounds))
                    continue;

                paintWithIntermediateSurface(options, tileRect);
            }
        }
    }
}