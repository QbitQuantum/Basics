QString PathHelper::getLocalDesktopPath()
{
    //
    // !!! QDesktopServices::storageLocation could be used for this as well
    //

    QString localDesktopPath = "";

#ifdef Q_WS_WIN
    // SHGetFolderPathW: (http://msdn.microsoft.com/en-us/library/bb762181(v=vs.85).aspx)
    // minimum windows version: 2000, XP
    WCHAR szPath[MAX_PATH];
    if(SUCCEEDED(SHGetFolderPathW(NULL,
                                 CSIDL_DESKTOP|CSIDL_FLAG_CREATE,
                                 NULL,
                                 0,
                                 szPath)))
    {
        localDesktopPath = QString::fromWCharArray(szPath);
    }

    // SHGetKnownFolderPath: "This function replaces SHGetFolderPath. That older function is now simply a wrapper for SHGetKnownFolderPath."
    // from Windows Vista the desired way is: SHGetKnownFolderPath (http://msdn.microsoft.com/en-us/library/bb762188(v=vs.85).aspx)
    //  BUT SHGetKnownFolderPath requires Vista as minimum OS !!
#endif

#ifdef Q_WS_MAC
    localDesktopPath = "~/Desktop";
#endif

    return localDesktopPath;
}