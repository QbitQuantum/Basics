void DrugInputEdit::handleCompleteDrugName(QString addName) {
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::LineUnderCursor);
    tc.removeSelectedText();
    tc.insertText(addName + "\n");
    setTextCursor(tc);
}