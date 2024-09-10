bool CPGSSubFile::Open(CString fn, CString name /*= _T("")*/, CString videoName /*= _T("")*/)
{
    bool bOpened = false;

    if (name.IsEmpty()) {
        m_name = Subtitle::GuessSubtitleName(fn, videoName);
    } else {
        m_name = name;
    }

    CFile f;
    if (f.Open(fn, CFile::modeRead | CFile::shareDenyWrite)) {
        WORD wSyncCode = 0;
        f.Read(&wSyncCode, sizeof(wSyncCode));
        wSyncCode = _byteswap_ushort(wSyncCode);
        if (wSyncCode == PGS_SYNC_CODE) {
            m_parsingThread = std::thread([this, fn] { ParseFile(fn); });
            bOpened = true;
        }
    }

    return bOpened;
}