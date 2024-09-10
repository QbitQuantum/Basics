int	ProcessErrorInfo(int new_sock)
{
    ERRORINFO_T	ErrorInfo[MAX_RETURN_NUM];
    PRODUCTID_T	ProductID;
    int	ErrorCount = 0;
    int	ErrorCode = 0;

    memset(ErrorInfo, 0, sizeof(ERRORINFO_T) * MAX_RETURN_NUM);

    if((ErrorCode = ReadProductID(&ProductID, new_sock)) != NO_ERROR)	{
        printLog(HEAD, "ERR: read error! ErroCode(%d)\n", ErrorCode) ;
        return	ErrorCode;
    }

    ErrorCode = GetErrorInfo(ProductID, &ErrorCount, ErrorInfo) ;
    printLog(HEAD, "work_errorInfo_get(): ret(%d) count(%d)\n", ErrorCode, ErrorCount) ;

    ErrorCode = WriteErrorInfo(ErrorInfo, ErrorCode, ErrorCount, new_sock);

    return	ErrorCode;
}