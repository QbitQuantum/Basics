bool ShortcutEdit::eventFilter(QObject* watched, QEvent* event)
{
    if ((watched == m_edit) && (event->type() == QEvent::KeyPress)) {
        QKeyEvent* key_event = static_cast<QKeyEvent*>(event);

        Qt::KeyboardModifiers modifiers = key_event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier);
        int key = key_event->key();

        switch (key) {
        // Don't do anything if they only press a modifier
        case Qt::Key_Shift:
        case Qt::Key_Control:
        case Qt::Key_Meta:
        case Qt::Key_Alt:
            return true;

        // Clear on backspace unless modifier is used
        case Qt::Key_Backspace:
        case Qt::Key_Delete:
            if (modifiers == Qt::NoModifier) {
                clear();
                return true;
            }
            break;

        // Allow tab to change focus
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            return false;

        default:
            break;
        }

        // Add modifiers; only allow shift if it is not required for key of shortcut
        if ((modifiers & Qt::ShiftModifier) && !key_event->text().isEmpty()) {
            QChar c = key_event->text().at(0);
            if (c.isPrint() && !c.isLetterOrNumber() && !c.isSpace()) {
                key |= Qt::SHIFT;
            }
        }
        if (modifiers & Qt::ControlModifier) {
            key |= Qt::CTRL;
        }
        if (modifiers & Qt::MetaModifier) {
            key |= Qt::META;
        }
        if (modifiers & Qt::AltModifier) {
            key |= Qt::ALT;
        }

        // Change shortcut
        m_shortcut = QKeySequence(key);
        setText();
        emit changed();

        return true;
    } else {
        return QWidget::eventFilter(watched, event);
    }
}