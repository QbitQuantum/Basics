MyGlobalShortCut::MyGlobalShortCut(QString key, QObject *app)
{
    m_key = QKeySequence(key);
    m_filter = new MyWinEventFilter(this);
    m_app->installNativeEventFilter(m_filter);


    registerHotKey();
}