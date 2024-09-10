char* iupdrvLocaleInfo(void)
{
  CPINFOEXA info;
  GetCPInfoExA(CP_ACP, 0, &info);
  return iupStrReturnStr(info.CodePageName);
}