void UIRuntimeMiniToolBar::integrate()
{
    /* Reintegrate if necessary: */
    if (m_integrationMode == IntegrationMode_Embedded && isWindow())
    {
        setWindowFlags(Qt::Widget);
#ifdef VBOX_RUNTIME_UI_WITH_SHAPED_MINI_TOOLBAR
        setAttribute(Qt::WA_TranslucentBackground, false);
#endif /* VBOX_RUNTIME_UI_WITH_SHAPED_MINI_TOOLBAR */
        show();
    }
    else if (m_integrationMode == IntegrationMode_External && !isWindow())
    {
        setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
#ifdef VBOX_RUNTIME_UI_WITH_SHAPED_MINI_TOOLBAR
        setAttribute(Qt::WA_TranslucentBackground, true);
#endif /* VBOX_RUNTIME_UI_WITH_SHAPED_MINI_TOOLBAR */
        show();
    }
}