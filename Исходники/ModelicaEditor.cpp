/*!
  Slot activated when toggle comment selection is seleteted from context menu or ctrl+k is pressed.
  The implementation and logic is inspired from Qt Creator sources.
  */
void ModelicaEditor::toggleCommentSelection()
{
  CommentDefinition definition;
  if (!definition.hasSingleLineStyle() && !definition.hasMultiLineStyle()) {
    return;
  }

  QTextCursor cursor = mpPlainTextEdit->textCursor();
  QTextDocument *doc = cursor.document();
  cursor.beginEditBlock();

  int pos = cursor.position();
  int anchor = cursor.anchor();
  int start = qMin(anchor, pos);
  int end = qMax(anchor, pos);
  bool anchorIsStart = (anchor == start);

  QTextBlock startBlock = doc->findBlock(start);
  QTextBlock endBlock = doc->findBlock(end);

  if (end > start && endBlock.position() == end) {
    --end;
    endBlock = endBlock.previous();
  }

  bool doMultiLineStyleUncomment = false;
  bool doMultiLineStyleComment = false;
  bool doSingleLineStyleUncomment = false;

  bool hasSelection = cursor.hasSelection();

  if (hasSelection && definition.hasMultiLineStyle()) {

    QString startText = startBlock.text();
    int startPos = start - startBlock.position();
    const int multiLineStartLength = definition.multiLineStart().length();
    bool hasLeadingCharacters = !startText.left(startPos).trimmed().isEmpty();

    if (startPos >= multiLineStartLength
        && isComment(startText,
                     startPos - multiLineStartLength,
                     definition,
                     &CommentDefinition::multiLineStart)) {
      startPos -= multiLineStartLength;
      start -= multiLineStartLength;
    }

    bool hasSelStart = (startPos <= startText.length() - multiLineStartLength
                        && isComment(startText,
                                     startPos,
                                     definition,
                                     &CommentDefinition::multiLineStart));

    QString endText = endBlock.text();
    int endPos = end - endBlock.position();
    const int multiLineEndLength = definition.multiLineEnd().length();
    bool hasTrailingCharacters =
        !endText.left(endPos).remove(definition.singleLine()).trimmed().isEmpty()
        && !endText.mid(endPos).trimmed().isEmpty();

    if (endPos <= endText.length() - multiLineEndLength
        && isComment(endText, endPos, definition, &CommentDefinition::multiLineEnd)) {
      endPos += multiLineEndLength;
      end += multiLineEndLength;
    }

    bool hasSelEnd = (endPos >= multiLineEndLength
                      && isComment(endText,
                                   endPos - multiLineEndLength,
                                   definition,
                                   &CommentDefinition::multiLineEnd));

    doMultiLineStyleUncomment = hasSelStart && hasSelEnd;
    doMultiLineStyleComment = !doMultiLineStyleUncomment
        && (hasLeadingCharacters
            || hasTrailingCharacters
            || !definition.hasSingleLineStyle());
  } else if (!hasSelection && !definition.hasSingleLineStyle()) {

    QString text = startBlock.text().trimmed();
    doMultiLineStyleUncomment = text.startsWith(definition.multiLineStart())
        && text.endsWith(definition.multiLineEnd());
    doMultiLineStyleComment = !doMultiLineStyleUncomment && !text.isEmpty();

    start = startBlock.position();
    end = endBlock.position() + endBlock.length() - 1;

    if (doMultiLineStyleUncomment) {
      int offset = 0;
      text = startBlock.text();
      const int length = text.length();
      while (offset < length && text.at(offset).isSpace())
        ++offset;
      start += offset;
    }
  }

  if (doMultiLineStyleUncomment) {
    cursor.setPosition(end);
    cursor.movePosition(QTextCursor::PreviousCharacter,
                        QTextCursor::KeepAnchor,
                        definition.multiLineEnd().length());
    cursor.removeSelectedText();
    cursor.setPosition(start);
    cursor.movePosition(QTextCursor::NextCharacter,
                        QTextCursor::KeepAnchor,
                        definition.multiLineStart().length());
    cursor.removeSelectedText();
  } else if (doMultiLineStyleComment) {
    cursor.setPosition(end);
    cursor.insertText(definition.multiLineEnd());
    cursor.setPosition(start);
    cursor.insertText(definition.multiLineStart());
  } else {
    endBlock = endBlock.next();
    doSingleLineStyleUncomment = true;
    for (QTextBlock block = startBlock; block != endBlock; block = block.next()) {
      QString text = block.text().trimmed();
      if (!text.isEmpty() && !text.startsWith(definition.singleLine())) {
        doSingleLineStyleUncomment = false;
        break;
      }
    }

    const int singleLineLength = definition.singleLine().length();
    for (QTextBlock block = startBlock; block != endBlock; block = block.next()) {
      if (doSingleLineStyleUncomment) {
        QString text = block.text();
        int i = 0;
        while (i <= text.size() - singleLineLength) {
          if (isComment(text, i, definition, &CommentDefinition::singleLine)) {
            cursor.setPosition(block.position() + i);
            cursor.movePosition(QTextCursor::NextCharacter,
                                QTextCursor::KeepAnchor,
                                singleLineLength);
            cursor.removeSelectedText();
            break;
          }
          if (!text.at(i).isSpace())
            break;
          ++i;
        }
      } else {
        QString text = block.text();
        foreach(QChar c, text) {
          if (!c.isSpace()) {
            if (definition.isAfterWhiteSpaces())
              cursor.setPosition(block.position() + text.indexOf(c));
            else
              cursor.setPosition(block.position());
            cursor.insertText(definition.singleLine());
            break;
          }
        }
      }
    }
  }
  // adjust selection when commenting out
  if (hasSelection && !doMultiLineStyleUncomment && !doSingleLineStyleUncomment) {
    cursor = mpPlainTextEdit->textCursor();
    if (!doMultiLineStyleComment)
      start = startBlock.position(); // move the comment into the selection
    int lastSelPos = anchorIsStart ? cursor.position() : cursor.anchor();
    if (anchorIsStart) {
      cursor.setPosition(start);
      cursor.setPosition(lastSelPos, QTextCursor::KeepAnchor);
    } else {
      cursor.setPosition(lastSelPos);
      cursor.setPosition(start, QTextCursor::KeepAnchor);
    }
    mpPlainTextEdit->setTextCursor(cursor);
  }
  cursor.endEditBlock();
}