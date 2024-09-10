void BasicGraph::Demo()
{
   QCustomPlot* customPlot = ui.basicGraph;

   // add two new graphs and set their look:
   customPlot->addGraph();
   customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
   customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
   customPlot->addGraph();
   customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
   // generate some points of data (y0 for first, y1 for second graph):
   QVector<double> x(250), y0(250), y1(250);
   for (int i = 0; i<250; ++i)
   {
      x[i] = i;
      y0[i] = exp(-i / 150.0)*cos(i / 10.0); // exponentially decaying cosine
      y1[i] = exp(-i / 150.0); // exponential envelope
   }
   // configure right and top axis to show ticks but no labels:
   // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
   customPlot->xAxis2->setVisible(true);
   customPlot->xAxis2->setTickLabels(false);
   customPlot->yAxis2->setVisible(true);
   customPlot->yAxis2->setTickLabels(false);
   // make left and bottom axes always transfer their ranges to right and top axes:
   connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
   connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
   // pass data points to graphs:
   customPlot->graph(0)->setData(x, y0);
   customPlot->graph(1)->setData(x, y1);
   // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
   customPlot->graph(0)->rescaleAxes();
   // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
   customPlot->graph(1)->rescaleAxes(true);
   // Note: we could have also just called customPlot->rescaleAxes(); instead
   // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
   customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

   

   ExternalReplot();
}