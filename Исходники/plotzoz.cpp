PlotZoz::PlotZoz(QWidget *)
{
    // Прозрачность полотна
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setFrameStyle(QFrame::NoFrame);
    canvas->setPaintAttribute(QwtPlotCanvas::BackingStore, false);
    canvas->setPaintAttribute(QwtPlotCanvas::Opaque, false);
    canvas->setAttribute(Qt::WA_OpaquePaintEvent, false);
    canvas->setAutoFillBackground( false );
    setCanvas(canvas);
    plotLayout()->setAlignCanvasToScales(true);

    // Отключаем щкалы деления
    for (int i=0; i<QwtPlot::axisCnt; i++) {
        axisScaleDraw(i)->enableComponent(QwtScaleDraw::Ticks, false);
        axisScaleDraw(i)->enableComponent(QwtScaleDraw::Backbone, false);
    }

    pltSpectrogram = new PlotSpectr();
    pltRasterData = new PlotRasterData();

    pltGrid = new QwtPlotGrid;
    pltGrid->enableXMin(true);       // разрешаем отображение линий сетки, соответствующих вспомогательным делениям нижней шкалы
    pltGrid->enableYMin(true);       // разрешаем отображение линий сетки, соответствующих вспомогательным делениям нижней шкалы
    pltGrid->setMajorPen(QPen(Qt::gray,0,Qt::DotLine));  // черный для основных делений
    pltGrid->setMinorPen(QPen(Qt::gray,0,Qt::DotLine));  // серый для вспомогательных
    pltGrid->attach(this);

    setAxisMaxMajor(0,20);
    setAxisMaxMinor(0,0);
    setAxisMaxMajor(1,20);
    setAxisMaxMinor(1,0);
    setAxisMaxMajor(2,20);
    setAxisMaxMinor(2,0);
    setAxisMaxMajor(3,20);
    setAxisMaxMinor(3,0);

    canvas->setCursor(Qt::ArrowCursor);
    setMouseTracking(true);
    for (int i=0; i<QwtPlot::axisCnt; i++)
        axisWidget(i)->setMouseTracking(true);
}