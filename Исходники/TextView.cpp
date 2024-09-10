bool TextView::eventFilter(QObject *obj, QEvent *event)
{
#ifdef SCINTILLA
    QAbstractScrollArea * sa = scintEditor;
#else
    QAbstractScrollArea * sa = plainTextEdit;
#endif

    if (obj == sa) {
        sa->setAttribute(Qt::WA_NoMousePropagation, false);
        if (event->type() == QEvent::KeyPress) {
             QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
             switch (keyEvent->key())
             {
                 case Qt::Key_Z:
                     if (keyEvent->modifiers().testFlag(Qt::ShiftModifier) && keyEvent->modifiers().testFlag(Qt::ControlModifier)) {
                         byteSource->historyForward();
                         keyEvent->accept();
                         return true;
                     }
                     else if (keyEvent->modifiers().testFlag(Qt::ControlModifier)) {
                         byteSource->historyBackward();
                         keyEvent->accept();
                         return true;
                     }
                    break;
                 default:
                     return false;
             }

        } else if (event->type() == QEvent::Wheel) {
            if (sa->verticalScrollBar()->isVisible()) {
                sa->setAttribute(Qt::WA_NoMousePropagation);
            }

            return false;
        }
    }

    return QWidget::eventFilter(obj, event);

}