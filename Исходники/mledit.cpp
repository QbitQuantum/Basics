void MLEdit::contextMenuEvent(QContextMenuEvent* event)
{
  QMenu* menu=createStandardContextMenu();

  if (!isReadOnly())
  {
#ifdef HAVE_HUNSPELL
    // Save position so we know which word to replace
    myMenuPos = event->pos();

    // Get word under cursor
    QTextCursor cr = cursorForPosition(myMenuPos);
    cr.select(QTextCursor::WordUnderCursor);
    QString word = cr.selectedText();
    if (!word.isEmpty())
    {
      // Get spelling suggestions
      QStringList suggestions = mySpellChecker->getSuggestions(word);
      if (!suggestions.isEmpty())
      {
        // Add spelling suggestions at the top of the menu
        QAction* firstAction = menu->actions().first();
        foreach (QString w, suggestions)
        {
          QAction* a = new QAction(w, menu);
          connect(a, SIGNAL(triggered()), SLOT(replaceWord()));
          menu->insertAction(firstAction, a);
        }