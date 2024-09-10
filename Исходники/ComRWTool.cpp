//清空输入输出缓冲区
BOOL ComRWTool::ClearComBuffer()
{
    return PurgeComm(m_hComm ,PURGE_TXCLEAR|PURGE_RXCLEAR);
}