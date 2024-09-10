bool InsertDate(char * def, char * pBuf, size_t & index,
                size_t & filelength, size_t maxlength,
                apr_time_t date_svn)
{
    // Search for first occurrence of def in the buffer, starting at index.
    if (!FindPlaceholder(def, pBuf, index, filelength))
    {
        // No more matches found.
        return false;
    }
    // Format the text to insert at the placeholder
    __time64_t ttime;
    if (date_svn == USE_TIME_NOW)
        _time64(&ttime);
    else
        ttime = date_svn/1000000L;

    struct tm newtime;
    if (strstr(def, "UTC"))
    {
        if (_gmtime64_s(&newtime, &ttime))
            return false;
    }
    else
    {
        if (_localtime64_s(&newtime, &ttime))
            return false;
    }
    char destbuf[1024] = { 0 };
    char * pBuild = pBuf + index;
    ptrdiff_t Expansion;
    if ((strcmp(def,DATEWFMTDEF) == 0) || (strcmp(def,NOWWFMTDEF) == 0) || (strcmp(def,LOCKWFMTDEF) == 0) ||
        (strcmp(def,DATEWFMTDEFUTC) == 0) || (strcmp(def,NOWWFMTDEFUTC) == 0) || (strcmp(def,LOCKWFMTDEFUTC) == 0))
    {
        // Format the date/time according to the supplied strftime format string
        char format[1024] = { 0 };
        char * pStart = pBuf + index + strlen(def);
        char * pEnd = pStart;

        while (*pEnd != '$')
        {
            pEnd++;
            if (pEnd - pBuf >= (__int64)filelength)
                return false;   // No terminator - malformed so give up.
        }
        if ((pEnd - pStart) > 1024)
        {
            return false; // Format specifier too big
        }
        SecureZeroMemory(format, sizeof(format));
        memcpy(format,pStart,pEnd - pStart);

        // to avoid wcsftime aborting if the user specified an invalid time format,
        // we set a custom invalid parameter handler that does nothing at all:
        // that makes wcsftime do nothing and set errno to EINVAL.
        // we restore the invalid parameter handler right after
        _invalid_parameter_handler oldHandler = _set_invalid_parameter_handler(_invalid_parameter_donothing);

        if (strftime(destbuf,1024,format,&newtime) == 0)
        {
            if (errno == EINVAL)
                strcpy_s(destbuf, "Invalid Time Format Specified");
        }
        _set_invalid_parameter_handler(oldHandler);
        Expansion = strlen(destbuf) - (strlen(def) + pEnd - pStart + 1);
    }
    else
    {
        // Format the date/time in international format as yyyy/mm/dd hh:mm:ss
        sprintf_s(destbuf, "%04d/%02d/%02d %02d:%02d:%02d",
            newtime.tm_year + 1900,
            newtime.tm_mon + 1,
            newtime.tm_mday,
            newtime.tm_hour,
            newtime.tm_min,
            newtime.tm_sec);

        Expansion = strlen(destbuf) - strlen(def);
    }
    // Replace the def string with the actual commit date
    if (Expansion < 0)
    {
        memmove(pBuild, pBuild - Expansion, filelength - ((pBuild - Expansion) - pBuf));
    }
    else if (Expansion > 0)
    {
        // Check for buffer overflow
        if (maxlength < Expansion + filelength) return false;
        memmove(pBuild + Expansion, pBuild, filelength - (pBuild - pBuf));
    }
    memmove(pBuild, destbuf, strlen(destbuf));
    filelength += Expansion;
    return true;
}