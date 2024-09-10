QDeclarativeWebView* QDeclarativeWebView::createWindow(QWebPage::WebWindowType type)
{
    switch (type) {
    case QWebPage::WebBrowserWindow: {
        if (!d->newWindowComponent && d->newWindowParent)
            qWarning("WebView::newWindowComponent not set - WebView::newWindowParent ignored");
        else if (d->newWindowComponent && !d->newWindowParent)
            qWarning("WebView::newWindowParent not set - WebView::newWindowComponent ignored");
        else if (d->newWindowComponent && d->newWindowParent) {
            QDeclarativeWebView* webview = 0;
            QDeclarativeContext* windowContext = new QDeclarativeContext(qmlContext(this));

            QObject* newObject = d->newWindowComponent->create(windowContext);
            if (newObject) {
                windowContext->setParent(newObject);
                QDeclarativeItem* item = qobject_cast<QDeclarativeItem *>(newObject);
                if (!item)
                    delete newObject;
                else {
                    webview = item->findChild<QDeclarativeWebView*>();
                    if (!webview)
                        delete item;
                    else {
                        newObject->setParent(d->newWindowParent);
                        static_cast<QGraphicsObject*>(item)->setParentItem(d->newWindowParent);
                    }
                }
            } else
                delete windowContext;

            return webview;
        }
    }
    break;
    case QWebPage::WebModalDialog: {
        // Not supported
    }
    }
    return 0;
}