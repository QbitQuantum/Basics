int WINAPI _export Start(const struct PluginStartupInfo *FarInfo,const struct AHPluginStartupInfo *AHInfo)
{
  Info=*FarInfo;
  FSF=*FarInfo->FSF;
  ::AHInfo=*AHInfo;
  FSF.sprintf(PluginRootKey,"%s\\%s",AHInfo->RootKey,"Custom");
  GetRegKey("Modality",&Modality,0);
  Modality %= 2;
  GetRegKey("Visuality",&Visuality,0);
  Visuality %= 2;
  return 0;
}