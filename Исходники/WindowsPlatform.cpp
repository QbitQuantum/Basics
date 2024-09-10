void WindowsPlatform::syncFolderAdded(QString syncPath, QString syncName, QString syncID)
{
    if (syncPath.startsWith(QString::fromAscii("\\\\?\\")))
    {
        syncPath = syncPath.mid(4);
    }

    if (!syncPath.size())
    {
        return;
    }

    QDir syncDir(syncPath);
    if (!syncDir.exists())
    {
        return;
    }

    if (!Preferences::instance()->leftPaneIconsDisabled())
    {
        addSyncToLeftPane(syncPath, syncName, syncID);
    }

    DWORD dwVersion = GetVersion();
    DWORD dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    int iconIndex = (dwMajorVersion<6) ? 2 : 3;

    QString infoTip = QCoreApplication::translate("WindowsPlatform", "MEGA synced folder");
    SHFOLDERCUSTOMSETTINGS fcs = {0};
    fcs.dwSize = sizeof(SHFOLDERCUSTOMSETTINGS);
    fcs.dwMask = FCSM_ICONFILE | FCSM_INFOTIP;
    fcs.pszIconFile = (LPWSTR)MegaApplication::applicationFilePath().utf16();
    fcs.iIconIndex = iconIndex;
    fcs.pszInfoTip = (LPWSTR)infoTip.utf16();
    SHGetSetFolderCustomSettings(&fcs, (LPCWSTR)syncPath.utf16(), FCS_FORCEWRITE);

    WCHAR path[MAX_PATH];
    HRESULT res = SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path);
    if (res != S_OK)
    {
        return;
    }

    QString linksPath = QString::fromWCharArray(path);
    linksPath += QString::fromAscii("\\Links");
    QFileInfo info(linksPath);
    if (!info.isDir())
    {
        return;
    }

    QString linkPath = linksPath + QString::fromAscii("\\") + syncName + QString::fromAscii(".lnk");
    if (QFile(linkPath).exists())
    {
        return;
    }

    WCHAR wDescription[]=L"MEGAsync synchronized folder";
    linkPath = QDir::toNativeSeparators(linkPath);
    WCHAR *wLinkPath = (WCHAR *)linkPath.utf16();

    syncPath = QDir::toNativeSeparators(syncPath);
    WCHAR *wSyncPath = (WCHAR *)syncPath.utf16();

    QString exec = MegaApplication::applicationFilePath();
    exec = QDir::toNativeSeparators(exec);
    WCHAR *wExecPath = (WCHAR *)exec.utf16();
    res = CreateLink(wSyncPath, wLinkPath, wDescription, wExecPath);

    SHChangeNotify(SHCNE_CREATE, SHCNF_PATH | SHCNF_FLUSHNOWAIT, wLinkPath, NULL);

    WCHAR *wLinksPath = (WCHAR *)linksPath.utf16();
    SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_PATH | SHCNF_FLUSHNOWAIT, wLinksPath, NULL);
    SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATH | SHCNF_FLUSHNOWAIT, syncPath.utf16(), NULL);
}