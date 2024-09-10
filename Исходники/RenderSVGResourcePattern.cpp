PassOwnPtr<ImageBuffer> RenderSVGResourcePattern::createTileImage(PatternData* patternData,
                                                                  const SVGPatternElement* patternElement,
                                                                  RenderObject* object) const
{
    PatternAttributes attributes = patternElement->collectPatternProperties();

    // If we couldn't determine the pattern content element root, stop here.
    if (!attributes.patternContentElement())
        return 0;

    FloatRect objectBoundingBox = object->objectBoundingBox();    
    FloatRect patternBoundaries = calculatePatternBoundaries(attributes, objectBoundingBox, patternElement); 
    AffineTransform patternTransform = attributes.patternTransform();

    AffineTransform viewBoxCTM = patternElement->viewBoxToViewTransform(patternElement->viewBox(),
                                                                        patternElement->preserveAspectRatio(),
                                                                        patternBoundaries.width(),
                                                                        patternBoundaries.height());

    FloatRect patternBoundariesIncludingOverflow = calculatePatternBoundariesIncludingOverflow(attributes,
                                                                                               objectBoundingBox,
                                                                                               viewBoxCTM,
                                                                                               patternBoundaries);

    IntSize imageSize(lroundf(patternBoundariesIncludingOverflow.width()), lroundf(patternBoundariesIncludingOverflow.height()));

    // FIXME: We should be able to clip this more, needs investigation
    clampImageBufferSizeToViewport(object->document()->view(), imageSize);

    // Don't create ImageBuffers with image size of 0
    if (imageSize.isEmpty())
        return 0;

    OwnPtr<ImageBuffer> tileImage = ImageBuffer::create(imageSize);

    GraphicsContext* context = tileImage->context();
    ASSERT(context);

    context->save();

    // Translate to pattern start origin
    if (patternBoundariesIncludingOverflow.location() != patternBoundaries.location()) {
        context->translate(patternBoundaries.x() - patternBoundariesIncludingOverflow.x(),
                           patternBoundaries.y() - patternBoundariesIncludingOverflow.y());

        patternBoundaries.setLocation(patternBoundariesIncludingOverflow.location());
    }

    // Process viewBox or boundingBoxModeContent correction
    if (!viewBoxCTM.isIdentity())
        context->concatCTM(viewBoxCTM);
    else if (attributes.boundingBoxModeContent()) {
        context->translate(objectBoundingBox.x(), objectBoundingBox.y());
        context->scale(FloatSize(objectBoundingBox.width(), objectBoundingBox.height()));
    }

    // Render subtree into ImageBuffer
    for (Node* node = attributes.patternContentElement()->firstChild(); node; node = node->nextSibling()) {
        if (!node->isSVGElement() || !static_cast<SVGElement*>(node)->isStyled() || !node->renderer())
            continue;
        renderSubtreeToImage(tileImage.get(), node->renderer());
    }

    patternData->boundaries = patternBoundaries;

    // Compute pattern transformation
    patternData->transform.translate(patternBoundaries.x(), patternBoundaries.y());
    patternData->transform.multiply(patternTransform);

    context->restore();
    return tileImage.release();
}