void GraphicsContext::drawPath(const Path& path)
{
    if (paintingDisabled())
        return;

    CGContextRef context = platformContext();
    const GraphicsContextState& state = m_state;

    if (state.fillGradient || state.strokeGradient) {
        // We don't have any optimized way to fill & stroke a path using gradients
        // FIXME: Be smarter about this.
        fillPath(path);
        strokePath(path);
        return;
    }

    CGContextBeginPath(context);
    CGContextAddPath(context, path.platformPath());

    if (state.fillPattern)
        applyFillPattern();
    if (state.strokePattern)
        applyStrokePattern();

    CGPathDrawingMode drawingMode;
    if (calculateDrawingMode(state, drawingMode))
        CGContextDrawPath(context, drawingMode);
}