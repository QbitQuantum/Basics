bool KexiRecordNavigator::eventFilter(QObject *o, QEvent *e)
{
    if (o == d->navRecordNumber) {
        bool recordEntered = false;
        bool ret;
        if (e->type() == QEvent::KeyPress) {
            QKeyEvent *ke = static_cast<QKeyEvent*>(e);
            switch (ke->key()) {
            case Qt::Key_Escape: {
                ke->accept();
                d->navRecordNumber->undo();
                if (d->view)
                    d->view->setFocus();
                return true;
            }
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Tab:
            case Qt::Key_Backtab: {
                recordEntered = true;
                ke->accept(); //to avoid pressing Enter later
                ret = true;
            }
            default:;
            }
        } else if (e->type() == QEvent::FocusOut) {
            if (static_cast<QFocusEvent*>(e)->reason() != Qt::TabFocusReason
                    && static_cast<QFocusEvent*>(e)->reason() != Qt::BacktabFocusReason
                    && static_cast<QFocusEvent*>(e)->reason() != Qt::OtherFocusReason)
            {
                recordEntered = true;
            }
            ret = false;
        }

        if (recordEntered) {
            bool ok = true;
            uint r = d->navRecordNumber->text().toUInt(&ok);
            if (!ok || r < 1)
                r = (recordCount() > 0) ? 1 : 0;
            if (d->view && (hasFocus() || e->type() == QEvent::KeyPress))
                d->view->setFocus();
            setCurrentRecordNumber(r);
            emit recordNumberEntered(r);
            if (d->handler)
                d->handler->moveToRecordRequested(r - 1);
            return ret;
        }
    }
    return false;
}