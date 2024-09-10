int
not_an_API_LeashAFSGetToken(
    TICKETINFO * ticketinfo,
    TicketList** ticketList,
    char * kerberosPrincipal
    )
{
#ifdef NO_AFS
    return(0);
#else
    struct ktc_principal    aserver;
    struct ktc_principal    aclient;
    struct ktc_token        atoken;
    int                     EndMonth;
    int                     EndDay;
    int                     cellNum;
    int                     BreakAtEnd;
    char                    UserName[64];
    char                    CellName[64];
    char                    ServiceName[64];
    char                    InstanceName[64];
    char                    EndTime[16];
    char                    Buffer[256];
    char                    Months[12][4] = {"Jan\0", "Feb\0", "Mar\0", "Apr\0", "May\0", "Jun\0", "Jul\0", "Aug\0", "Sep\0", "Oct\0", "Nov\0", "Dec\0"};
    char                    TokenStatus[16];
    time_t                  CurrentTime;
    struct tm               *newtime;
    DWORD                   CurrentState;
    DWORD                   rc;
    char                    HostName[64];


    TicketList* list = NULL;
    if ( ticketinfo ) {
        ticketinfo->btickets = NO_TICKETS;
        ticketinfo->principal[0] = '\0';
    }
    if ( !kerberosPrincipal )
        kerberosPrincipal = "";

    if (!AfsAvailable || GetAfsStatus(&AfsOnLine) && !AfsOnLine)
        return(0);

    CurrentState = 0;
    memset(HostName, '\0', sizeof(HostName));
    gethostname(HostName, sizeof(HostName));
    if (GetServiceStatus(HostName, TRANSARCAFSDAEMON, &CurrentState) != NOERROR)
        return(0);
    if (CurrentState != SERVICE_RUNNING)
        return(0);

    BreakAtEnd = 0;
    cellNum = 0;
    while (1)
    {
        if (rc = ktc_ListTokens(cellNum, &cellNum, &aserver))
        {
            if (rc != KTC_NOENT)
                return(0);

            if (BreakAtEnd == 1)
                break;
        }
        BreakAtEnd = 1;
        memset(&atoken, '\0', sizeof(atoken));
        if (rc = ktc_GetToken(&aserver, &atoken, sizeof(atoken), &aclient))
        {
            if (rc == KTC_ERROR)
                return(0);

            continue;
        }

        if (!list)
        {
            list = (TicketList*) calloc(1, sizeof(TicketList));
            (*ticketList) = list;
        }
        else
        {
            list->next = (struct TicketList*) calloc(1, sizeof(TicketList));
            list = (TicketList*) list->next;
        }

        CurrentTime = time(NULL);

        newtime = localtime(&atoken.endTime);

        memset(UserName, '\0', sizeof(UserName));
        strcpy(UserName, aclient.name);

        memset(CellName, '\0', sizeof(CellName));
        strcpy(CellName, aclient.cell);

        memset(InstanceName, '\0', sizeof(InstanceName));
        strcpy(InstanceName, aclient.instance);

        memset(ServiceName, '\0', sizeof(ServiceName));
        strcpy(ServiceName, aserver.name);

        memset(TokenStatus, '\0', sizeof(TokenStatus));

        EndDay = newtime->tm_mday;

        EndMonth = newtime->tm_mon + 1;;

        sprintf(EndTime, "%02d:%02d:%02d", newtime->tm_hour, newtime->tm_min, newtime->tm_sec);

        sprintf(Buffer,"                          %s %02d %s      %s%s%s@%s  %s",
                Months[EndMonth - 1], EndDay, EndTime,
                UserName,
                InstanceName[0] ? "." : "",
                InstanceName,
                CellName,
                TokenStatus);

        list->theTicket = (char*) calloc(1, sizeof(Buffer));
        if (!list->theTicket)
        {
#ifdef USE_MESSAGE_BOX
            MessageBox(NULL, "Memory Error", "Error", MB_OK);
#endif /* USE_MESSAGE_BOX */
            return ENOMEM;
        }

        strcpy(list->theTicket, Buffer);
        list->name = strdup(aclient.name);
        list->inst = aclient.instance[0] ? strdup(aclient.instance) : NULL;
        list->realm = strdup(aclient.cell);
        list->encTypes = NULL;
        list->addrCount = 0;
        list->addrList = NULL;

        if ( ticketinfo ) {
            sprintf(Buffer,"%s@%s",UserName,CellName);
            if (!ticketinfo->principal[0] || !stricmp(Buffer,kerberosPrincipal)) {
                strcpy(ticketinfo->principal, Buffer);
                ticketinfo->issue_date = 0;
                ticketinfo->lifetime = atoken.endTime;
                ticketinfo->renew_till = 0;

                _tzset();
                if ( ticketinfo->lifetime - time(0) <= 0L )
                    ticketinfo->btickets = EXPD_TICKETS;
                else
                    ticketinfo->btickets = GOOD_TICKETS;
            }
        }
    }
    return(0);
#endif
}