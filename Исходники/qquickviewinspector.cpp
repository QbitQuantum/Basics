void QQuickViewInspector::setWindowFlags(Qt::WindowFlags flags)
{
    QWindow *w = getMasterWindow(m_view);
    w->setFlags(flags);
    // make flags are applied
    w->setVisible(false);
    w->setVisible(true);
}