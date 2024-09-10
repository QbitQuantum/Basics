void RenderPath::paint(PaintInfo& paintInfo, int, int)
{
    if (paintInfo.context->paintingDisabled() || style()->visibility() == HIDDEN || m_path.isEmpty())
        return;

    FloatRect boundingBox = repaintRectInLocalCoordinates();
    FloatRect nonLocalBoundingBox = m_localTransform.mapRect(boundingBox);
    // FIXME: The empty rect check is to deal with incorrect initial clip in renderSubtreeToImage
    // unfortunately fixing that problem is fairly complex unless we were willing to just futz the
    // rect to something "close enough"
    if (!nonLocalBoundingBox.intersects(paintInfo.rect) && !paintInfo.rect.isEmpty())
        return;

    PaintInfo childPaintInfo(paintInfo);
    childPaintInfo.context->save();
    applyTransformToPaintInfo(childPaintInfo, m_localTransform);
    SVGResourceFilter* filter = 0;

    if (childPaintInfo.phase == PaintPhaseForeground) {
        PaintInfo savedInfo(childPaintInfo);

        if (prepareToRenderSVGContent(this, childPaintInfo, boundingBox, filter)) {
            if (style()->svgStyle()->shapeRendering() == SR_CRISPEDGES)
                childPaintInfo.context->setShouldAntialias(false);
            fillAndStrokePath(m_path, childPaintInfo.context, style(), this);

            if (static_cast<SVGStyledElement*>(node())->supportsMarkers())
                m_markerLayoutInfo.drawMarkers(childPaintInfo);
        }
        finishRenderSVGContent(this, childPaintInfo, filter, savedInfo.context);
    }

    if ((childPaintInfo.phase == PaintPhaseOutline || childPaintInfo.phase == PaintPhaseSelfOutline) && style()->outlineWidth())
        paintOutline(childPaintInfo.context, static_cast<int>(boundingBox.x()), static_cast<int>(boundingBox.y()),
            static_cast<int>(boundingBox.width()), static_cast<int>(boundingBox.height()), style());
    
    childPaintInfo.context->restore();
}