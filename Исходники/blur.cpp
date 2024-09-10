void BlurEffect::prePaintWindow(EffectWindow* w, WindowPrePaintData& data, int time)
{
    // this effect relies on prePaintWindow being called in the bottom to top order

    effects->prePaintWindow(w, data, time);

    if (!w->isPaintingEnabled()) {
        return;
    }
    if (!shader || !shader->isValid()) {
        return;
    }

    // to blur an area partially we have to shrink the opaque area of a window
    QRegion newClip;
    const QRegion oldClip = data.clip;
    const int radius = shader->radius();
    foreach (const QRect& rect, data.clip.rects()) {
        newClip |= rect.adjusted(radius,radius,-radius,-radius);
    }
    data.clip = newClip;

    const QRegion oldPaint = data.paint;

    // we don't have to blur a region we don't see
    m_currentBlur -= newClip;
    // if we have to paint a non-opaque part of this window that intersects with the
    // currently blurred region (which is not cached) we have to redraw the whole region
    if ((data.paint-oldClip).intersects(m_currentBlur)) {
        data.paint |= m_currentBlur;
    }

    // in case this window has regions to be blurred
    const QRect screen = effects->virtualScreenGeometry();
    const QRegion blurArea = blurRegion(w).translated(w->pos()) & screen;
    const QRegion expandedBlur = expand(blurArea) & screen;

    if (m_shouldCache) {
        // we are caching the horizontally blurred background texture

        // if a window underneath the blurred area is damaged we have to
        // update the cached texture
        QRegion damagedCache;
        CacheEntry it = windows.find(w);
        if (it != windows.end() && !it->dropCache &&
            it->windowPos == w->pos() &&
            it->blurredBackground.size() == expandedBlur.boundingRect().size()) {
            damagedCache = (expand(expandedBlur & m_damagedArea) |
                            (it->damagedRegion & data.paint)) & expandedBlur;
        } else {
            damagedCache = expandedBlur;
        }
        if (!damagedCache.isEmpty()) {
            // This is the area of the blurry window which really can change.
            const QRegion damagedArea = damagedCache & blurArea;
            // In order to be able to recalculate this area we have to make sure the
            // background area is painted before.
            data.paint |= expand(damagedArea);
            if (it != windows.end()) {
                // In case we already have a texture cache mark the dirty regions invalid.
                it->damagedRegion &= expandedBlur;
                it->damagedRegion |= damagedCache;
                // The valid part of the cache can be considered as being opaque
                // as long as we don't need to update a bordering part
                data.clip |= blurArea - expand(it->damagedRegion);
                it->dropCache = false;
            }
            // we keep track of the "damage propagation"
            m_damagedArea |= damagedArea;
            // we have to check again whether we do not damage a blurred area
            // of a window we do not cache
            if (expandedBlur.intersects(m_currentBlur)) {
                data.paint |= m_currentBlur;
            }
        }
    } else {
        // we are not caching the window

        // if this window or an window underneath the blurred area is painted again we have to
        // blur everything
        if (m_paintedArea.intersects(expandedBlur) || data.paint.intersects(blurArea)) {
            data.paint |= expandedBlur;
            // we keep track of the "damage propagation"
            m_damagedArea |= expand(expandedBlur & m_damagedArea) & blurArea;
            // we have to check again whether we do not damage a blurred area
            // of a window we do not cache
            if (expandedBlur.intersects(m_currentBlur)) {
                data.paint |= m_currentBlur;
            }
        }

        m_currentBlur |= expandedBlur;
    }

    // we don't consider damaged areas which are occluded and are not
    // explicitly damaged by this window
    m_damagedArea -= data.clip;
    m_damagedArea |= oldPaint;

    // in contrast to m_damagedArea does m_paintedArea keep track of all repainted areas
    m_paintedArea -= data.clip;
    m_paintedArea |= data.paint;
}