/** Message 조회
 *
 * @param szId target device id
 * @param nMessageType 0 이라면 Message 전체
 * @param pWrapper 응답을 전해 줄 IF4Wrapper
 */
BOOL CMessageHelper::Select(const char *szId, BYTE nMessageType, IF4Wrapper *pWrapper)
{
    if(!CheckDB()) return FALSE;

    CppSQLite3Query result;
    char timeString[32];
    TIMESTAMP issueTime;
    unsigned char * pPayload;
    int idx=0, nPayloadLen;
    int year, mon, day, hour, min, sec;

    if(pWrapper == NULL) return FALSE;

    if(!Open()) return FALSE;
    try
    {
        CppSQLite3Statement stmt;
        
        if (nMessageType > 0) {
            stmt = m_SqliteHelper.compileStatement(
                "SELECT "
                "messageId, issueTime, userData, payload, "
                "duration, errorHandler, preHandler, postHandler "
                "FROM MessageTbl "
                "WHERE targetId = ? and messageType = ? ; ");

            stmt.bind(1, szId);
            stmt.bind(2, nMessageType);
        } else {
            stmt = m_SqliteHelper.compileStatement(
                "SELECT "
                "messageId, issueTime, userData, payload, "
                "duration, errorHandler, preHandler, postHandler "
                "FROM MessageTbl "
                "WHERE targetId = ? ; ");

            stmt.bind(1, szId);
        }

        result = stmt.execQuery();
        while(!result.eof())
        {
            memset(timeString, 0, sizeof(timeString));
            memset(&issueTime, 0, sizeof(TIMESTAMP));
            pPayload = NULL; nPayloadLen = 0; idx = 0;

            IF4API_AddResultNumber(pWrapper, "1.6", VARSMI_UINT, result.getIntField(idx));  idx++;
            strcat(timeString, result.getStringField(idx));                                 idx++;
            sscanf(timeString,"%04d-%02d-%02d %02d:%02d:%02d",
                    &year, &mon, &day, &hour, &min, &sec);
            issueTime.year = year; issueTime.mon = mon;
            issueTime.day = day; issueTime.hour = hour;
            issueTime.min = min; issueTime.sec = sec;
            /*
            XDEBUG(" %04d/%02d/%02d %02d:%02d:%02d\r\n",
                    issueTime.year, issueTime.mon, issueTime.day, issueTime.hour, issueTime.min, issueTime.sec);
                    */
	        IF4API_AddResultFormat(pWrapper, "1.16", VARSMI_TIMESTAMP, &issueTime, sizeof(TIMESTAMP));
            IF4API_AddResultNumber(pWrapper, "1.6", VARSMI_UINT, result.getIntField(idx));  idx++;
            pPayload = const_cast<unsigned char *>(result.getBlobField(idx, nPayloadLen));  idx++;
	        IF4API_AddResultFormat(pWrapper, "1.12", VARSMI_STREAM, pPayload, nPayloadLen);

            result.nextRow();
        }
        stmt.finalize();
        Close();
    }
	catch ( CppSQLite3Exception& e )
	{
        Close();
		XDEBUG(ANSI_COLOR_RED "MessageTbl DB ERROR SELECT: %d %s\r\n" ANSI_NORMAL, e.errorCode(), e.errorMessage());
        return FALSE;
	}
    return TRUE;
}