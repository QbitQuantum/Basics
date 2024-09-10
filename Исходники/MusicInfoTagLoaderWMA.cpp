CStdString fixString(CStdString &ansiString)
// ucs2CharsetToStringCharset is always called even when not required resulting in some strings
// twice the length they should be. This function is a quick fix to the problem. The correct
// solution would be to call ucs2CharsetToStringCharset only when necessary.
{
  int halfLen = ansiString.length() / 2 - 1;
  CStdString out = "";

  if (halfLen > 0)
    if (*(ansiString.Mid(halfLen, 1).c_str()) == 0 &&
        *(ansiString.Mid(halfLen + 1, 1).c_str()) == 0)
      out = ansiString.Left(halfLen);
  if (out == "")
    return ansiString ;
  else
    return out ;
}