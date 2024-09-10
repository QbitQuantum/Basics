TabbedWebView::TabbedWebView(QupZilla* mainClass, WebTab* webTab)
    : WebView(webTab)
    , p_QupZilla(mainClass)
    , m_tabWidget(p_QupZilla->tabWidget())
    , m_page(0)
    , m_webTab(webTab)
    , m_menu(new Menu(this))
    , m_mouseTrack(false)
    , m_navigationVisible(false)
    , m_hasRss(false)
    , m_rssChecked(false)
{
    connect(this, SIGNAL(loadStarted()), this, SLOT(slotLoadStarted()));
    connect(this, SIGNAL(loadProgress(int)), this, SLOT(loadingProgress(int)));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(slotLoadFinished()));

    connect(this, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
    connect(this, SIGNAL(titleChanged(QString)), this, SLOT(titleChanged()));
    connect(this, SIGNAL(iconChanged()), this, SLOT(slotIconChanged()));

    connect(this, SIGNAL(statusBarMessage(QString)), p_QupZilla->statusBar(), SLOT(showMessage(QString)));

    connect(mApp->networkManager(), SIGNAL(wantsFocus(QUrl)), this, SLOT(getFocus(QUrl)));

    connect(p_QupZilla, SIGNAL(setWebViewMouseTracking(bool)), this, SLOT(trackMouse(bool)));

    // Tracking mouse also on tabs created in fullscreen
    trackMouse(p_QupZilla->isFullScreen());
}