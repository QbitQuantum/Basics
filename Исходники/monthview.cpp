bool MonthView::eventFilter(QObject *o, QEvent *e)
{
    if ( e->type() == QEvent::KeyPress) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(e);
        if (ke->key() == Qt::Key_Back) {
            emit closeView();
            ke->accept();
            return true;
        }
    }
    return QCalendarWidget::eventFilter(o, e);
}