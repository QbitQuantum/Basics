XCONTRACT_CALL(void) xContract_violationReport( char const*                 file
                                            ,   unsigned                    line
                                            ,   char const*                 function
                                            ,   char const*                 expression
                                            ,   char const*                 message
                                            ,   char const*                 qualifier
                                            ,   xContract_violation_type_t  type
                                            ,   int                         level)
{
    /* 1. formulate the termination messages */

    char        sz[2001];
    size_t      type_len = 0;
    char const* type_str = xcontract_lookup_violation_type_string_(type, &type_len);
    int         cch;

    STLSOFT_SUPPRESS_UNUSED(level);

#ifdef XCONTRACT_USING_SAFE_STR_FUNCTIONS
    cch = sprintf_s(
#else /* ? XCONTRACT_USING_SAFE_STR_FUNCTIONS */
    cch = snprintf(
#endif /* XCONTRACT_USING_SAFE_STR_FUNCTIONS */
                    &sz[0]
                ,   STLSOFT_NUM_ELEMENTS(sz) - 2
                ,   "Contract violation: %s at %s(%d)%s%s: %s%s%s%s%s"
                /* %s */
                ,   type_str
                /* %s(%d)%s%s */
                ,   file
                ,   line
                ,   (NULL == function) ? "" : " in function "
                ,   stlsoft_ns_qual(c_str_ptr_a)(function)
                /* %s%s%s */
                ,   message
                ,   (NULL == expression) ? "" : " - failed expression: "
                ,   stlsoft_ns_qual(c_str_ptr_a)(expression)
                /* %s%s */
                ,   (NULL == qualifier || '\0' == 0[qualifier]) ? "" : ": "
                ,   stlsoft_ns_qual(c_str_ptr_a)(qualifier)
                );

    if(cch < 0)
    {
        cch = STLSOFT_NUM_ELEMENTS(sz) - 2;
    }

    sz[cch]     = '\n';
    sz[cch + 1] = '\0';

    /* 2. write out the termination messages */

    fputs(sz, stderr);

#ifdef XCONTRACT_USE_WIN_OUTPUTDEBUGSTRING
    OutputDebugStringA(sz);
#endif /* XCONTRACT_USE_WIN_OUTPUTDEBUGSTRING */

    sz[cch] = '\0';

#ifdef XCONTRACT_USE_WIN_EVENTLOG
    {
        HANDLE hEvLog = RegisterEventSource(NULL, "xContract");

        if(NULL != hEvLog)
        {
            WORD        wType       =   EVENTLOG_ERROR_TYPE;
            WORD        category    =   XCONTRACT_WIN_EVENTLOG_CATEGORY;
            DWORD       eventId     =   XCONTRACT_WIN_EVENTLOG_EVENTID;
            PSID        lpUserSid   =   NULL;
            WORD        wNumStrings =   1;
            LPCSTR      entry       =   &sz[0];
            LPCSTR*     lpStrings   =   &entry;
            DWORD       dwDataSize  =   0;
            LPVOID      lpRawData   =   NULL;

            ReportEventA(   hEvLog
                        ,   wType
                        ,   category
                        ,   eventId
                        ,   lpUserSid
                        ,   wNumStrings
                        ,   dwDataSize
                        ,   lpStrings
                        ,   lpRawData);

            DeregisterEventSource(hEvLog);
        }
    }
#endif /* XCONTRACT_USE_WIN_EVENTLOG */

#ifdef XCONTRACT_USE_SYSLOG
    syslog(XCONTRACT_SYSLOG_FLAGS, "%s", sz);
#endif /* XCONTRACT_USE_SYSLOG */
}