PRBool
ParseString(const nsACString& aSource, char aDelimiter, 
            nsTArray<nsCString>& aArray)
{
  PRInt32 start = 0;
  PRInt32 end = aSource.Length();

  PRUint32 oldLength = aArray.Length();

  for (;;) {
    PRInt32 delimiter = aSource.FindChar(aDelimiter, start);
    if (delimiter < 0) {
      delimiter = end;
    }

    if (delimiter != start) {
      if (!aArray.AppendElement(Substring(aSource, start, delimiter - start))) {
        aArray.RemoveElementsAt(oldLength, aArray.Length() - oldLength);
        return PR_FALSE;
      }
    }

    if (delimiter == end)
      break;
    start = ++delimiter;
    if (start == end)
      break;
  }

  return PR_TRUE;
}