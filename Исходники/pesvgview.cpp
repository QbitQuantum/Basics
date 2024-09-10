PESvgView::PESvgView(QWidget * parent) : QFrame(parent)
{
    this->setObjectName("peSVG");

    m_pegi = NULL;
  
    QVBoxLayout * mainLayout = new QVBoxLayout;

    m_filename = new QLabel();
    mainLayout->addWidget(m_filename);

    QFrame * boundsFrame = new QFrame;
    QHBoxLayout * boundsLayout = new QHBoxLayout;

    QLabel * label = new QLabel("x:");
    boundsLayout->addWidget(label);
    m_x = new QLabel;
    boundsLayout->addWidget(m_x);
    boundsLayout->addSpacing(PEUtils::Spacing);

    label = new QLabel("y:");
    boundsLayout->addWidget(label);
    m_y = new QLabel;
    boundsLayout->addWidget(m_y);
    boundsLayout->addSpacing(PEUtils::Spacing);

    label = new QLabel(tr("width:"));
    boundsLayout->addWidget(label);
    m_width = new QLabel;
    boundsLayout->addWidget(m_width);
    boundsLayout->addSpacing(PEUtils::Spacing);

    label = new QLabel(tr("height:"));
    boundsLayout->addWidget(label);
    m_height = new QLabel;
    boundsLayout->addWidget(m_height);
    boundsLayout->addSpacing(PEUtils::Spacing);

    m_units = new QLabel();
    boundsLayout->addWidget(m_units);

    boundsLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    boundsFrame->setLayout(boundsLayout);
    mainLayout->addWidget(boundsFrame);

    m_svgElement = new QLabel;
    m_svgElement->setWordWrap(false);
    m_svgElement->setTextFormat(Qt::PlainText);
    mainLayout->addWidget(m_svgElement);

    mainLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));

	//this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setLayout(mainLayout);


}