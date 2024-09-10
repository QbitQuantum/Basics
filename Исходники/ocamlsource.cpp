void OCamlSource::mousePressEvent ( QMouseEvent * e )
{
    QTextCursor current_cur = textCursor();
    QTextCursor cur = cursorForPosition( e->pos() );
    if ( current_cur.hasSelection() )
        cur = current_cur;

    _breakpoint_line   = cur.blockNumber() + 1;
    _breakpoint_column = cur.position() - cur.block().position() + 1;
    if ( ! cur.hasSelection() )
    {
        cur.select(QTextCursor::WordUnderCursor);
        setTextCursor(cur);
    }
    _selected_text = cur.selectedText();
    if ( e->button() == Qt::LeftButton )
    {
        lineSearchArea->hide();
        lineSearchArea->setEnabled(false);
        setFocus();
    }

    if ( e->button() == Qt::MidButton )
    {
        watchVar();
    }
    else
        QPlainTextEdit::mousePressEvent(e);
}