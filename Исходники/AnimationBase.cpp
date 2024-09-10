bool AnimationBase::computeTransformedExtentViaTransformList(const FloatRect& rendererBox, const RenderStyle& style, LayoutRect& bounds) const
{
    FloatRect floatBounds = bounds;
    FloatPoint transformOrigin;
    
    bool applyTransformOrigin = containsRotation(style.transform().operations()) || style.transform().affectedByTransformOrigin();
    if (applyTransformOrigin) {
        float offsetX = style.transformOriginX().isPercent() ? rendererBox.x() : 0;
        float offsetY = style.transformOriginY().isPercent() ? rendererBox.y() : 0;

        transformOrigin.setX(floatValueForLength(style.transformOriginX(), rendererBox.width()) + offsetX);
        transformOrigin.setY(floatValueForLength(style.transformOriginY(), rendererBox.height()) + offsetY);
        // Ignore transformOriginZ because we'll bail if we encounter any 3D transforms.
        
        floatBounds.moveBy(-transformOrigin);
    }

    for (const auto& operation : style.transform().operations()) {
        if (operation->type() == TransformOperation::ROTATE) {
            // For now, just treat this as a full rotation. This could take angle into account to reduce inflation.
            floatBounds = boundsOfRotatingRect(floatBounds);
        } else {
            TransformationMatrix transform;
            operation->apply(transform, rendererBox.size());
            if (!transform.isAffine())
                return false;

            if (operation->type() == TransformOperation::MATRIX || operation->type() == TransformOperation::MATRIX_3D) {
                TransformationMatrix::Decomposed2Type toDecomp;
                transform.decompose2(toDecomp);
                // Any rotation prevents us from using a simple start/end rect union.
                if (toDecomp.angle)
                    return false;
            }

            floatBounds = transform.mapRect(floatBounds);
        }
    }

    if (applyTransformOrigin)
        floatBounds.moveBy(transformOrigin);

    bounds = LayoutRect(floatBounds);
    return true;
}