/** \brief Anhängen einer Zeile ans Ende.

  Am Ende der Ausgabe wird immer ein Newline + Prompt ausgegeben!
*/
void QCommandPrompt::write(QString sMsg, QColor /*col*/)
{
    // Überprüfen, ob die Zeile mit einem Prompt anfängt
    QTextCursor tc = textCursor();
    tc.movePosition(QTextCursor::StartOfLine);
    tc.select(QTextCursor::LineUnderCursor);
    tc.removeSelectedText();
    setTextCursor(tc);

    // old: simple text
    insertPlainText(sMsg + "\n" + m_sPrompt);
/*
    // colored version
    QBrush brush(Qt::SolidPattern);
    brush.setColor(col);

    QTextCharFormat fmt;
    fmt.setForeground(brush);
    tc.insertText(sMsg + "\n", fmt);

    brush.setColor(m_colDefault);
    fmt.setForeground(brush);
    tc.insertText(m_sPrompt, fmt);
*/
    m_nPromptPos = tc.position();

    ensureCursorVisible();
}