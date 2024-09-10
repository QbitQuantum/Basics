void TextureMapperImageBuffer::drawSolidColor(const FloatRect& rect, const TransformationMatrix& matrix, const Color& color)
{

    GraphicsContext* context = currentContext();
    if (!context)
        return;

    context->save();
    context->setCompositeOperation(isInMaskMode() ? CompositeDestinationIn : CompositeSourceOver);
#if ENABLE(3D_RENDERING)
    context->concat3DTransform(matrix);
#else
    context->concatCTM(matrix.toAffineTransform());
#endif

    context->fillRect(rect, color, ColorSpaceDeviceRGB);
    context->restore();
}