LineChartPicker::LineChartPicker(QwtPlot *plot) :
    QwtPlotPicker(plot->canvas()),
    p(plot)
{
  QwtPlotCanvas *canvas = plot->canvas();

  canvas->installEventFilter(this);

  canvas->setFocusPolicy(Qt::StrongFocus);
  canvas->setMouseTracking(true);
  canvas->setFocusIndicator(QwtPlotCanvas::ItemFocusIndicator);
  canvas->setFocus();
}