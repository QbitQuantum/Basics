static void drawDeferredFilter(GraphicsContext* context, FilterData* filterData, SVGFilterElement* filterElement)
{
    SkiaImageFilterBuilder builder(context);
    SourceGraphic* sourceGraphic = static_cast<SourceGraphic*>(filterData->builder->getEffectById(SourceGraphic::effectName()));
    ASSERT(sourceGraphic);
    builder.setSourceGraphic(sourceGraphic);
    RefPtr<ImageFilter> imageFilter = builder.build(filterData->builder->lastEffect(), ColorSpaceDeviceRGB);
    FloatRect boundaries = filterData->boundaries;
    context->save();

    // Clip drawing of filtered image to the minimum required paint rect.
    FilterEffect* lastEffect = filterData->builder->lastEffect();
    context->clipRect(lastEffect->determineAbsolutePaintRect(lastEffect->maxEffectRect()));
    if (filterElement->hasAttribute(SVGNames::filterResAttr)) {
        // Get boundaries in device coords.
        // FIXME: See crbug.com/382491. Is the use of getCTM OK here, given it does not include device
        // zoom or High DPI adjustments?
        FloatSize size = context->getCTM().mapSize(boundaries.size());
        // Compute the scale amount required so that the resulting offscreen is exactly filterResX by filterResY pixels.
        float filterResScaleX = filterElement->filterResX()->currentValue()->value() / size.width();
        float filterResScaleY = filterElement->filterResY()->currentValue()->value() / size.height();
        // Scale the CTM so the primitive is drawn to filterRes.
        context->scale(filterResScaleX, filterResScaleY);
        // Create a resize filter with the inverse scale.
        AffineTransform resizeMatrix;
        resizeMatrix.scale(1 / filterResScaleX, 1 / filterResScaleY);
        imageFilter = builder.buildTransform(resizeMatrix, imageFilter.get());
    }

    // See crbug.com/382491.
    if (!RuntimeEnabledFeatures::slimmingPaintEnabled()) {
        // If the CTM contains rotation or shearing, apply the filter to
        // the unsheared/unrotated matrix, and do the shearing/rotation
        // as a final pass.
        AffineTransform ctm = context->getCTM();
        if (ctm.b() || ctm.c()) {
            AffineTransform scaleAndTranslate;
            scaleAndTranslate.translate(ctm.e(), ctm.f());
            scaleAndTranslate.scale(ctm.xScale(), ctm.yScale());
            ASSERT(scaleAndTranslate.isInvertible());
            AffineTransform shearAndRotate = scaleAndTranslate.inverse();
            shearAndRotate.multiply(ctm);
            context->setCTM(scaleAndTranslate);
            imageFilter = builder.buildTransform(shearAndRotate, imageFilter.get());
        }
    }
    context->beginLayer(1, CompositeSourceOver, &boundaries, ColorFilterNone, imageFilter.get());
    context->endLayer();
    context->restore();
}