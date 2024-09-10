GraphicsProxySimpleBrowser::GraphicsProxySimpleBrowser(QGraphicsItem *parent) :
    QGraphicsWidget(parent)
  , mGraphicsWebView(0)
{
    QWebSettings *gs = QWebSettings::globalSettings();
    gs->setAttribute(QWebSettings::JavaEnabled, true);
    gs->setAttribute(QWebSettings::PluginsEnabled, true);
    gs->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
    gs->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    gs->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    gs->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
    gs->setAttribute(QWebSettings::DnsPrefetchEnabled, true);

    setAutoFillBackground(true);

    mGraphicsWebView = new QGraphicsProxyWidget();
    mGraphicsWebView->setWidget(new SimpleBrowser());

    mLabel = new QLabel("QGraphicsProxyWidget");

    mCloseButton = new QToolButton();
    mCloseButton->setAutoRaise(true);
    mCloseButton->setText("X");

    QGraphicsLinearLayout *mainLayer = new QGraphicsLinearLayout(Qt::Vertical);

    QGraphicsLinearLayout *titleLayout = new QGraphicsLinearLayout(Qt::Horizontal);

    QGraphicsProxyWidget *proxyLabel = new QGraphicsProxyWidget();
    proxyLabel->setWidget(mLabel);

    QGraphicsProxyWidget *proxyCloseButton = new QGraphicsProxyWidget();
    proxyCloseButton->setWidget(mCloseButton);

    titleLayout->addItem(proxyLabel);
    titleLayout->addItem(proxyCloseButton);

    QGraphicsWidget *titleLayoutItem = new QGraphicsWidget();
    titleLayoutItem->setLayout(titleLayout);

    mainLayer->addItem(titleLayoutItem);
    mainLayer->addItem(mGraphicsWebView);

    setLayout(mainLayer);

    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(on_mCloseButton_clicked()));

    setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);

}