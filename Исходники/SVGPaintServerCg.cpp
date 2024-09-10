void SVGPaintServer::renderPath(GraphicsContext*& context, const RenderPath* path, SVGPaintTargetType type) const
{
    RenderStyle* style = path->style();
    CGContextRef contextRef = context->platformContext();

    if ((type & ApplyToFillTargetType) && style->svgStyle()->hasFill())
        fillPath(contextRef, path);

    if ((type & ApplyToStrokeTargetType) && style->svgStyle()->hasStroke())
        strokePath(contextRef, path);
}