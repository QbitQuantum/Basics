void RenderWidget::paintContents(PaintInfo& paintInfo, const LayoutPoint& paintOffset)
{
    LayoutPoint adjustedPaintOffset = paintOffset + location();

    Widget* widget = this->widget();
    RELEASE_ASSERT(widget);

    // Tell the widget to paint now. This is the only time the widget is allowed
    // to paint itself. That way it will composite properly with z-indexed layers.
    IntPoint widgetLocation = widget->frameRect().location();
    IntPoint paintLocation(roundToInt(adjustedPaintOffset.x() + borderLeft() + paddingLeft()),
        roundToInt(adjustedPaintOffset.y() + borderTop() + paddingTop()));
    IntRect paintRect = paintInfo.rect;

    IntSize widgetPaintOffset = paintLocation - widgetLocation;
    // When painting widgets into compositing layers, tx and ty are relative to the enclosing compositing layer,
    // not the root. In this case, shift the CTM and adjust the paintRect to be root-relative to fix plug-in drawing.
    if (!widgetPaintOffset.isZero()) {
        paintInfo.context->translate(widgetPaintOffset.width(), widgetPaintOffset.height());
        paintRect.move(-widgetPaintOffset);
    }
    widget->paint(paintInfo.context, paintRect);

    if (!widgetPaintOffset.isZero())
        paintInfo.context->translate(-widgetPaintOffset.width(), -widgetPaintOffset.height());
}