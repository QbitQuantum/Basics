/**
 * Get the clipboard name if there is one.
 * @param UINT format the format we want the name of.
 * @return wchar_t* the format name or NULL if there isn't one, (or not needed).
 */
wchar_t* ClipboardData::GetClipboardName(UINT format)
{
  // if it is a known type then we don't need/have the name
  if (format < CF_MAX)
  {
    return NULL;
  }

  //  get the text from the clipboard.
  static const unsigned l = 1024;  //  max len of the meta file
  wchar_t* dataName = new wchar_t[l + 1];
  memset(dataName, 0, l + 1);
  if (GetClipboardFormatNameW(format, dataName, l) == 0)
  {
    //  either it did not work
    // or the value we found is not good.
    delete[] dataName;
    return NULL;
  }

  // return the value we found.
  return dataName;
}