ChainsProxyPage::ChainsProxyPage(QWidget *parent) : ContentWidget(parent)
{
    setTitle(tr("Application Proxy"));

    m_proxyType = new NextPageWidget;
    m_proxyType->setTitle(tr("Proxy Type"));

    m_addr = new LineEditWidget;
    m_addr->setTitle(tr("IP address"));
    m_addr->setPlaceholderText(tr("Required"));

    m_port = new LineEditWidget;
    m_port->setTitle(tr("Port"));
    m_port->setPlaceholderText(tr("Required"));

    m_username = new LineEditWidget;
    m_username->setTitle(tr("Username"));
    m_username->setPlaceholderText(tr("Optional"));

    m_password = new LineEditWidget;
    m_password->setTitle(tr("Password"));
    m_password->setPlaceholderText(tr("Optional"));
    m_password->textEdit()->setEchoMode(QLineEdit::Password);

    SettingsGroup *grp = new SettingsGroup;
    grp->appendItem(m_proxyType);
    grp->appendItem(m_addr);
    grp->appendItem(m_port);
    grp->appendItem(m_username);
    grp->appendItem(m_password);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(10);

    layout->addSpacing(20);
    layout->addWidget(grp);

    QLabel *tip = new QLabel;
    tip->setText(tr("Check \"Use a proxy\" in application context menu in Launcher after configured"));
    tip->setWordWrap(true);
    layout->addWidget(tip);

    ButtonTuple *btns = new ButtonTuple;
    btns->leftButton()->setText(tr("Cancel"));
    btns->rightButton()->setText(tr("OK"));

    layout->addWidget(btns);

    layout->addStretch();

    TranslucentFrame *w = new TranslucentFrame;
    w->setLayout(layout);

    setContent(w);

    connect(btns->leftButton(), &QPushButton::clicked, this, &ChainsProxyPage::back);
    connect(btns->rightButton(), &QPushButton::clicked, this, &ChainsProxyPage::onCheckValue);
    connect(m_proxyType, &NextPageWidget::clicked, this, &ChainsProxyPage::requestShowTypePage);
}