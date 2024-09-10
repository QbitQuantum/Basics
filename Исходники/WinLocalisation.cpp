HFONT WinLocalisation::GetCodePageFont(UINT CodePage, LONG Height) {
  CHARSETINFO CharsetInfo;
  UINT MyCharset;
  if(TranslateCharsetInfo((DWORD FAR *) CodePage, &CharsetInfo, TCI_SRCCODEPAGE)) {
    MyCharset = CharsetInfo.ciCharset;
  }
  else
    MyCharset = DEFAULT_CHARSET;

  return CreateFont(Height, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, MyCharset,       // Apart from the character set and size I don't care about the font.
                    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, NULL);
}