int WINAPI _export Start(const struct PluginStartupInfo *FarInfo,const struct AHPluginStartupInfo *AHInfo)
{
  Info=*FarInfo;
  FSF=*FarInfo->FSF;
  ::AHInfo=*AHInfo;
  FSF.sprintf(PluginRootKey,"%s\\%s",AHInfo->RootKey,"MS-Help2");
  GetRegKey("PathToViewer",PathToViewer,"H2Viewer.exe",sizeof(PathToViewer));
  GetRegKey("OpenContents",OpenContents,"/appid \"%f\" /helpcol \"%f\"",sizeof(OpenContents));
  GetRegKey("KeywordSearch",KeywordSearch,"/appid \"%f\" /helpcol \"%f\" /index \"%k\"",sizeof(KeywordSearch));
  return 0;
}