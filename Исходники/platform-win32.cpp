std::string getLocale()
{
  TCHAR szBuff1[10], szBuff2[10]; 

  LCID lcid = GetUserDefaultLCID(); 

  GetLocaleInfo(lcid, LOCALE_SISO639LANGNAME, szBuff1, 10); 
  GetLocaleInfo(lcid, LOCALE_SISO3166CTRYNAME, szBuff2, 10); 

  strcat(szBuff1,"_");
  strcat(szBuff1,szBuff2);

  return szBuff1;
}