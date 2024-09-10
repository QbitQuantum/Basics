bool SVGSVGElement::checkIntersection(SVGElement* element, const FloatRect& rect)
{
    // TODO : take into account pointer-events?
    // FIXME: Why is element ignored??
    // FIXME: Implement me (see bug 11274)
    return rect.intersects(getBBox());
}