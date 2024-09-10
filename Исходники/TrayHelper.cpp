//---------------------------------------------------------------------------------------
void GetLangTLA(TCHAR szLang[], int nSize)
{
   short nLangID = GetUserDefaultLangID();
   short nPrimaryLangID = PRIMARYLANGID(nLangID);

   if(nPrimaryLangID == LANG_ENGLISH)
      _tcsncpy_s(szLang, nSize, _T("ENU"), _TRUNCATE);
   else
      _tcsncpy_s(szLang, nSize, _T("ENU"), _TRUNCATE);
}