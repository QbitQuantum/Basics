// 保存数据到图像文件
// 2005.12.9
BOOL CMyDib::SaveToFile(LPCTSTR lpszPathName)
{
	DWORD dWord = 0;
    CFile file;
    //打开文件
    if (!file.Open(lpszPathName, CFile::modeCreate |
        CFile::modeReadWrite | CFile::shareExclusive))
    {
        return FALSE;
    }

    TRY
    {
        //保存为DIB图像
        dWord = Save(file);
        
        file.Close();
    }
    //保存失败
    CATCH (CException, eSave)
    {
        file.Abort();
        return FALSE;
    }