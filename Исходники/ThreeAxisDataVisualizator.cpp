ThreeAxisDataVisualizator::ThreeAxisDataVisualizator(int duree,int dataFreq,int min, int max, int _type, QWidget *parent):
    QWidget(parent),
    duree_de_visualisation(duree),
    frequency(dataFreq),
    type(_type),
    min(0),
    max(0)
{
    curves = QList<QString>();
    QString typeStr;
    if(type==DataType::acc){
        typeStr = "accelerometre";
    }else  if(type==DataType::gyro){
        typeStr = "gyroscope";
    }else  if(type==DataType::euler){
        typeStr = "euler";
    }else  if(type==DataType::qua){
        typeStr = "quaternion";
    }

    curves.append(typeStr+" x");
    curves.append(typeStr+" y");
    curves.append(typeStr+" z");

    QHBoxLayout * mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    plot = new QwtPlot();
    mainLayout->addWidget(plot,5);

    QWidget * checkBoxGroup = new QWidget(this);
    mainLayout->addWidget(checkBoxGroup,1);

    QVBoxLayout * checkBoxGroupLayout = new QVBoxLayout;
    checkBoxGroup->setLayout(checkBoxGroupLayout);

    QPushButton * resetScaleButton = new QPushButton;
    resetScaleButton->setText("reset y scale");
    setStyleSheet("QPushButton{"
                  "font-family: Futura;"
                  "color:#4C6BCF;"
                  "font-size: 14px;"
                  "border:2px solid ;"
                  "border-color: #4C6BCF;"
                  "border-radius:5px;"
                  "min-height:60;}");

    checkBoxGroupLayout->addWidget(resetScaleButton);

    checkBoxX = new QCheckBox(curves.at(0),checkBoxGroup);
    checkBoxGroupLayout->addWidget(checkBoxX);

    checkBoxY = new QCheckBox(curves.at(1),checkBoxGroup);
    checkBoxGroupLayout->addWidget(checkBoxY);

    checkBoxZ = new QCheckBox(curves.at(2),checkBoxGroup);
    checkBoxGroupLayout->addWidget(checkBoxZ);

    timeSlider = new QSlider(Qt::Horizontal,checkBoxGroup);
    checkBoxGroupLayout->addWidget(timeSlider);

    checkBoxX->setChecked(true);
    checkBoxY->setChecked(true);
    checkBoxZ->setChecked(true);

    QSignalMapper * mapper = new QSignalMapper;
    mapper->setMapping(checkBoxX,0);
    mapper->setMapping(checkBoxY,1);
    mapper->setMapping(checkBoxZ,2);

    connect(checkBoxX,SIGNAL(stateChanged(int)),mapper,SLOT(map()));
    connect(checkBoxY,SIGNAL(stateChanged(int)),mapper,SLOT(map()));
    connect(checkBoxZ,SIGNAL(stateChanged(int)),mapper,SLOT(map()));

    connect(mapper,SIGNAL(mapped(int)),SLOT(handleCheckBox(int)));

    // canvas
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setLineWidth( 1 );
    canvas->setFrameStyle( QFrame::Box | QFrame::Plain );
    canvas->setBorderRadius( 15 );

    QPalette canvasPalette( Qt::white );
    canvasPalette.setColor( QPalette::Foreground, QColor( 133, 190, 232 ) );
    canvas->setPalette( canvasPalette );

    plot->setCanvas( canvas );

    QwtPlotScaleItem *it1 = new QwtPlotScaleItem(QwtScaleDraw::BottomScale ,0.0);
    it1->attach(plot);
    plot->enableAxis(QwtPlot::xBottom,false);
    plot->setAxisScale( QwtPlot::xBottom, 0.0, duree_de_visualisation );
    plot->setAxisScale( QwtPlot::yLeft, min, max );

    xCurve = new QwtPlotCurve( curves.at(0));
    xCurve->setRenderHint( QwtPlotItem::RenderAntialiased );
    xCurve->setLegendAttribute( QwtPlotCurve::LegendShowLine, true );
    xCurve->setPen( Qt::red );
    xCurve->attach( plot );

    yCurve = new QwtPlotCurve(curves.at(1));
    yCurve->setRenderHint( QwtPlotItem::RenderAntialiased );
    yCurve->setLegendAttribute( QwtPlotCurve::LegendShowLine, true );
    yCurve->setPen( Qt::blue );
    yCurve->attach( plot );

    zCurve = new QwtPlotCurve( curves.at(2));
    zCurve->setRenderHint( QwtPlotItem::RenderAntialiased );
    zCurve->setLegendAttribute( QwtPlotCurve::LegendShowLine, true );
    zCurve->setPen( Qt::green );
    zCurve->attach( plot );


   timerReplot = new QTimer;
   timerReplot->setInterval(50);
   connect(timerReplot,SIGNAL(timeout()),plot,SLOT(replot()));
   connect(timeSlider,SIGNAL(sliderMoved(int)),SLOT(updateVizualizatorTimeWindow(int)));

   timerRescale = new QTimer;
   timerRescale->setInterval(1000);
   connect(timerRescale,SIGNAL(timeout()),SLOT(rescale()));

   connect(resetScaleButton,SIGNAL(clicked(bool)),SLOT(resetScale()));

    setEnabled(false);
}