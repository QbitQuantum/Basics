std::unique_ptr<PathPositionMapper> LayoutSVGTextPath::layoutPath() const
{
    const SVGTextPathElement& textPathElement = toSVGTextPathElement(*node());
    Element* targetElement = SVGURIReference::targetElementFromIRIString(
        textPathElement.hrefString(), treeScopeForIdResolution(textPathElement));

    if (!isSVGPathElement(targetElement))
        return nullptr;

    SVGPathElement& pathElement = toSVGPathElement(*targetElement);
    Path pathData = pathElement.asPath();
    if (pathData.isEmpty())
        return nullptr;

    // Spec:  The transform attribute on the referenced 'path' element represents a
    // supplemental transformation relative to the current user coordinate system for
    // the current 'text' element, including any adjustments to the current user coordinate
    // system due to a possible transform attribute on the current 'text' element.
    // http://www.w3.org/TR/SVG/text.html#TextPathElement
    pathData.transform(pathElement.calculateAnimatedLocalTransform());

    return PathPositionMapper::create(pathData);
}