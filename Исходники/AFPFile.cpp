bool CAFPFile::OpenForWrite(const CURL& url, bool bOverWrite)
{

    int ret = 0;
    m_fileSize = 0;
    m_fileOffset = 0;

    Close();
    CSingleLock lock(gAfpConnection);
    if (gAfpConnection.Connect(url) != CAfpConnection::AfpOk || !gAfpConnection.GetVolume())
        return false;

    // we can't open files like afp://file.f or afp://server/file.f
    // if a file matches the if below return false, it can't exist on a afp share.
    if (!IsValidFile(url.GetFileName()))
        return false;

    m_pAfpVol = gAfpConnection.GetVolume();

    std::string strPath = gAfpConnection.GetPath(url);

    if (bOverWrite)
    {
        CLog::Log(LOGWARNING, "FileAFP::OpenForWrite() called with overwriting enabled! - %s", strPath.c_str());
        ret = gAfpConnection.GetImpl()->afp_wrap_creat(m_pAfpVol, strPath.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    }

    ret = gAfpConnection.GetImpl()->afp_wrap_open(m_pAfpVol, strPath.c_str(), O_RDWR, &m_pFp);

    if (ret || m_pFp == NULL)
    {
        // write error to logfile
        CLog::Log(LOGERROR, "CAFPFile::Open: Unable to open file : '%s'\nunix_err:'%x' error : '%s'", strPath.c_str(), errno, strerror(errno));
        return false;
    }

    // We've successfully opened the file!
    return true;
}