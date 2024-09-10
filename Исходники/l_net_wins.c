//===========================================================================
//
// Parameter:                -
// Returns:                    -
// Changes Globals:        -
//===========================================================================
int WINS_Init(void)
{
    int        i;
    struct hostent *local;
    char    buff[MAXHOSTNAMELEN];
    struct sockaddr_s addr;
    char    *p;
    int        r;
    WORD    wVersionRequested; 

    wVersionRequested = MAKEWORD(1, 1);

    r = WSAStartup (wVersionRequested, &winsockdata);

    if (r)
    {
        WinPrint("Winsock initialization failed.\n");
        return -1;
    }

    /*
    i = COM_CheckParm ("-udpport");
    if (i == 0)*/
        net_hostport = DEFAULTnet_hostport;
    /*
    else if (i < com_argc-1)
        net_hostport = Q_atoi (com_argv[i+1]);
    else
        Sys_Error ("WINS_Init: you must specify a number after -udpport");
    */

    // determine my name & address
    gethostname(buff, MAXHOSTNAMELEN);
    local = gethostbyname(buff);
    myAddr = *(int *)local->h_addr_list[0];

    // if the quake hostname isn't set, set it to the machine name
//    if (Q_strcmp(hostname.string, "UNNAMED") == 0)
    {
        // see if it's a text IP address (well, close enough)
        for (p = buff; *p; p++)
            if ((*p < '0' || *p > '9') && *p != '.')
                break;

        // if it is a real name, strip off the domain; we only want the host
        if (*p)
        {
            for (i = 0; i < 15; i++)
                if (buff[i] == '.')
                    break;
            buff[i] = 0;
        }
//        Cvar_Set ("hostname", buff);
    }

    if ((net_controlsocket = WINS_OpenSocket (0)) == -1)
        WinError("WINS_Init: Unable to open control socket\n");

    ((struct sockaddr_in *)&broadcastaddr)->sin_family = AF_INET;
    ((struct sockaddr_in *)&broadcastaddr)->sin_addr.s_addr = INADDR_BROADCAST;
    ((struct sockaddr_in *)&broadcastaddr)->sin_port = htons((u_short)net_hostport);

    WINS_GetSocketAddr (net_controlsocket, &addr);
    strcpy(my_tcpip_address,  WINS_AddrToString (&addr));
    p = strrchr (my_tcpip_address, ':');
    if (p) *p = 0;
    WinPrint("Winsock Initialized\n");

    return net_controlsocket;
} //end of the function WINS_Init