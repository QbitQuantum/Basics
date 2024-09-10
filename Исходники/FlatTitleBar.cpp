bool FlatTitleBar::eventFilter(QObject *, QEvent *event)
{
    switch (event->type()) {
        case QEvent::WindowActivate:
        case QEvent::WindowDeactivate:
            updateColors();
        default:
            break;
    }
    return false;
}