void EmbeddedWebView::handlePageLoadFinished()
{
    constrainSize();

    // We've already set it in our constructor, but apparently it isn't enough (Qt 4.8.0 on X11).
    // Let's do it again here, it works.
    Qt::ScrollBarPolicy policy = isWindow() ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOff;
    page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, policy);
    page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, policy);
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}