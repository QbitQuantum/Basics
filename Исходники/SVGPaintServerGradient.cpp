static inline void clipToTextMask(GraphicsContext* context,
    OwnPtr<ImageBuffer>& imageBuffer, const RenderObject* object,
    const SVGPaintServerGradient* gradientServer)
{
    FloatRect maskBBox = const_cast<RenderObject*>(findTextRootObject(object))->relativeBBox(false);

    // Fixup transformations to be able to clip to mask
    TransformationMatrix transform = object->absoluteTransform();
    FloatRect textBoundary = transform.mapRect(maskBBox);

    IntSize maskSize(lroundf(textBoundary.width()), lroundf(textBoundary.height()));
    clampImageBufferSizeToViewport(object->document()->renderer(), maskSize);
    textBoundary.setSize(textBoundary.size().shrunkTo(maskSize));

    // Clip current context to mask image (gradient)
    context->concatCTM(transform.inverse());
    context->clipToImageBuffer(textBoundary, imageBuffer.get());
    context->concatCTM(transform);

    if (gradientServer->boundingBoxMode()) {
        context->translate(maskBBox.x(), maskBBox.y());
        context->scale(FloatSize(maskBBox.width(), maskBBox.height()));
    }
    context->concatCTM(gradientServer->gradientTransform());
}