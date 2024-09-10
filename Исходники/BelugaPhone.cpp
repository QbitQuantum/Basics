BOOL BelugaPhone::DialNumber( TCHAR	gszDefaultNum[])
{
    /* TCHAR	gszDefaultNum[] = TEXT("+1 (425) 882-8080");*/
    LPTSTR			gpszPhoneNum = gszDefaultNum;
    LONG lResult;
    lResult = tapiRequestMakeCall(gpszPhoneNum, NULL, NULL, NULL);
    return (0 == lResult);
}