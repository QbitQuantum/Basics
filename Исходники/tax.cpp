Tax::Tax(double bT, double sT, double brT, QWidget *parent)
{
    setParent(parent);

    lSell	= new QLabel (tr("sell tax"), this);
    lBuy	= new QLabel (tr("buy tax"), this);
    lBroker	= new QLabel (tr("broker fee"), this);

    sbSell	= new QDoubleSpinBox (this);
    sbBuy	= new QDoubleSpinBox (this);
    sbBroker= new QDoubleSpinBox (this);

    sbSell->setSuffix("%");
    sbSell->setValue(sT);
    sbBuy->setSuffix("%");
    sbBuy->setValue(bT);
    sbBroker->setSuffix("%");
    sbBroker->setValue(brT);;

    layout   = new QVBoxLayout(this);

    layout->addWidget(lBuy);
    layout->addWidget(sbBuy);

    layout->addWidget(lSell);
    layout->addWidget(sbSell);

    layout->addWidget(lBroker);
    layout->addWidget(sbBroker);

    adjustSize();

    connect(sbSell,	  SIGNAL(valueChanged(double)),	this, SLOT(onSellChange(double)));
    connect(sbBuy,	  SIGNAL(valueChanged(double)), this, SLOT(onBuyChange(double)));
    connect(sbBroker, SIGNAL(valueChanged(double)), this, SLOT(onBrokerChange(double)));
}