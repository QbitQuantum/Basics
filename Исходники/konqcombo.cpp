bool KonqCombo::eventFilter( QObject *o, QEvent *ev )
{
    // Handle Ctrl+Del/Backspace etc better than the Qt widget, which always
    // jumps to the next whitespace.
    QLineEdit *edit = lineEdit();
    if ( o == edit ) {
        const int type = ev->type();
        if (type == QEvent::KeyPress) {
            QKeyEvent *e = static_cast<QKeyEvent *>( ev );

            KShortcut key( e->key() | e->modifiers() );

            if ( key == KStandardShortcut::deleteWordBack() ||
                 key == KStandardShortcut::deleteWordForward() ||
                 ((e->modifiers() & Qt::ControlModifier) &&
                   (e->key() == Qt::Key_Left || e->key() == Qt::Key_Right) ) ) {
                selectWord(e);
                e->accept();
                return true;
            }
        }

        else if ( type == QEvent::MouseButtonDblClick ) {
            edit->selectAll();
            return true;
        }
    }
    return KComboBox::eventFilter( o, ev );
}