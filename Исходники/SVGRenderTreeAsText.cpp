static TextStream& operator<<(TextStream& ts, const RenderSVGShape& shape)
{
    writePositionAndStyle(ts, shape);

    ASSERT(shape.node()->isSVGElement());
    SVGElement* svgElement = toSVGElement(shape.node());
    SVGLengthContext lengthContext(svgElement);

    if (svgElement->hasTagName(SVGNames::rectTag)) {
        SVGRectElement* element = static_cast<SVGRectElement*>(svgElement);
        writeNameValuePair(ts, "x", element->x().value(lengthContext));
        writeNameValuePair(ts, "y", element->y().value(lengthContext));
        writeNameValuePair(ts, "width", element->width().value(lengthContext));
        writeNameValuePair(ts, "height", element->height().value(lengthContext));
    } else if (svgElement->hasTagName(SVGNames::lineTag)) {
        SVGLineElement* element = static_cast<SVGLineElement*>(svgElement);
        writeNameValuePair(ts, "x1", element->x1().value(lengthContext));
        writeNameValuePair(ts, "y1", element->y1().value(lengthContext));
        writeNameValuePair(ts, "x2", element->x2().value(lengthContext));
        writeNameValuePair(ts, "y2", element->y2().value(lengthContext));
    } else if (svgElement->hasTagName(SVGNames::ellipseTag)) {
        SVGEllipseElement* element = static_cast<SVGEllipseElement*>(svgElement);
        writeNameValuePair(ts, "cx", element->cx().value(lengthContext));
        writeNameValuePair(ts, "cy", element->cy().value(lengthContext));
        writeNameValuePair(ts, "rx", element->rx().value(lengthContext));
        writeNameValuePair(ts, "ry", element->ry().value(lengthContext));
    } else if (svgElement->hasTagName(SVGNames::circleTag)) {
        SVGCircleElement* element = static_cast<SVGCircleElement*>(svgElement);
        writeNameValuePair(ts, "cx", element->cx().value(lengthContext));
        writeNameValuePair(ts, "cy", element->cy().value(lengthContext));
        writeNameValuePair(ts, "r", element->r().value(lengthContext));
    } else if (svgElement->hasTagName(SVGNames::polygonTag) || svgElement->hasTagName(SVGNames::polylineTag)) {
        SVGPolyElement* element = static_cast<SVGPolyElement*>(svgElement);
        writeNameAndQuotedValue(ts, "points", element->pointList().valueAsString());
    } else if (svgElement->hasTagName(SVGNames::pathTag)) {
        SVGPathElement* element = toSVGPathElement(svgElement);
        String pathString;
        // FIXME: We should switch to UnalteredParsing here - this will affect the path dumping output of dozens of tests.
        buildStringFromByteStream(element->pathByteStream(), pathString, NormalizedParsing);
        writeNameAndQuotedValue(ts, "data", pathString);
    } else
        ASSERT_NOT_REACHED();
    return ts;
}