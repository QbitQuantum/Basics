Path RenderSVGTextPath::layoutPath() const
{
    SVGTextPathElement* textPathElement = static_cast<SVGTextPathElement*>(element());
        String pathId = SVGURIReference::getTarget(textPathElement->href());
    Element* targetElement = textPathElement->document()->getElementById(pathId);    
    if (!targetElement || !targetElement->hasTagName(SVGNames::pathTag))
        return Path();
    
    SVGPathElement* pathElement = static_cast<SVGPathElement*>(targetElement);
    
    Path pathData = pathElement->toPathData();
    // Spec:  The transform attribute on the referenced 'path' element represents a
    // supplemental transformation relative to the current user coordinate system for
    // the current 'text' element, including any adjustments to the current user coordinate
    // system due to a possible transform attribute on the current 'text' element.
    // http://www.w3.org/TR/SVG/text.html#TextPathElement
    pathData.transform(pathElement->animatedLocalTransform());
    return pathData;
}