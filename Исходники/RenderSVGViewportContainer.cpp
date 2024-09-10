bool RenderSVGViewportContainer::nodeAtPoint(const HitTestRequest& request, HitTestResult& result, int _x, int _y, int _tx, int _ty, HitTestAction hitTestAction)
{
    if (!viewport().isEmpty()
            && style()->overflowX() == OHIDDEN
            && style()->overflowY() == OHIDDEN) {
        // Check if we need to do anything at all.
        IntRect overflowBox = IntRect(0, 0, width(), height());
        overflowBox.move(_tx, _ty);
        TransformationMatrix ctm = RenderObject::absoluteTransform();
        ctm.translate(viewport().x(), viewport().y());
        double localX, localY;
        ctm.inverse().map(_x - _tx, _y - _ty, &localX, &localY);
        if (!overflowBox.contains((int)localX, (int)localY))
            return false;
    }

    int sx = 0;
    int sy = 0;

    // Respect parent translation offset for non-outermost <svg> elements.
    // Outermost <svg> element is handled by RenderSVGRoot.
    if (element()->hasTagName(SVGNames::svgTag)) {
        sx = _tx;
        sy = _ty;
    }

    for (RenderObject* child = lastChild(); child; child = child->previousSibling()) {
        if (child->nodeAtPoint(request, result, _x - sx, _y - sy, _tx, _ty, hitTestAction)) {
            updateHitTestResult(result, IntPoint(_x - _tx, _y - _ty));
            return true;
        }
    }

    // Spec: Only graphical elements can be targeted by the mouse, period.
    // 16.4: "If there are no graphics elements whose relevant graphics content is under the pointer (i.e., there is no target element), the event is not dispatched."
    return false;
}