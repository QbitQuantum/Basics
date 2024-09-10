void GLFOutputWindow::printMessage(const char* message)
{
    static int index = 1;
    // Remove the first few lines when the buffer is overflow.
    int nlines = _pTextEdit->document()->lineCount();
    if (nlines > MAX_NUM_LINES)
    {
        int deleteNumLines = nlines / 2;
        for (int i = 0; i < deleteNumLines; ++i)
        {
            QTextCursor tc = _pTextEdit->textCursor();

            tc.movePosition(QTextCursor::Start);
            tc.select(QTextCursor::LineUnderCursor);
            tc.removeSelectedText();
        }

        QTextCursor tc = _pTextEdit->textCursor();
        tc.movePosition(QTextCursor::End);
        _pTextEdit->setTextCursor(tc);            
    }

    // Insert the new message
    char buffer[1024];
    sprintf(buffer, "%d: %s", index++, message);
    _pTextEdit->insertPlainText(QString(buffer));

    // Scroll to the bottom
    QScrollBar *sb = _pTextEdit->verticalScrollBar();
    sb->setValue(sb->maximum());
}