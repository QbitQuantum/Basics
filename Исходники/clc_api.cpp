//  CodePageFromCharSet()
//
UINT CodePageFromCharSet(UINT uCharSet) // LOGFONT.lfCharSet; 
/*
ANSI_CHARSET
BALTIC_CHARSET
CHINESEBIG5_CHARSET
DEFAULT_CHARSET
EASTEUROPE_CHARSET
GB2312_CHARSET
*/
{
  CHARSETINFO ci;
  if (TranslateCharsetInfo((DWORD*)uCharSet,&ci,TCI_SRCCHARSET))
    return(ci.ciACP);
  else
    return(GetACP());
}