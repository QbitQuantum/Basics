KugouWindow::KugouWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    const QString radioStyle = "QPushButton{ border:none; color:rgb(135, 135, 135);} \
                                QPushButton:hover{ color:rgb(104, 169, 236);} \
                                QPushButton:checked{ color:rgb(40, 143, 231);} \
                                QWidget{background: white;}";
    QWidget *top = new QWidget(this);
    top->setFixedHeight(25);
    top->setStyleSheet( radioStyle );
    QHBoxLayout *topLayout = new QHBoxLayout(top);
    topLayout->setContentsMargins(0, 0, 0, 0);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    QPushButton *bt = new QPushButton(tr(" Recommend "), top);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    buttonGroup->addButton(bt, 0);
    bt = new QPushButton(tr(" Radio "), top);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    buttonGroup->addButton(bt, 1);
    bt = new QPushButton(tr(" Rank "), top);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    buttonGroup->addButton(bt, 2);
    bt = new QPushButton(tr(" Singer "), top);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    buttonGroup->addButton(bt, 3);
    bt = new QPushButton(tr(" Category "), top);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    buttonGroup->addButton(bt, 4);
    bt = new QPushButton(tr(" Show "), top);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    buttonGroup->addButton(bt, 5);
    bt = new QPushButton(tr(" CCTV "), top);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    buttonGroup->addButton(bt, 6);
    connect(buttonGroup, SIGNAL(buttonClicked(int)), SLOT(differButtonIndexChanged(int)));

    topLayout->addStretch(1);
    topLayout->addWidget(buttonGroup->button(0));
    topLayout->addWidget(buttonGroup->button(1));
    topLayout->addWidget(buttonGroup->button(2));
    topLayout->addWidget(buttonGroup->button(3));
    topLayout->addWidget(buttonGroup->button(4));
    topLayout->addWidget(buttonGroup->button(5));
    topLayout->addWidget(buttonGroup->button(6));
    topLayout->addStretch(1);

    m_webView = new QWebView(this);
    m_webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    m_webView->setUrl(QUrl( KugouUrl::getRecommendUrl() ));

    layout->addWidget(top);
    layout->addWidget(m_webView);
    setLayout(layout);
}