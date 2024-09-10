int WINAPI _export Start(const struct PluginStartupInfo *FarInfo,const struct DialogPluginStartupInfo *DialogInfo)
{
    ::FarInfo=*FarInfo;
    FSF=*FarInfo->FSF;
    ::DialogInfo=*DialogInfo;
    FSF.sprintf(PluginRootKey,"%s\\BCopy",::DialogInfo.RootKey);
    if(!ShowInfoMenu)
    {
        HMODULE m=GetModuleHandle("bcopy.dll");
        ShowInfoMenu=m?((ShowInfoMenuProc)GetProcAddress(m,"ShowInfoMenu")):NULL;
    }
    return 0;
}