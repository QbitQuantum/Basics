bool RenderSVGResourceClipper::applyResource(RenderObject* object, GraphicsContext* context)
{
    ASSERT(object);
    ASSERT(context);

    m_clipper.add(object);

    context->beginPath();

    AffineTransform obbTransform;
    FloatRect objectBoundingBox = object->objectBoundingBox();
    bool bbox = static_cast<SVGClipPathElement*>(node())->clipPathUnits() == SVGUnitTypes::SVG_UNIT_TYPE_OBJECTBOUNDINGBOX;
    if (bbox) {
        obbTransform.translate(objectBoundingBox.x(), objectBoundingBox.y());
        obbTransform.scaleNonUniform(objectBoundingBox.width(), objectBoundingBox.height());
    }

    bool hasClipPath = false;
    WindRule clipRule = RULE_EVENODD;
    for (Node* childNode = node()->firstChild(); childNode; childNode = childNode->nextSibling()) {
        if (!childNode->isSVGElement() || !static_cast<SVGElement*>(childNode)->isStyledTransformable())
            continue;
        SVGStyledTransformableElement* styled = static_cast<SVGStyledTransformableElement*>(childNode);
        RenderStyle* style = styled->renderer() ? styled->renderer()->style() : 0;
        if (!style || style->display() == NONE)
            continue;
        Path pathData = styled->toClipPath();
        if (pathData.isEmpty())
            continue;
        if (bbox)
            pathData.transform(obbTransform);
        hasClipPath = true;
        context->addPath(pathData);
        clipRule = style->svgStyle()->clipRule();
    }

    if (!hasClipPath) {
        Path clipPath;
        clipPath.addRect(FloatRect());
        context->addPath(clipPath);
    }

    // FIXME!
    // We don't currently allow for heterogenous clip rules.
    // we would have to detect such, draw to a mask, and then clip
    // to that mask
    context->clipPath(clipRule);

    return true;
}