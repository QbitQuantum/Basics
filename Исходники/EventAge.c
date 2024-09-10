BOOL ShouldWriteRecord(DWORD dwWrittenTime)
{
    CHAR tmpbuff[9], tmpbuff2[9];
    struct tm* pTime;

    // get current date
    _strdate(tmpbuff);

    // convert UTC time to date format
    pTime = localtime(&dwWrittenTime);
    strftime(tmpbuff2, 9, "%m/%d/%y", pTime);

    // compare strings
    return((strcmp(tmpbuff, tmpbuff2) == 0)
           ? TRUE : FALSE);
}