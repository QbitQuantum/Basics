void CCommonSeqReference::OutputDescCommSeq( const char* szFileName )
{
    const char* szFileRealName = strrchr(szFileName, '/');
    szFileRealName++;
    m_strCommonFileName = szFileRealName;
    char charEnter[4] = {0x0D,0x00,0x0A,0x00};
    char charTab[2] = {0x09,0x00};
    CreateFileDirectory(szFileName);
    ofstream ofsCommSeq(szFileName, ios_base::binary | ios_base::out);

    char headArray[2];
    headArray[0] = uint8(15*16+15);
    headArray[1] = uint8(15*16+14);
    ofsCommSeq.write(headArray, 2);

    vector<wstring> vecColName;
    vecColName.push_back(L"Index");
    vecColName.push_back(L"CommonSequence");

    ofsCommSeq.write((const char*)vecColName[0].c_str(), vecColName[0].length()*2);
    ofsCommSeq.write(charTab, 2);
    ofsCommSeq.write((const char*)vecColName[1].c_str(), vecColName[1].length()*2);
    ofsCommSeq.write(charEnter, 4);

    typedef hash_map<uint32, string>::iterator IterHmapUS;
    uint32 uCommSeqIndex;
    wchar_t szCommonIndex[20];
    wstring wstrCommSeq;
    for (IterHmapUS iter=s_hmapCommSeq.begin(); iter!=s_hmapCommSeq.end(); ++iter)
    {
        uCommSeqIndex = iter->first;
        _ui64tow(uCommSeqIndex, szCommonIndex, 10);
        ofsCommSeq.write((char*)szCommonIndex, wcslen(szCommonIndex)*2);
        ofsCommSeq.write(charTab, 2);
        wstrCommSeq = gbk_to_utf16(iter->second);
        ofsCommSeq.write((const char*)wstrCommSeq.c_str(), wstrCommSeq.length()*2);
        ofsCommSeq.write(charEnter, 4);
    }
    ofsCommSeq.close();
}