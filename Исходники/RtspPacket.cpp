/**
* Description:  SetRangeField().    设置Range头域
* @param  [in]  ulStartTime         起始时间
* @param  [in]  bRelativeTime   是否为相对时间
* @param  [io]  strRange        设置后的字符串
* @return       long.   返回码
*/
long CRtspPacket::SetRangeField
(
    IN  unsigned long   ulStartTime,
    IN  BOOL            bRelativeTime,
    IO  string&         strRange
)const
{
    //开始时间转换为字符串，最大长度不会超过32字节
    char szStartTime[32] = {0};
    
    if (bRelativeTime)
    {
        (void)snprintf(szStartTime, sizeof(szStartTime) - 1, "%u-", ulStartTime);

        //Range使用npt相对时间
        strRange += "Range:npt=";
    }
    else
    {
        time_t tStartTime = ulStartTime;
        
        //localtime返回NULL的条件:  Before midnight, January 1, 1970.  After 03:14:07, January 19, 2038,
        struct tm _tm;
		memset(&_tm, 0, sizeof(tm));
		localtime_s(&_tm, &tStartTime);
        
        (void)snprintf(szStartTime, sizeof(szStartTime) - 1, 
                        "%04d%02d%02dT%02d%02d%02dZ-", 
                        _tm.tm_year + 1900, 
                        _tm.tm_mon + 1, 
                        _tm.tm_mday, 
                        _tm.tm_hour, 
                        _tm.tm_min, 
                        _tm.tm_sec);

        //Range使用clock绝对时间
        strRange += "Range:clock=";
    }
    
    strRange += szStartTime;
    strRange += RTSP::CRLF;

    return RTSP::RET_CODE_OK; 
}