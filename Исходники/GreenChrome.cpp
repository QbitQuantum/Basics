void GreenChrome()
{
    // exe路径
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);

    // exe所在文件夹
    wchar_t exeFolder[MAX_PATH];
    wcscpy(exeFolder, exePath);
    PathRemoveFileSpecW(exeFolder);

    // 生成默认ini文件
    wchar_t iniPath[MAX_PATH];
    ReleaseIni(exeFolder, iniPath);

    // 读取配置
    ReadConfig(iniPath);

    // 启动单次功能
    bool first_run = OnceFeature(iniPath);

    // 自定义用户数据目录
    CustomUserData(iniPath);

    // 打造便携版chrome
    MakePortable(iniPath);

    // 给resources.pak打补丁
    PatchResourcesPak(iniPath);

    // 标签页，书签，地址栏增强
    TabBookmark();

    // 父进程不是Chrome，则需要启动追加参数功能
    wchar_t parentPath[MAX_PATH];
    if (GetParentPath(parentPath))
    {
        if (PathFileExistsW(parentPath) && _wcsicmp(parentPath, exePath) != 0)
        {
            CustomCommand(iniPath, exeFolder, exePath, first_run);
        }
    }
    else
    {
        DebugLog(L"GetParentPath failed");
    }
}