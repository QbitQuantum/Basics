void HitRegionManager::removeHitRegionsInRect(const FloatRect& rect, const AffineTransform& ctm)
{
    Path clearArea;
    clearArea.addRect(rect);
    clearArea.transform(ctm);

    HitRegionIterator itEnd = m_hitRegionList.rend();
    HitRegionList toBeRemoved;

    for (HitRegionIterator it = m_hitRegionList.rbegin(); it != itEnd; ++it) {
        RefPtrWillBeRawPtr<HitRegion> hitRegion = *it;
        hitRegion->removePixels(clearArea);
        if (hitRegion->path().isEmpty())
            toBeRemoved.add(hitRegion);
    }

    itEnd = toBeRemoved.rend();
    for (HitRegionIterator it = toBeRemoved.rbegin(); it != itEnd; ++it)
        removeHitRegion(it->get());
}