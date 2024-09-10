bool
gfxSurfaceDrawable::Draw(gfxContext* aContext,
                         const gfxRect& aFillRect,
                         bool aRepeat,
                         const GraphicsFilter& aFilter,
                         const gfxMatrix& aTransform)
{
    ExtendMode extend = ExtendMode::CLAMP;

    if (aRepeat) {
        extend = ExtendMode::REPEAT;
    }

    Matrix patternTransform = ToMatrix(aTransform * mTransform);
    patternTransform.Invert();

    SurfacePattern pattern(mSourceSurface, extend,
                           patternTransform, ToFilter(aFilter));

    Rect fillRect = ToRect(aFillRect);
    DrawTarget* dt = aContext->GetDrawTarget();

    if (aContext->CurrentOperator() == gfxContext::OPERATOR_CLEAR) {
        dt->ClearRect(fillRect);
    } else if (aContext->CurrentOperator() == gfxContext::OPERATOR_SOURCE) {
        // Emulate cairo operator source which is bound by mask!
        dt->ClearRect(fillRect);
        dt->FillRect(fillRect, pattern);
    } else {
        CompositionOp op = CompositionOpForOp(aContext->CurrentOperator());
        AntialiasMode aaMode =
            aContext->CurrentAntialiasMode() == gfxContext::MODE_ALIASED ?
                AntialiasMode::NONE :
                AntialiasMode::SUBPIXEL;
        dt->FillRect(fillRect, pattern, DrawOptions(1.0f, op, aaMode));
    }
    return true;
}