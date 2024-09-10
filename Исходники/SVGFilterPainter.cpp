static void paintFilteredContent(const LayoutObject& object, GraphicsContext& context, FilterData* filterData)
{
    ASSERT(filterData->m_state == FilterData::ReadyToPaint);
    ASSERT(filterData->filter->sourceGraphic());

    filterData->m_state = FilterData::PaintingFilter;

    SkiaImageFilterBuilder builder;
    RefPtr<SkImageFilter> imageFilter = builder.build(filterData->filter->lastEffect(), ColorSpaceDeviceRGB);
    FloatRect boundaries = filterData->filter->filterRegion();
    context.save();

    // Clip drawing of filtered image to the minimum required paint rect.
    FilterEffect* lastEffect = filterData->filter->lastEffect();
    context.clipRect(lastEffect->determineAbsolutePaintRect(lastEffect->maxEffectRect()));

#ifdef CHECK_CTM_FOR_TRANSFORMED_IMAGEFILTER
    // TODO: Remove this workaround once skew/rotation support is added in Skia
    // (https://code.google.com/p/skia/issues/detail?id=3288, crbug.com/446935).
    // If the CTM contains rotation or shearing, apply the filter to
    // the unsheared/unrotated matrix, and do the shearing/rotation
    // as a final pass.
    AffineTransform ctm = SVGLayoutSupport::deprecatedCalculateTransformToLayer(&object);
    if (ctm.b() || ctm.c()) {
        AffineTransform scaleAndTranslate;
        scaleAndTranslate.translate(ctm.e(), ctm.f());
        scaleAndTranslate.scale(ctm.xScale(), ctm.yScale());
        ASSERT(scaleAndTranslate.isInvertible());
        AffineTransform shearAndRotate = scaleAndTranslate.inverse();
        shearAndRotate.multiply(ctm);
        context.concatCTM(shearAndRotate.inverse());
        imageFilter = builder.buildTransform(shearAndRotate, imageFilter.get());
    }
#endif

    context.beginLayer(1, SkXfermode::kSrcOver_Mode, &boundaries, ColorFilterNone, imageFilter.get());
    context.endLayer();
    context.restore();

    filterData->m_state = FilterData::ReadyToPaint;
}