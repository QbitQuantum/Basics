bool RenderSVGText::nodeAtPoint(const HitTestRequest& request, HitTestResult& result, int _x, int _y, int _tx, int _ty, HitTestAction hitTestAction)
{
    PointerEventsHitRules hitRules(PointerEventsHitRules::SVG_TEXT_HITTESTING, style()->svgStyle()->pointerEvents());
    bool isVisible = (style()->visibility() == VISIBLE);
    if (isVisible || !hitRules.requireVisible) {
        if ((hitRules.canHitStroke && (style()->svgStyle()->hasStroke() || !hitRules.requireStroke))
            || (hitRules.canHitFill && (style()->svgStyle()->hasFill() || !hitRules.requireFill))) {
            AffineTransform totalTransform = absoluteTransform();
            double localX, localY;
            totalTransform.inverse().map(_x, _y, &localX, &localY);
            FloatPoint hitPoint(_x, _y);
            return RenderBlock::nodeAtPoint(request, result, (int)localX, (int)localY, _tx, _ty, hitTestAction);
        }
    }
    return false;
}