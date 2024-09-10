void LinePlotterWindow::plotSpectrLine(HyperCube *pCube, uint x1, uint x2, uint y1, uint y2, uint z1, uint z2)
{
    m_customPlot->clearGraphs(); // только 1 график на виджете
    uint k = 1;
    int length = round (qSqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1)) / k);
    if (length == 0 || length == 1)
    {
        qDebug()<<"выберите точки, расположенные дальше друг от друга";
        throw(GenericExc("Точки должны быть расположены дальше друг от друга"));
        return;
    }
    int* cordXarr = new int[length];
    int* cordYarr = new int[length];
    int* cordZarr = new int[length];
    for (int i = 0; i<length; ++i)
    {
        cordXarr[i] = x1 + (double)((int)x2-(int)x1)/(length-1) * i;
        cordYarr[i] = y1 + (double)((int)y2-(int)y1)/(length-1) * i;
        cordZarr[i] = z1 +(double)((int)z2-(int)z1)/(length-1) * i;

    }
    QVector<double> plotXArr(length), plotYArr(length);

    quint16 Chnls = pCube->GetCountofChannels();
    for (int i = 0; i<length; ++i)
    {
        qint16* pSpectrValues = new qint16[Chnls];
        try{
             pCube->GetSpectrumPoint(cordXarr[i], cordYarr[i],pSpectrValues);
        }catch(...)
        {
            qDebug()<<"не берет GetSpectrumPoint";
        }

        plotYArr[i] = pSpectrValues[cordZarr[i]]; // эти три строчки можно заменить GetSpectrum1Point, если реализовать ее в гиперкубе
        plotXArr[i] = i;
        delete pSpectrValues;
    }
    delete cordXarr;
    delete cordYarr;
    delete cordZarr;

    QVector<double> sortedYArr;
    sortedYArr = plotYArr;
    qSort(sortedYArr);
     double minY = 70000, maxY = -10000;
    if (sortedYArr.first() < minY )
        minY = sortedYArr.first();
    if (sortedYArr.last() > maxY )
        maxY = sortedYArr.last();

    m_customPlot->setInteraction(QCP::iRangeDrag , true);
    m_customPlot->setInteraction(QCP::iRangeZoom  , true);

    m_customPlot->addGraph();
    m_customPlot->graph()->setPen(QPen(Qt::black));


    m_customPlot->graph()->setData(plotXArr,plotYArr);
    m_customPlot->xAxis->setRange(plotXArr.first(),plotXArr.last());
    m_customPlot->yAxis->setRange(minY,maxY);

    m_customPlot->legend->setVisible(true);
    m_customPlot->graph()->setName("Начало(X=" + QString::number(x1) +", Y="+ QString::number(y1) +", Z="+ QString::number(z1) + ")"
                                   +" Конец(X=" + QString::number(x2) +", Y="+ QString::number(y2) +", Z="+ QString::number(z2) + ")");
    m_customPlot->xAxis->setLabel("Интервалы разбиения прямой");
    m_customPlot->yAxis->setLabel("Яркость");
    m_customPlot->replot();
}