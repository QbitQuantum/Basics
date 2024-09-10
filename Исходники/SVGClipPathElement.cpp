SVGResource* SVGClipPathElement::canvasResource()
{
    if (!m_clipper)
        m_clipper = SVGResourceClipper::create();
    else
        m_clipper->resetClipData();

    bool bbox = clipPathUnits() == SVGUnitTypes::SVG_UNIT_TYPE_OBJECTBOUNDINGBOX;

    RenderStyle* clipPathStyle = styleForRenderer(parent()->renderer()); // FIXME: Manual style resolution is a hack
    for (Node* n = firstChild(); n; n = n->nextSibling()) {
        if (n->isSVGElement() && static_cast<SVGElement*>(n)->isStyledTransformable()) {
            SVGStyledTransformableElement* styled = static_cast<SVGStyledTransformableElement*>(n);
            RenderStyle* pathStyle = document()->styleSelector()->styleForElement(styled, clipPathStyle);
            if (pathStyle->display() != NONE) {
                Path pathData = styled->toClipPath();
                // FIXME: How do we know the element has done a layout?
                pathData.transform(styled->animatedLocalTransform());
                if (!pathData.isEmpty())
                    m_clipper->addClipData(pathData, pathStyle->svgStyle()->clipRule(), bbox);
            }
            pathStyle->deref(document()->renderArena());
        }
    }
    if (m_clipper->clipData().isEmpty()) {
        Path pathData;
        pathData.addRect(FloatRect());
        m_clipper->addClipData(pathData, RULE_EVENODD, bbox);
    }
    clipPathStyle->deref(document()->renderArena());
    return m_clipper.get();
}