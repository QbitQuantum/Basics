void ContentLayerChromium::calculateClippedUpdateRect(IntRect& dirtyRect, IntRect& drawRect) const
{
    // For the given layer size and content rect, calculate:
    // 1) The minimal texture space rectangle to be uploaded, returned in dirtyRect.
    // 2) The rectangle to draw this texture in relative to the target render surface, returned in drawRect.

    ASSERT(m_targetRenderSurface);
    const IntRect clipRect = m_targetRenderSurface->contentRect();

    TransformationMatrix layerOriginTransform = drawTransform();
    layerOriginTransform.translate3d(-0.5 * m_bounds.width(), -0.5 * m_bounds.height(), 0);

    // For now we apply the large layer treatment only for layers that are either untransformed
    // or are purely translated. Their matrix is expected to be invertible.
    ASSERT(layerOriginTransform.isInvertible());

    TransformationMatrix targetToLayerMatrix = layerOriginTransform.inverse();
    IntRect clipRectInLayerCoords = targetToLayerMatrix.mapRect(clipRect);
    clipRectInLayerCoords.intersect(IntRect(0, 0, m_bounds.width(), m_bounds.height()));

    dirtyRect = clipRectInLayerCoords;

    // Map back to the target surface coordinate system.
    drawRect = layerOriginTransform.mapRect(dirtyRect);
}