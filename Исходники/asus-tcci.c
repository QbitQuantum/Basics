/** @main Application entry-point. */
int main(int argc, char* argv[])
{
    int c;
    strcpy(initcmd, DEF_CMD_INIT);
    while (true)
    {
        static struct option long_options[] =
        {
            {"adapter", required_argument, 0, 'a'},
            {"remote-adapter", required_argument, 0, 'b'},
            {"close", no_argument, 0, 'c'},
            {"blink-on-receive", no_argument, 0, 'k'},
            {"log-packets", no_argument, 0, 'p'},
            {"verbose", no_argument, 0, 'v'},
            {"version", no_argument, 0, 'V'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;
        c = getopt_long (argc, argv, "a:b:ckpvV?", long_options, &option_index);
        
        /* Detect the end of the options. */
        if (c == -1)
            break;
        switch (c) {
            case 'a':
                tc_eth_adapter = optarg;
                break;
            case 'b':
                tc_eth_remoteAdapter = optarg;
                break;
            case 'c':
                exitReason = 0;
                break;
            case 'p':
                dbg_logPackets = true;
                break;
            case 'v':
                dbg_debugOut = true;
                break;
            case 'k':
                dbg_blinkOnReceive = true;
                break;
            case 'V':
                printf("Asus-TCCI (TrendChip Command Interpreter), version %s, build %s\n", VERSION, VERSION_BUILD);
                printf(" by %s. Sources and updates: %s\n", AUTHOR, URL);
                return EC_NORMAL;
            case 'h':
                /* getopt_long already printed an error message. */
                printf("usage: %s -V|--version\n", argv[0]); 
                printf("or: %s [-a|--adapter=\"%s\"] [-b|--remote-adapter=\"%s\"] [-c|--close] [-p|--log-packets] [-v|--verbose] [-k|--blink-on-receive] [<%s>]\n", argv[0], tc_eth_adapter, tc_eth_remoteAdapter, initcmd);
                
                return EC_NORMAL;
            default:
                return 9;
        }
    }
    
    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
        initcmd[0] = '\0'; // Clear string
        while (optind < argc)
            strncat(initcmd, argv[optind++], sizeof(initcmd));
    }
    debugf("-- Starting...\n");
    // Initialize in-socket
    tc_eth_sockIn = socket(AF_INET, SOCK_DGRAM, 0);
    if (tc_eth_sockIn < 0)
    {
        errorf("-- E: Input socket init failed!\n");
        return EC_APIFAIL;
    }
	/*debugf("-- dbg_debugOut = %d, dbg_logPackets = %d, tc_eth_adapter = \"%s\", initcmd = \"%s\"\n",
	    dbg_debugOut, dbg_logPackets, tc_eth_adapter, initcmd);*/
	// Initialize adapter
	eth_adapterId = if_nametoindex(tc_eth_adapter);
    initAdapter(tc_eth_adapter);
    // Initialize out-socket
    tc_eth_sockOut = socket(AF_PACKET,SOCK_RAW, htons(ETH_P_ALL));
    if (tc_eth_sockOut < 0)
    {
        errorf("-- E: Output socket init failed!\n");
        return EC_APIFAIL;
    }
    // Acquired MACs
    debugf("Remote (TrendChip) MAC: ");
    printmac(debugf, tc_eth_remoteMac);
    debugf("\nLocal (terminal) MAC: ");
    printmac(debugf, tc_eth_localMac);
    // Initial command execution
    debugf("\n-- Phase 2 - Perform init-command (%s)\n", initcmd);
    if (!tc_exec(initcmd))
        return EC_NETFAIL;
    // Interactive shell
    char inbuff[TC_CMD_MAX_LEN];
    fd_set rfds;
    struct timeval tv;
    int retval;
    while(exitReason < 0) {
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 100000; //100ms
        retval = select(1, &rfds, NULL, NULL, &tv);
        if (retval == -1){
            perror("-- select(stdin)");
            return EC_APIFAIL;
        }
        else if (retval){   
            debugf("-- Gathering input... "); 
            char* cmd = fgets(inbuff, TC_CMD_MAX_LEN, stdin);
            if (cmd[strlen(cmd)-1] == '\n')
                cmd[strlen(cmd)-1] = '\0'; // Trim the trailing '\n' char.
            debugf("Got '%s'\n", cmd); 
            if (cmd[0] == '\0')
                {} // Do nothing on blank lines.
            else if (strcmp(cmd, "!q") == 0 || strcmp(cmd, "!quit") == 0)
                exitReason = EC_NORMAL;
            else if (strcmp(cmd, "!v") == 0 || strcmp(cmd, "!verbose") == 0)
                errorf("-- Verbose output is now %s.\n", (dbg_debugOut = !dbg_debugOut) ? "ON" : "OFF");
            else if (strcmp(cmd, "!p") == 0 || strcmp(cmd, "!logpackets") == 0)
                errorf("-- Packet logging is now %s.\n", (dbg_logPackets = !dbg_logPackets) ? "ON" : "OFF");
            else if (strcmp(cmd, "!k") == 0 || strcmp(cmd, "!blink") == 0)
                errorf("-- Blink-on-receive is now %s.\n", (dbg_blinkOnReceive = !dbg_blinkOnReceive) ? "ON" : "OFF");
            else if (strcmp(cmd, "!h") == 0 || strcmp(cmd, "!help") == 0)
                errorf("-- Valid client commands: \n--  ![blin]k, !h[elp], ![log]p[ackets], !q[uit], !v[erbose].\n"); 
            else if (cmd[0] == '!')
                errorf("-- Unrecognized client command. Please try \"!help\" if you aren't sure.\n"); 
            else if (!tc_exec(cmd))
                errorf("-- W: Command request fail!\n");
                //exitReason = EC_NETFAIL; // I/O error?
        }
        if (!tc_listen())
            exitReason = EC_NETFAIL;
    }
    if (tc_eth_sockIn) 
        close(tc_eth_sockIn);
    else
        debugf("-- W: Input socket already closed!");
    if (tc_eth_sockOut) 
        close(tc_eth_sockOut);
    else
        debugf("-- W: Output socket already closed!");
    debugf("-- Connection closed, reason = %d (-1).\n", exitReason);
    return exitReason-1;
}