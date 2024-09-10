bool HelpBrowser::eventFilter(QObject *object, QEvent *event)
{
    if (object == mWebView) {
        switch (event->type()) {
        case QEvent::MouseButtonPress: {
            QMouseEvent * mouseEvent = static_cast<QMouseEvent*>(event);
            switch (mouseEvent->button()) {
            case Qt::XButton1:
                mWebView->pageAction(QWebPage::Back)->trigger();
                return true;

            case Qt::XButton2:
                mWebView->pageAction(QWebPage::Forward)->trigger();
                return true;

            default:
                break;
            }
            break;
        }
        case QEvent::ShortcutOverride: {
            QKeyEvent * kevent = static_cast<QKeyEvent*>(event);
            if ( kevent == QKeySequence::Copy ||
                 kevent == QKeySequence::Paste )
            {
                kevent->accept();
                return true;
            }
            break;
        }
        default:
            break;
        }
    }
    return false;
}