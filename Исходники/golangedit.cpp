void GolangEdit::findLinkOutput(QByteArray data, bool bStdErr)
{
    if (bStdErr) {
        return;
    }

    if ( m_editor == m_liteApp->editorManager()->currentEditor()) {
        QTextCursor cur = this->textCursorForPos(QCursor::pos());
        cur.select(QTextCursor::WordUnderCursor);
        if (cur.selectionStart() == m_linkCursor.selectionStart() &&
                cur.selectionEnd() == m_linkCursor.selectionEnd()) {
            QStringList info = QString::fromUtf8(data).trimmed().split("\n");
            if (info.size() == 2) {
                if (info[0] != "-") {
                    QRegExp reg(":(\\d+):(\\d+)");
                    int pos = reg.lastIndexIn(info[0]);
                    if (pos >= 0) {
                        QString fileName = info[0].left(pos);
                        int line = reg.cap(1).toInt();
                        int col = reg.cap(2).toInt();
                        LiteApi::Link link(fileName,line-1,col-1);
                        m_lastCursor.select(QTextCursor::WordUnderCursor);
                        link.linkTextStart = m_linkCursor.selectionStart();
                        link.linkTextEnd = m_linkCursor.selectionEnd();
                        m_lastLink = link;
                        m_editor->showLink(link);
                    }
                }
                QRect rc = m_plainTextEdit->cursorRect(m_linkCursor);
                QPoint pt = m_plainTextEdit->mapToGlobal(rc.topRight());
                QToolTip::showText(pt,info[1],m_plainTextEdit);
            }
        }
    }
}