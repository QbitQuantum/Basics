void ExplorerPane::updateErrors(const QString& errors)
{
    QTextEdit *errorWidget = dynamic_cast<QTextEdit *>(errorsPage);
    if (errorWidget)
    {
        // Get the current text
        QString text = errorWidget->toPlainText();
        if (!text.isEmpty())
        {
            // Set the text color to light grey
            errorWidget->setTextColor(QColor("grey"));
            // Restore the current text
            errorWidget->setPlainText(text);
        }
        // Set the text color to red
        errorWidget->setTextColor(QColor("red"));
        // Append the new error message
        errorWidget->append(errors);
        // Place cursor at end of text
        errorWidget->moveCursor(QTextCursor::End);
        // Raise the Error tab
        tabWidget->setCurrentWidget(errorsPage);
    }
}