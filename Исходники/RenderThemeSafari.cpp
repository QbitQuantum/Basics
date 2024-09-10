void RenderThemeSafari::paintMenuListButtonGradients(RenderObject* o, const PaintInfo& paintInfo, const IntRect& r)
{
    if (r.isEmpty())
        return;

    CGContextRef context = paintInfo.context->platformContext();

    paintInfo.context->save();

    RoundedRect bound = o->style()->getRoundedBorderFor(r);
    int radius = bound.radii().topLeft().width();

    CGColorSpaceRef cspace = deviceRGBColorSpaceRef();

    FloatRect topGradient(r.x(), r.y(), r.width(), r.height() / 2.0f);
    struct CGFunctionCallbacks topCallbacks = { 0, TopGradientInterpolate, NULL };
    RetainPtr<CGFunctionRef> topFunction(AdoptCF, CGFunctionCreate(NULL, 1, NULL, 4, NULL, &topCallbacks));
    RetainPtr<CGShadingRef> topShading(AdoptCF, CGShadingCreateAxial(cspace, CGPointMake(topGradient.x(), topGradient.y()), CGPointMake(topGradient.x(), topGradient.maxY()), topFunction.get(), false, false));

    FloatRect bottomGradient(r.x() + radius, r.y() + r.height() / 2.0f, r.width() - 2.0f * radius, r.height() / 2.0f);
    struct CGFunctionCallbacks bottomCallbacks = { 0, BottomGradientInterpolate, NULL };
    RetainPtr<CGFunctionRef> bottomFunction(AdoptCF, CGFunctionCreate(NULL, 1, NULL, 4, NULL, &bottomCallbacks));
    RetainPtr<CGShadingRef> bottomShading(AdoptCF, CGShadingCreateAxial(cspace, CGPointMake(bottomGradient.x(),  bottomGradient.y()), CGPointMake(bottomGradient.x(), bottomGradient.maxY()), bottomFunction.get(), false, false));

    struct CGFunctionCallbacks mainCallbacks = { 0, MainGradientInterpolate, NULL };
    RetainPtr<CGFunctionRef> mainFunction(AdoptCF, CGFunctionCreate(NULL, 1, NULL, 4, NULL, &mainCallbacks));
    RetainPtr<CGShadingRef> mainShading(AdoptCF, CGShadingCreateAxial(cspace, CGPointMake(r.x(),  r.y()), CGPointMake(r.x(), r.maxY()), mainFunction.get(), false, false));

    RetainPtr<CGShadingRef> leftShading(AdoptCF, CGShadingCreateAxial(cspace, CGPointMake(r.x(),  r.y()), CGPointMake(r.x() + radius, r.y()), mainFunction.get(), false, false));

    RetainPtr<CGShadingRef> rightShading(AdoptCF, CGShadingCreateAxial(cspace, CGPointMake(r.maxX(),  r.y()), CGPointMake(r.maxX() - radius, r.y()), mainFunction.get(), false, false));
    paintInfo.context->save();
    CGContextClipToRect(context, bound.rect());
    paintInfo.context->addRoundedRectClip(bound);
    CGContextDrawShading(context, mainShading.get());
    paintInfo.context->restore();

    paintInfo.context->save();
    CGContextClipToRect(context, topGradient);
    paintInfo.context->addRoundedRectClip(RoundedRect(enclosingIntRect(topGradient), bound.radii().topLeft(), bound.radii().topRight(), IntSize(), IntSize()));
    CGContextDrawShading(context, topShading.get());
    paintInfo.context->restore();

    if (!bottomGradient.isEmpty()) {
        paintInfo.context->save();
        CGContextClipToRect(context, bottomGradient);
        paintInfo.context->addRoundedRectClip(RoundedRect(enclosingIntRect(bottomGradient), IntSize(), IntSize(), bound.radii().bottomLeft(), bound.radii().bottomRight()));
        CGContextDrawShading(context, bottomShading.get());
        paintInfo.context->restore();
    }

    paintInfo.context->save();
    CGContextClipToRect(context, bound.rect());
    paintInfo.context->addRoundedRectClip(bound);
    CGContextDrawShading(context, leftShading.get());
    CGContextDrawShading(context, rightShading.get());
    paintInfo.context->restore();

    paintInfo.context->restore();
}