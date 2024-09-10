static void drawReplacementArrow(GraphicsContext& context, const FloatRect& insideRect)
{
    GraphicsContextStateSaver stateSaver(context);

    FloatRect rect(insideRect);
    rect.inflate(-replacementArrowPadding);

    FloatPoint center(rect.center());
    FloatPoint arrowTip(rect.maxX(), center.y());

    context.setStrokeThickness(2);
    context.setLineCap(RoundCap);
    context.setLineJoin(RoundJoin);

    Path path;
    path.moveTo(FloatPoint(rect.x(), center.y()));
    path.addLineTo(arrowTip);
    path.addLineTo(FloatPoint(center.x(), rect.y()));
    path.moveTo(arrowTip);
    path.addLineTo(FloatPoint(center.x(), rect.maxY()));
    context.strokePath(path);
}