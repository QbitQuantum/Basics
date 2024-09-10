bool RenderSVGForeignObject::nodeAtFloatPoint(const HitTestRequest& request, HitTestResult& result, const FloatPoint& pointInParent, HitTestAction hitTestAction)
{
    // Embedded content is drawn in the foreground phase.
    if (hitTestAction != HitTestForeground)
        return false;

    AffineTransform localTransform = this->localTransform();
    if (!localTransform.isInvertible())
        return false;

    FloatPoint localPoint = localTransform.inverse().mapPoint(pointInParent);

    // Early exit if local point is not contained in clipped viewport area
    if (SVGRenderSupport::isOverflowHidden(this) && !m_viewport.contains(localPoint))
        return false;

    // FOs establish a stacking context, so we need to hit-test all layers.
    HitTestLocation hitTestLocation(roundedLayoutPoint(localPoint));
    return RenderBlock::nodeAtPoint(request, result, hitTestLocation, LayoutPoint(), HitTestForeground)
        || RenderBlock::nodeAtPoint(request, result, hitTestLocation, LayoutPoint(), HitTestFloat)
        || RenderBlock::nodeAtPoint(request, result, hitTestLocation, LayoutPoint(), HitTestChildBlockBackgrounds);
}