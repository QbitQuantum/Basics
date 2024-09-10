void RtfCssEditor::insertBrace() {
  if (c->widget() != this)
    return;
  QTextCursor tc = textCursor();
  int currentPos = tc.position();
  tc.movePosition(QTextCursor::Down);
  tc.select(QTextCursor::LineUnderCursor);
  if (tc.selectedText().isEmpty() == true) {
    tc.setPosition(currentPos);
    //if (QTextCursor::NextWord)
    tc.insertText("\n    \n}");
    /*tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::Left);*/
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::Left);
    setTextCursor(tc);
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0) + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!
  }
  else {
    tc.setPosition(currentPos);
    tc.insertText("\n    ");
  }
  tc.movePosition(QTextCursor::EndOfWord);
  QRect cr = cursorRect();
  cr.setWidth(c->popup()->sizeHintForColumn(0) + c->popup()->verticalScrollBar()->sizeHint().width());
  c->complete(cr); // popup it up!
    
}