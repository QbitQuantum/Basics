static void setGradientAttributes(SVGGradientElement* element, LinearGradientAttributes& attributes, bool isLinear = true)
{
    if (!attributes.hasSpreadMethod() && element->spreadMethod()->isSpecified())
        attributes.setSpreadMethod(element->spreadMethod()->currentValue()->enumValue());

    if (!attributes.hasGradientUnits() && element->gradientUnits()->isSpecified())
        attributes.setGradientUnits(element->gradientUnits()->currentValue()->enumValue());

    if (!attributes.hasGradientTransform() && element->gradientTransform()->isSpecified()) {
        AffineTransform transform;
        element->gradientTransform()->currentValue()->concatenate(transform);
        attributes.setGradientTransform(transform);
    }

    if (!attributes.hasStops()) {
        const Vector<Gradient::ColorStop>& stops(element->buildStops());
        if (!stops.isEmpty())
            attributes.setStops(stops);
    }

    if (isLinear) {
        SVGLinearGradientElement* linear = toSVGLinearGradientElement(element);

        if (!attributes.hasX1() && linear->x1()->isSpecified())
            attributes.setX1(linear->x1()->currentValue());

        if (!attributes.hasY1() && linear->y1()->isSpecified())
            attributes.setY1(linear->y1()->currentValue());

        if (!attributes.hasX2() && linear->x2()->isSpecified())
            attributes.setX2(linear->x2()->currentValue());

        if (!attributes.hasY2() && linear->y2()->isSpecified())
            attributes.setY2(linear->y2()->currentValue());
    }
}