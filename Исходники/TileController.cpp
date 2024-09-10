void TileController::adjustTileCoverageRect(FloatRect& coverageRect, const FloatSize& newSize, const FloatRect& previousVisibleRect, const FloatRect& visibleRect, float contentsScale) const
{
    // If the page is not in a window (for example if it's in a background tab), we limit the tile coverage rect to the visible rect.
    if (!m_isInWindow) {
        coverageRect = visibleRect;
        return;
    }

#if PLATFORM(IOS)
    // FIXME: unify the iOS and Mac code.
    UNUSED_PARAM(previousVisibleRect);
    
    if (m_tileCoverage == CoverageForVisibleArea || MemoryPressureHandler::singleton().isUnderMemoryPressure()) {
        coverageRect = visibleRect;
        return;
    }

    double horizontalMargin = kDefaultTileSize / contentsScale;
    double verticalMargin = kDefaultTileSize / contentsScale;

    double currentTime = monotonicallyIncreasingTime();
    double timeDelta = currentTime - m_velocity.lastUpdateTime;

    FloatRect futureRect = visibleRect;
    futureRect.setLocation(FloatPoint(
        futureRect.location().x() + timeDelta * m_velocity.horizontalVelocity,
        futureRect.location().y() + timeDelta * m_velocity.verticalVelocity));

    if (m_velocity.horizontalVelocity) {
        futureRect.setWidth(futureRect.width() + horizontalMargin);
        if (m_velocity.horizontalVelocity < 0)
            futureRect.setX(futureRect.x() - horizontalMargin);
    }

    if (m_velocity.verticalVelocity) {
        futureRect.setHeight(futureRect.height() + verticalMargin);
        if (m_velocity.verticalVelocity < 0)
            futureRect.setY(futureRect.y() - verticalMargin);
    }

    if (!m_velocity.horizontalVelocity && !m_velocity.verticalVelocity) {
        if (m_velocity.scaleChangeRate > 0) {
            coverageRect = visibleRect;
            return;
        }
        futureRect.setWidth(futureRect.width() + horizontalMargin);
        futureRect.setHeight(futureRect.height() + verticalMargin);
        futureRect.setX(futureRect.x() - horizontalMargin / 2);
        futureRect.setY(futureRect.y() - verticalMargin / 2);
    }

    // Can't use m_tileCacheLayer->bounds() here, because the size of the underlying platform layer
    // hasn't been updated for the current commit.
    IntSize contentSize = expandedIntSize(newSize);
    if (futureRect.maxX() > contentSize.width())
        futureRect.setX(contentSize.width() - futureRect.width());
    if (futureRect.maxY() > contentSize.height())
        futureRect.setY(contentSize.height() - futureRect.height());
    if (futureRect.x() < 0)
        futureRect.setX(0);
    if (futureRect.y() < 0)
        futureRect.setY(0);

    coverageRect.unite(futureRect);
    return;
#else
    UNUSED_PARAM(contentsScale);

    // FIXME: look at how far the document can scroll in each dimension.
    FloatSize coverageSize = visibleRect.size();

    bool largeVisibleRectChange = !previousVisibleRect.isEmpty() && !visibleRect.intersects(previousVisibleRect);

    // Inflate the coverage rect so that it covers 2x of the visible width and 3x of the visible height.
    // These values were chosen because it's more common to have tall pages and to scroll vertically,
    // so we keep more tiles above and below the current area.
    float widthScale = 1;
    float heightScale = 1;

    if (m_tileCoverage & CoverageForHorizontalScrolling && !largeVisibleRectChange)
        widthScale = 2;

    if (m_tileCoverage & CoverageForVerticalScrolling && !largeVisibleRectChange)
        heightScale = 3;
    
    coverageSize.scale(widthScale, heightScale);

    FloatRect coverageBounds = boundsForSize(newSize);
    
    FloatRect coverage = expandRectWithinRect(visibleRect, coverageSize, coverageBounds);
    LOG_WITH_STREAM(Scrolling, stream << "TileController::computeTileCoverageRect newSize=" << newSize << " mode " << m_tileCoverage << " expanded to " << coverageSize << " bounds with margin " << coverageBounds << " coverage " << coverage);
    coverageRect.unite(coverage);
#endif
}