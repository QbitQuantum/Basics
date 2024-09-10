void XYZTextEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format) {
    QTextCursor cursor = m_ui->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    m_ui->textEdit->mergeCurrentCharFormat(format);
}