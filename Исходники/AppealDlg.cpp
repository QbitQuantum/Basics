//把录像文件按时间逆序，然后反应到控件上  yjj 090304
void CAppealDlg::ProcessRecordFile(const CString& strUserName)
{
    if (strUserName == "")
    {
        return;
    }
    GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(strUserName);
    GetDlgItem(IDC_EDIT_PHONE_NUM)->SetWindowText("");
    GetDlgItem(IDC_EDIT_APPEAL_EMAIL)->SetWindowText("");
    GetDlgItem(IDC_EDIT_APPEAL_CONTENT)->SetWindowText("");



    CString strPath = CBcfFile::GetAppPath(); //得到当前的目录

    strPath += "log";
    strPath += "\\";

    CString gamenamefile = strPath + "gamename.bcf";
    DWORD dwHandle = cfgOpenFile(gamenamefile);

    if(dwHandle < 0x10)
        return;

    strPath += "log_";
    strPath += strUserName;
    strPath += "\\";

    CTime tCurTime = CTime::GetCurrentTime();
    CString direct = tCurTime.Format("%Y-%m-%d");

    CString strCurDir = strPath + direct;

    strCurDir += "\\";
    CFileFind finder;
    strCurDir += _T("*.*");
    int iFindFileCount = 0;
    m_fileList.clear();

    //从当前，向前找6个目录
    for (int i=0; i<6; i++)
    {
        BOOL bWorking = finder.FindFile(strCurDir);
        while (bWorking)
        {
            bWorking = finder.FindNextFile();
            if (finder.IsDots())
                continue;




            //找到一个文件
            //CString sFileName = finder.GetFileName();
            //CString sFilePath = finder.GetFilePath();
            RecordFileStruct recordfile;

            recordfile.strWholeName = finder.GetFilePath(); //得到完整名字
            recordfile.strFileName = finder.GetFileName();     //得到文件名字

            //wushuqun 2009.5.20
            recordfile.strGamePath = finder.GetFilePath();

            //if (recordfile.strFileName.Find(".zxh") == -1)
            //{
            //	continue;
            //}
            CString strNameId = GetFileNameID(recordfile.strFileName);
            recordfile.strGameName = GetGameName(dwHandle,strNameId); //得到游戏名字

            if (recordfile.strGameName == "")
            {
                continue;
            }
            finder.GetCreationTime(recordfile.timeCreatTime);    //得到创建文件时间
            recordfile.strGameTime = recordfile.timeCreatTime.Format("%m-%d %H:%M ");
            m_fileList.push_back(recordfile);  //把文件信息加入链表
            iFindFileCount ++;
        }
        //找完整个目录
        if (iFindFileCount >= 20)
        {
            break;
        }
        //
        CTimeSpan ts(1,   0,   0,   0);
        tCurTime -= ts;
        direct = tCurTime.Format("%Y-%m-%d");
        strCurDir = strPath + direct;

        strCurDir += "\\";
        strCurDir +=_T("*.*");
        //找上一天的目录
    }

    //按升序排列



    m_fileList.sort();
    m_FileListCtrl.DeleteAllItems();


    list<RecordFileStruct>::iterator iter = m_fileList.begin();
    int iCount = 0;
    for (; iter != m_fileList.end(); iter++)
    {
        RecordFileStruct recordfile = *iter;

        //RecordFileStruct* pRecordFile = iter;
        //iter ++;
        //CString strListNmae;
        //strListNmae.Format("%s  %s",recordfile.strGameName,recordfile.strGameTime);

        int iItem = m_FileListCtrl.InsertItem(m_FileListCtrl.GetItemCount(),recordfile.strGameName);
        m_FileListCtrl.SetItemText(iItem,1,recordfile.strGameTime);

        //wushuqun 2009.5.20
        //新增加一列“文件名称"
        m_FileListCtrl.SetItemText(iItem,2,recordfile.strFileName);

        //m_FileListCtrl.SetItemData(iItem,(DWORD)&iter);
        iCount++;
        //m_ListBox.AddString(strListNmae);
        //m_ListBox.InsertString(iCount++,strListNmae);
        if (iCount == 20)
        {
            break;
        }
    }









    cfgClose(dwHandle);
    finder.Close();



}