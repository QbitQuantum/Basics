bool QCompletionEdit::eventFilter( QObject *o, QEvent *e )
{
    if ( o == popup || o == listbox || o == listbox->viewport() ) {
	if ( e->type() == QEvent::KeyPress ) {
	    QKeyEvent *ke = (QKeyEvent*)e;
	    if ( ke->key() == Key_Enter || ke->key() == Key_Return || ke->key() == Key_Tab ) {
		if ( ke->key() == Key_Tab && listbox->count() > 1 &&
		     listbox->currentItem() < (int)listbox->count() - 1 ) {
		    listbox->setCurrentItem( listbox->currentItem() + 1 );
		    return TRUE;
		}
		popup->close();
		setFocus();
		blockSignals( TRUE );
		setText( listbox->currentText() );
		blockSignals( FALSE );
		emit chosen( text() );
		return TRUE;
	    } else if ( ke->key() == Key_Left || ke->key() == Key_Right ||
			ke->key() == Key_Up || ke->key() == Key_Down ||
			ke->key() == Key_Home || ke->key() == Key_End ||
			ke->key() == Key_Prior || ke->key() == Key_Next ) {
		return FALSE;
	    } else if ( ke->key() == Key_Escape ) {
		popup->close();
		setFocus();
	    } else if ( ke->key() != Key_Shift && ke->key() != Key_Control &&
			ke->key() != Key_Alt ) {
		updateListBox();
		if ( listbox->count() == 0 || text().length() == 0 ) {
		    popup->close();
		    setFocus();
		}
		QApplication::sendEvent( this, e );
		return TRUE;
	    }
	} else if ( e->type() == QEvent::MouseButtonDblClick ) {
	    popup->close();
	    setFocus();
	    blockSignals( TRUE );
	    setText( listbox->currentText() );
	    blockSignals( FALSE );
	    emit chosen( text() );
	    return TRUE;
	}
    } else if ( o == this ) {
	if ( e->type() == QEvent::KeyPress ) {
	    QKeyEvent *ke = (QKeyEvent*)e;
	    if ( ke->key() == Key_Up ||
		 ke->key() == Key_Down ||
		 ke->key() == Key_Prior ||
		 ke->key() == Key_Next ||
		 ke->key() == Key_Return ||
		 ke->key() == Key_Enter ||
		 ke->key() == Key_Tab ||
		 ke->key() ==  Key_Escape ) {
		QApplication::sendEvent( listbox, e );
		return TRUE;
	    }
	}
    }
    return QLineEdit::eventFilter( o, e );
}