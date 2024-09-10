void PeakRepresentationSphere::doDraw(
    QPainter &painter, PeakViewColor &foregroundColor,
    PeakViewColor &backgroundColor,
    std::shared_ptr<PeakPrimitives> drawingInformation,
    PeakRepresentationViewInformation viewInformation) {
  auto drawingInformationSphere =
      std::static_pointer_cast<PeakPrimitiveCircle>(drawingInformation);

  // Setup the QPainter
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setOpacity(drawingInformationSphere->peakOpacityAtDistance);

  // Add a pen with color, style and stroke, and a painter path
  auto foregroundColorSphere = foregroundColor.colorSphere;
  QPainterPath peakRadiusInnerPath;
  const QPointF originWindows(viewInformation.xOriginWindow,
                              viewInformation.yOriginWindow);
  peakRadiusInnerPath.addEllipse(originWindows,
                                 drawingInformationSphere->peakInnerRadiusX,
                                 drawingInformationSphere->peakInnerRadiusY);

  QPen pen(foregroundColorSphere);
  pen.setWidth(drawingInformationSphere->peakLineWidth);
  pen.setStyle(Qt::DashLine);
  painter.strokePath(peakRadiusInnerPath, pen);

  // Draw the background if this is requested
  if (m_showBackgroundRadius) {
    QPainterPath backgroundOuterPath;
    backgroundOuterPath.setFillRule(Qt::WindingFill);
    backgroundOuterPath.addEllipse(
        originWindows, drawingInformationSphere->backgroundOuterRadiusX,
        drawingInformationSphere->backgroundOuterRadiusY);
    QPainterPath backgroundInnerPath;
    backgroundInnerPath.addEllipse(
        originWindows, drawingInformationSphere->backgroundInnerRadiusX,
        drawingInformationSphere->backgroundInnerRadiusY);
    QPainterPath backgroundRadiusFill =
        backgroundOuterPath.subtracted(backgroundInnerPath);
    painter.fillPath(backgroundRadiusFill, backgroundColor.colorSphere);
  }
  painter.end();
}