/*******************************************************************************
*
*  函 数 名 : GetDebugPragramUDDPath
*  功能描述 : 取得od udd目录
*  参数列表 : pOutBuffer        --    取出buffer
*  说    明 : 
*  返回结果 : 如果成功返回TRUE，失败返回FALSE
*
*******************************************************************************/
BOOL GetDebugPragramUDDPath(char *pOutBuffer)
{
    NULLVALUE_CHECK(pOutBuffer, BackupUDD) ;
    char szOdPath[MAX_PATH] = {0} ;

    // 取得od路径
    if(0 == GetModuleFileNameA(NULL, szOdPath, MAX_PATH))
    {
        OutputDebugString(_T("GetDebugPragramUDDPath GetModuleFileNameA failed")) ;
        return FALSE ;
    }

    // 构造UDD路径
    // 处理中路径，去文件名
    PathRemoveFileSpecA(szOdPath) ;
    PathAppendA(szOdPath, "UDD") ;

    strcpy_s(pOutBuffer, MAX_PATH, szOdPath) ;
    return TRUE ;
}