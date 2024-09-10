bool QMarkdownTextEdit::eventFilter(QObject* obj, QEvent *event)
{
    if ( event->type() == QEvent::KeyPress )
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if ( ( keyEvent->key() == Qt::Key_Tab ) || ( keyEvent->key() == Qt::Key_Backtab ) )
        {
            // indent selected text (if there is a text selected)
            return increaseSelectedTextIndention( keyEvent->key() == Qt::Key_Backtab );
        }
        else if ( ( keyEvent->key() == Qt::Key_F ) && QGuiApplication::keyboardModifiers() == Qt::ExtraButton24 )
        {
            qDebug()<<"Ctrl + F";
            return false;
        }
        // set cursor to pointing hand if control key was pressed
        else if ( keyEvent->key() == Qt::Key_Control )
        {
            QWidget *viewPort = this->viewport();
            viewPort->setCursor( Qt::PointingHandCursor );
            return false;
        }

        return false;
    }
    else if ( event->type() == QEvent::KeyRelease )
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        // reset cursor if control key was released
        if ( keyEvent->key() == Qt::Key_Control )
        {
            QWidget *viewPort = this->viewport();
            viewPort->setCursor( Qt::IBeamCursor );
        }

        return false;
    }
    else if ( event->type() == QEvent::MouseButtonRelease )
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        // track Ctrl+LeftMouseClick in the noteTextEdit
        if ( ( obj == this->viewport() ) && ( mouseEvent->button() == Qt::LeftButton ) && ( QGuiApplication::keyboardModifiers() == Qt::ExtraButton24 ) )
        {
            // open the link (if any) at the current position in the noteTextEdit
            openLinkAtCursorPosition();
            return false;
        }
    }

    return QTextEdit::eventFilter( obj, event );
}