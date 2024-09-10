 void planner::graphInit(){
     line=0;
    // add two new graphs and set their look:
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue

    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(Qt::green)); // line color red for second graph

     fermatSpiral1 = new QCPCurve(ui->plot->xAxis, ui->plot->yAxis);
     ui->plot->addPlottable(fermatSpiral1);
     fermatSpiral1->setPen(QPen(Qt::red));
     fermatSpiral1->setBrush(QBrush(QColor(255, 0, 0, 20)));

     //viuslaize robot triangle instead of trajectory
     trajectoryLine = new QCPCurve(ui->plot->xAxis, ui->plot->yAxis);
     ui->plot->addPlottable(trajectoryLine);
     trajectoryLine->setPen(QPen(Qt::black));
     trajectoryLine->setBrush(QBrush(QColor(0, 0, 0, 20)));

     // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(250), y0(250), y1(250);
    for (int i=0; i<250; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
      y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    ui->plot->xAxis2->setVisible(true);
    ui->plot->xAxis2->setTickLabels(false);
    ui->plot->yAxis2->setVisible(true);
    ui->plot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->plot->graph(0)->setData(x, y0);
    ui->plot->graph(1)->setData(x, y1);
    ui->plot->graph(0)->rescaleAxes();
    ui->plot->graph(1)->rescaleAxes(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}