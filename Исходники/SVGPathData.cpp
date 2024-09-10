static void updatePathFromLineElement(SVGElement* element, Path& path)
{
    ASSERT_WITH_SECURITY_IMPLICATION(element->hasTagName(SVGNames::lineTag));
    SVGLineElement* line = static_cast<SVGLineElement*>(element);

    SVGLengthContext lengthContext(element);
    path.moveTo(FloatPoint(line->x1().value(lengthContext), line->y1().value(lengthContext)));
    path.addLineTo(FloatPoint(line->x2().value(lengthContext), line->y2().value(lengthContext)));
}