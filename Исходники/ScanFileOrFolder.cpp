ScanFileOrFolder::ScanFileOrFolder(const Ultracopier::CopyMode &mode)
{
    moveTheWholeFolder  = true;
    stopped             = true;
    stopIt              = false;
    this->mode          = mode;
    folder_isolation    = QRegularExpression("^(.*/)?([^/]+)/$");
    setObjectName("ScanFileOrFolder");
    #ifdef Q_OS_WIN32
    QString userName;
    DWORD size=255;
    WCHAR * userNameW=new WCHAR[size];
    if(GetUserNameW(userNameW,&size))
    {
        userName=QString::fromWCharArray(userNameW,size-1);
        blackList << QFileInfo(QString("C:/Users/%1/AppData/Roaming/").arg(userName)).absoluteFilePath();
    }
    delete userNameW;
    #endif
}