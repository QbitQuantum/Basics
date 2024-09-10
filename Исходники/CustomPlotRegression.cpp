void CustomPlotRegression::setupQuadraticDemo(double * kernely,
                                              int size_kernely,
                                              double * kernelx,
                                              int size_kernelx  )
{
    QCustomPlot* customPlot=m_CustomPlot;
    // make top right axes clones of bottom left axes:

    // generate some data:
    QVector<double> x1( 0 ), y1( 0 );   // initialize with entries 0..100
    customPlot->addGraph();
    customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    //customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    //    customPlot->graph( 0 )->setData( x1, y1 );
    QVector<double> x;
    QVector<double> y;
    //std::cout << "****************************************************************+++" <<endl;
    double maxx= DBL_MIN;
    double maxy= DBL_MIN;
    for (int i = 0; i < size_kernelx; i++) {
        //        std::cout << kernel[i] << endl;
        x.push_back(kernelx[i]);
        y.push_back(kernely[i]);
        if(kernelx[i] > maxx){
            maxx=kernelx[i];
        }
        if(kernely[i] > maxy){
            maxy=kernely[i];
        }
    }
    m_CustomPlot->graph( 0 )->setData( x, y);
    //    std::cout << "ok" << endl;
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));

    customPlot->addGraph();
    customPlot->graph( 1 )->setPen( QPen( Qt::green ) );
    //customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    //    customPlot->graph( 1 )->setData( x1, y1 );
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));

    // give the axes some labels:
    customPlot->xAxis->setLabel( "Generation" );
    customPlot->yAxis->setLabel( "Fitness" );
    // set axes ranges, so we see all data:

    customPlot->xAxis->setRange( 0, maxx );
    customPlot->yAxis->setRange( 0, maxy);

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
    for (int i = 0; i < number_of_function; ++i) {
            customPlot->addGraph();
    }


}