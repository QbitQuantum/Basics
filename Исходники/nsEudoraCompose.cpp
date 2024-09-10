void nsEudoraCompose::ExtractType( nsString& str)
{
  nsString tStr;
  PRInt32 idx = str.FindChar( ';');
  if (idx != -1) {
    str.Left( tStr, idx);
    str = tStr;
  }
  str.Trim( kWhitespace);

  if ((str.CharAt( 0) == '"') && (str.Length() > 2)) {
    str.Mid( tStr, 1, str.Length() - 2);
    str = tStr;
    str.Trim( kWhitespace);
  }

  // if multipart then ignore it since no outlook message body is ever
  // valid multipart!
  if (str.Length() > 10) {
    str.Left( tStr, 10);
    if (tStr.LowerCaseEqualsLiteral("multipart/"))
      str.Truncate();
  }
}