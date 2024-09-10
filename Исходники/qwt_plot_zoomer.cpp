/*!
  Expand the selected rectangle to minZoomSize() and zoom in
  if accepted.

  \sa QwtPlotZoomer::accept()a, QwtPlotZoomer::minZoomSize()
*/
bool QwtPlotZoomer::end(bool ok)
{
    ok = QwtPlotPicker::end(ok);
    if (!ok)
        return false;

    QwtPlot *plot = QwtPlotZoomer::plot();
    if ( !plot )
        return false;

    const QwtPolygon &pa = selection();
    if ( pa.count() < 2 )
        return false;

    QRect rect = QRect(pa[0], pa[int(pa.count() - 1)]);
#if QT_VERSION < 0x040000
    rect = rect.normalize();
#else
    rect = rect.normalized();
#endif


    QwtDoubleRect zoomRect = invTransform(rect).normalized();

    const QwtDoublePoint center = zoomRect.center();
    zoomRect.setSize(zoomRect.size().expandedTo(minZoomSize()));
    zoomRect.moveCenter(center);

    zoom(zoomRect);

    return true;
}