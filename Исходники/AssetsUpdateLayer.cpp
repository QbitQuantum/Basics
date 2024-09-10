void AssetsUpdateLayer::createDownloadedDir()
{
    m_pathToSave = CCFileUtils::sharedFileUtils()->getWritablePath();
    m_pathToSave += "loaddir/";
    CCLOG("writable path[%s]", m_pathToSave.c_str());
    getAssetsManager()->setStoragePath(m_pathToSave.c_str());

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *pDir = NULL;

    pDir = opendir (m_pathToSave.c_str());
    if (! pDir)
    {
        mkdir(m_pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }
#else
    if ((GetFileAttributesA(m_pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
    {
        CreateDirectoryA(m_pathToSave.c_str(), 0);
    }
#endif
}