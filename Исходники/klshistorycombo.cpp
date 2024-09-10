bool KLSHistoryCombo::eventFilter( QObject *o, QEvent *ev )
{
    // Handle Ctrl+Del/Backspace etc better than the Qt widget, which always
    // jumps to the next whitespace.
    QLineEdit *edit = lineEdit();
    if ( o == edit )
    {
        int type = ev->type();
        if ( type == QEvent::KeyPress )
        {
            QKeyEvent *e = static_cast<QKeyEvent *>( ev );

            if ( e->key() == Key_Return || e->key() == Key_Enter )
            {
                //m_modifier = e->state();
                return false;
            }

            int delete_word_back = KStdAccel::deleteWordBack().keyCodeQt();
            int delete_word_forward = KStdAccel::deleteWordForward().keyCodeQt();

            if ( KKey( e ) == KKey(delete_word_back) ||
                    KKey( e ) == KKey(delete_word_forward) ||
                    ((e->state() & ControlButton) &&
                     (e->key() == Key_Left || e->key() == Key_Right) ) )
            {
                selectWord(e);
                e->accept();
                return true;
            }
        }

        else if ( type == QEvent::MouseButtonDblClick )
        {
            edit->selectAll();
            return true;
        }
    }
    return KComboBox::eventFilter( o, ev );
}