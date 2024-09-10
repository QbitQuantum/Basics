/**
 * Is the final character, ignoring trailing whitespace, a colon
 *
 */
bool InputSplitter::finalCharIsColon(const QString & str) const
{
  QChar singleChar;
  int index = str.size() - 1;
  for (; index >= 0; --index)
  {
    singleChar = str.at(index);
    if(singleChar.isSpace()) continue;
    else break;
  }
  return (singleChar == ':');
}