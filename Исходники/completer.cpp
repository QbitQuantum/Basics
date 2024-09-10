void Completer::invokeCompletion( QPlainTextEdit* editor )
{
    if ( !isVisible() )
    {
        mEditor = editor;
        setParent( mEditor, windowFlags() );
        QPoint position = mEditor->mapToGlobal( mEditor->cursorRect().topLeft() );
        int h = mEditor->cursorRect().height();
        QDesktopWidget *dw = QApplication::desktop();

        if(position.ry() < (dw->screen()->height()-height()))
            position.ry() += h;
        else
            position.ry() -= (h+height());

        move( position );
        if ( prepareCompletion() )
        {
            show();
            lwItems->setFocus();
        }
    }
}