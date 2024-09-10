int __GetLCID(const char* lang, const char* ctry, LCID* lcid) {
  __FindFlag=0;
  __FndLang=lang;
  __FndCtry=ctry;
  EnumSystemLocalesA(EnumLocalesProcA, LCID_INSTALLED);

  if(__FindFlag==0) return -1;

  *lcid=__FndLCID;
  return 0;
}