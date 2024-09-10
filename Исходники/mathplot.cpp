void MathPlot::setupTextureBrushDemo(QCustomPlot *customPlot)
{
  // add two graphs with a textured fill:
  customPlot->addGraph();
  QPen redDotPen;
  redDotPen.setStyle(Qt::DotLine);
  redDotPen.setColor(QColor(170, 100, 100, 180));
  redDotPen.setWidthF(2);
  customPlot->graph(0)->setPen(redDotPen);
  customPlot->graph(0)->setBrush(QBrush(QPixmap("://skin/images/balboa.jpg"))); // fill with texture of specified image

  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red));

  // activate channel fill for graph 0 towards graph 1:
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

  // generate data:
  QVector<double> x(250);
  QVector<double> y0(250), y1(250);
  for (int i=0; i<250; ++i)
  {
    // just playing with numbers, not much to learn here
    x[i] = 3*i/250.0;
    y0[i] = 1+exp(-x[i]*x[i]*0.8)*(x[i]*x[i]+x[i]);
    y1[i] = 1-exp(-x[i]*x[i]*0.4)*(x[i]*x[i])*0.1;
  }

  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  // activate top and right axes, which are invisible by default:
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  // make tick labels invisible on top and right axis:
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  // set ranges:
  customPlot->xAxis->setRange(0, 2.5);
  customPlot->yAxis->setRange(0.9, 1.6);
  // assign top/right axes same properties as bottom/left:
  customPlot->axisRect()->setupFullAxesBox();
}