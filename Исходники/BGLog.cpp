CBGLog::CBGLog(DWORD dwFileNumber)
{
    const std::string strLogName = "BGLog" + std::to_string(dwFileNumber) + ".txt";
    std::string strCurrentDir;
    GetCurrentPath(strCurrentDir);

    m_stLogInfo.strFilePath = strCurrentDir + "\\" + strLogName;
    m_stLogInfo.pFile = _fsopen(m_stLogInfo.strFilePath.c_str(), "a+", _SH_DENYNO);
}