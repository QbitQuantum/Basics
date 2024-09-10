PassOwnPtr<ImageBuffer> SVGMaskElement::drawMaskerContent(const FloatRect& targetRect, FloatRect& maskDestRect) const
{    
    // Determine specified mask size
    float xValue;
    float yValue;
    float widthValue;
    float heightValue;

    if (maskUnits() == SVGUnitTypes::SVG_UNIT_TYPE_OBJECTBOUNDINGBOX) {
        xValue = x().valueAsPercentage() * targetRect.width();
        yValue = y().valueAsPercentage() * targetRect.height();
        widthValue = width().valueAsPercentage() * targetRect.width();
        heightValue = height().valueAsPercentage() * targetRect.height();
    } else {
        xValue = x().value(this);
        yValue = y().value(this);
        widthValue = width().value(this);
        heightValue = height().value(this);
    } 

    IntSize imageSize(lroundf(widthValue), lroundf(heightValue));
    clampImageBufferSizeToViewport(document()->view(), imageSize);

    if (imageSize.width() < static_cast<int>(widthValue))
        widthValue = imageSize.width();

    if (imageSize.height() < static_cast<int>(heightValue))
        heightValue = imageSize.height();

    OwnPtr<ImageBuffer> maskImage = ImageBuffer::create(imageSize, false);
    if (!maskImage)
        return 0;

    maskDestRect = FloatRect(xValue, yValue, widthValue, heightValue);
    if (maskUnits() == SVGUnitTypes::SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
        maskDestRect.move(targetRect.x(), targetRect.y());

    GraphicsContext* maskImageContext = maskImage->context();
    ASSERT(maskImageContext);

    maskImageContext->save();
    maskImageContext->translate(-xValue, -yValue);

    if (maskContentUnits() == SVGUnitTypes::SVG_UNIT_TYPE_OBJECTBOUNDINGBOX) {
        maskImageContext->save();
        maskImageContext->scale(FloatSize(targetRect.width(), targetRect.height()));
    }

    // Render subtree into ImageBuffer
    for (Node* n = firstChild(); n; n = n->nextSibling()) {
        SVGElement* elem = 0;
        if (n->isSVGElement())
            elem = static_cast<SVGElement*>(n);
        if (!elem || !elem->isStyled())
            continue;

        SVGStyledElement* e = static_cast<SVGStyledElement*>(elem);
        RenderObject* item = e->renderer();
        if (!item)
            continue;

        renderSubtreeToImage(maskImage.get(), item);
    }

    if (maskContentUnits() == SVGUnitTypes::SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
        maskImageContext->restore();

    maskImageContext->restore();
    return maskImage.release();
}