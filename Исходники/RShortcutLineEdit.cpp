bool RShortcutLineEdit::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *> (event);
        int nextKey = keyEvent->key();
        if (m_keyNum > 3 || nextKey == Qt::Key_Control || nextKey
                == Qt::Key_Shift || nextKey == Qt::Key_Meta || nextKey
                == Qt::Key_Alt)
            return true;

        nextKey |= translateModifiers(keyEvent->modifiers(), keyEvent->text());
        switch (m_keyNum) {
        case 0:
            m_key[0] = nextKey;
            break;
        case 1:
            m_key[1] = nextKey;
            break;
        case 2:
            m_key[2] = nextKey;
            break;
        case 3:
            m_key[3] = nextKey;
            break;
        default:
            break;
        }
        m_keyNum++;
        QKeySequence ks(m_key[0], m_key[1], m_key[2], m_key[3]);
        setText(ks);
        keyEvent->accept();
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}