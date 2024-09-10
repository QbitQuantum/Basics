BOOL ATELogFile::AddRecord(const ATEStr& szRec)
{
    if(szRec.IsEmpty()) { return FALSE; }
    time_t t = time(NULL);
    WCHAR* pszTime = _wctime(&t);
    if(NULL == pszTime) { return FALSE; }
    ATEStr szTime = pszTime;
    *(szTime.GetTail() - 1) = 0;
    szTime.Refresh();

    m_file.Seek(0, SEEKPOS_END);
    BOOL bRet = m_file.Printf(L"%04d [%24s]\t%s\n", m_uRecCnt + 1, szTime.GetHead(), szRec.GetHead());
    if(!bRet) { return FALSE; }

    m_uRecCnt++;
    return TRUE;
}