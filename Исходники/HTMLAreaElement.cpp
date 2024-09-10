Path HTMLAreaElement::computePath(RenderElement* obj) const
{
    if (!obj)
        return Path();
    
    // FIXME: This doesn't work correctly with transforms.
    FloatPoint absPos = obj->localToAbsolute();

    // Default should default to the size of the containing object.
    LayoutSize size = m_lastSize;
    if (m_shape == Default)
        size = obj->absoluteOutlineBounds().size();
    
    Path p = getRegion(size);
    float zoomFactor = obj->style().effectiveZoom();
    if (zoomFactor != 1.0f) {
        AffineTransform zoomTransform;
        zoomTransform.scale(zoomFactor);
        p.transform(zoomTransform);
    }

    p.translate(toFloatSize(absPos));
    return p;
}