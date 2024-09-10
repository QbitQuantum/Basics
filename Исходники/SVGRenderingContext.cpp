void SVGRenderingContext::clipToImageBuffer(GraphicsContext& context, const AffineTransform& absoluteTransform, const FloatRect& targetRect, std::unique_ptr<ImageBuffer>& imageBuffer, bool safeToClear)
{
    if (!imageBuffer)
        return;

    FloatRect absoluteTargetRect = calculateImageBufferRect(targetRect, absoluteTransform);

    // The mask image has been created in the absolute coordinate space, as the image should not be scaled.
    // So the actual masking process has to be done in the absolute coordinate space as well.
    context.concatCTM(absoluteTransform.inverse().valueOr(AffineTransform()));
    context.clipToImageBuffer(*imageBuffer, absoluteTargetRect);
    context.concatCTM(absoluteTransform);

    // When nesting resources, with objectBoundingBox as content unit types, there's no use in caching the
    // resulting image buffer as the parent resource already caches the result.
    if (safeToClear && !currentContentTransformation().isIdentity())
        imageBuffer.reset();
}