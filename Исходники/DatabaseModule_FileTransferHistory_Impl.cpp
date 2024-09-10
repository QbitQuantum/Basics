BOOL DatabaseModule_Impl::sqlGetFileTransferHistory(OUT std::vector<TransferFileEntity>& fileList)
{
    try
    {
        CppSQLite3Statement stmt;
        stmt = m_pSqliteDB->compileStatement(getFileTransferHistoryBySIdSql.c_str());
        stmt.bind(1, 20);

        CppSQLite3Query query = stmt.execQuery();
        while (!query.eof())
        {
            TransferFileEntity fileInfo;
            fileInfo.sTaskID = query.getStringField(1);
            fileInfo.sFromID = query.getStringField(2);
            fileInfo.sFileName = query.getStringField(3);
            CString strSavePath = util::stringToCString(query.getStringField(7));
            fileInfo.setSaveFilePath(strSavePath);
            fileInfo.nFileSize = query.getIntField(8);
            fileInfo.time = query.getIntField(9);
            fileList.push_back(fileInfo);
            query.nextRow();
        }
    }
    catch (CppSQLite3Exception& sqliteException)
    {
#ifdef _DEBUG
        MessageBoxA(0, sqliteException.errorMessage(), "BD ERROR", MB_OK | MB_ICONHAND);
#endif
        CString csErrMsg = util::stringToCString(sqliteException.errorMessage(), CP_UTF8);
        LOG__(ERR, _T("db failed,error msg:%s"),
            csErrMsg);
        return FALSE;
    }
    catch (...)
    {
        return FALSE;
    }

    return TRUE;
}