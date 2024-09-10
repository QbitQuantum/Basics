PARSE_RESULT STDAPICALLTYPE SvcParseCommandLine(char *pszCmdParam)
{
    char szCmdParam[MAX_PATH];
    lstrcpyA(szCmdParam, pszCmdParam);
    CharUpperA(szCmdParam);
    PARSE_RESULT result = PARSE_NORMAL;
    if (strstr(szCmdParam, "/REGSERVER") 
        || strstr(szCmdParam, "-REGSERVER"))
        result = PARSE_REGISTER_SERVER;
    else if (strstr(szCmdParam, "/UNREGSERVER") 
        || strstr(szCmdParam, "-UNREGSERVER"))
        result = PARSE_UNREGISTER_SERVER;
    else if (strstr(szCmdParam, "/AUTOMATION") 
        || strstr(szCmdParam, "-AUTOMATION"))
        result = PARSE_AUTOMATION;
    else if (strstr(szCmdParam, "/EMBEDDING") 
        || strstr(szCmdParam, "-EMBEDDING"))
        result = PARSE_EMBEDDING;
    return result;
}