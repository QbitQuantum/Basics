err_t CreateUrlPart(nodecontext *Context, tchar_t *Out, size_t OutLen, const tchar_t *URL, filepos_t Offset, size_t Length, const tchar_t *Mime)
{
    datetime_t FileDate;
    if (!URL || !URL[0])
        return ERR_INVALID_DATA;

    stprintf_s(Out,OutLen,T("urlpart://%s"),URL);
    tcsreplace(Out,OutLen,URLPART_SEPARATOR,URLPART_SEP_ESCAPE);
    tcscat_s(Out,OutLen,URLPART_SEPARATOR);
    if (Offset > 0)
        stcatprintf_s(Out,OutLen,T("ofs=%d#"),(int)Offset); // TODO: support 64 bits offset
    if (Length > 0)
        stcatprintf_s(Out,OutLen,T("len=%d#"),(int)Length);
    if (Mime)
        stcatprintf_s(Out,OutLen,T("mime=%s#"),Mime);
    FileDate = FileDateTime(Context,URL);
    if (FileDate != INVALID_DATETIME_T)
        stcatprintf_s(Out,OutLen,T("date=%d#"),(int)FileDate);
    return ERR_NONE;
}