void PartPainter::paintContents(const PaintInfo& paintInfo,
                                const LayoutPoint& paintOffset) {
  LayoutPoint adjustedPaintOffset = paintOffset + m_layoutPart.location();

  Widget* widget = m_layoutPart.widget();
  CHECK(widget);

  IntPoint paintLocation(roundedIntPoint(
      adjustedPaintOffset + m_layoutPart.replacedContentRect().location()));

  // Widgets don't support painting with a paint offset, but instead offset
  // themselves using the frame rect location. To paint widgets at our desired
  // location, we need to apply paint offset as a transform, with the frame rect
  // neutralized.
  IntSize widgetPaintOffset = paintLocation - widget->frameRect().location();
  TransformRecorder transform(
      paintInfo.context, m_layoutPart,
      AffineTransform::translation(widgetPaintOffset.width(),
                                   widgetPaintOffset.height()));
  CullRect adjustedCullRect(paintInfo.cullRect(), -widgetPaintOffset);
  widget->paint(paintInfo.context, adjustedCullRect);
}