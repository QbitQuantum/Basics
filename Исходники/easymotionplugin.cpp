 void searchTargetFromScreen(QEditor *editor, const QChar &target)
 {
   m_targetPos.clear();
   if (editor == NULL) {
     return;
   }
   m_currentGroup = 0;
   m_targetChar = target;
   QTextDocument *doc = editor->document();
   int cursorPos = editor->textCursor().position();
   QPair<int, int> visibleRange = getFirstAndLastVisiblePosition(editor);
   int  firstPos = visibleRange.first;
   int lastPos = visibleRange.second;
   bool notCaseSensative = target.category() != QChar::Letter_Uppercase;
   for (int offset = 1; cursorPos - offset >= firstPos || cursorPos + offset <= lastPos; offset++) {
     if (cursorPos + offset <= lastPos) {
       QChar c = doc->characterAt(cursorPos + offset);
       if (notCaseSensative) {
         c = c.toLower();
       }
       if (c == target) {
         m_targetPos << (cursorPos + offset);
       }
     }
     if (cursorPos - offset >= firstPos) {
       QChar c = doc->characterAt(cursorPos - offset);
       if (notCaseSensative) {
         c = c.toLower();
       }
       if (c == target) {
         m_targetPos << (cursorPos - offset);
       }
     }
   }
 }