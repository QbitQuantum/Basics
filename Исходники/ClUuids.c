/* main:  register the interface, start listening for clients */
void __cdecl main(int argc, char * argv[])
{
    RPC_STATUS status;
    UUID MgrTypeUuid, ClientUuid;
    unsigned char * pszProtocolSequence = "ncacn_ip_tcp";
    unsigned char * pszSecurity         = NULL;
    unsigned char * pszClientUuid       = NULL_UUID_STRING;
    unsigned char * pszMgrTypeUuid      = "11111111-1111-1111-1111-111111111111";
    unsigned char * pszEndpoint         = "8765";
    unsigned char * pszSpn              = NULL;	
    unsigned int    cMinCalls           = 1;
    unsigned int    cMaxCalls           = 20;
    unsigned int    fDontWait           = FALSE;
    int i;

    cluuid_SERVER_EPV epv2;    // the mgr_epv for the 2nd implementation

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                pszProtocolSequence = argv[++i];
                break;
            case 'e':
                pszEndpoint = argv[++i];
                break;
            case 'a':
                pszSpn = argv[++i];
                break;
            case 'm':
                cMaxCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'n':
                cMinCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'f':
                fDontWait = (unsigned int) atoi(argv[++i]);
                break;
            case '1':
                pszMgrTypeUuid = argv[++i];
                break;
            case '2':
                pszClientUuid = argv[++i];
                break;

          
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
            Usage(argv[0]);
    }

    status = RpcServerUseProtseqEp(pszProtocolSequence,
                                   cMaxCalls,
                                   pszEndpoint,
                                   pszSecurity);  // Security descriptor
    printf_s("RpcServerUseProtseqEp returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    status = UuidFromString(pszClientUuid, &ClientUuid);
    printf_s("UuidFromString returned 0x%x = %d\n", status, status);
    if (status) {
        exit(status);
    }

    status = UuidFromString(pszMgrTypeUuid, &MgrTypeUuid);
    printf_s("UuidFromString returned 0x%x = %d\n", status, status);
    if (status) {
        exit(status);
    }
    if (strcmp (pszMgrTypeUuid, NULL_UUID_STRING) == 0) {
        printf_s("Register object using non-null uuid %s\n", pszMgrTypeUuid);
        exit(1);
    }

    if (strcmp (pszClientUuid, NULL_UUID_STRING) == 0) {
        printf_s("Register object using non-null uuid %s\n", pszMgrTypeUuid);
        ClientUuid = MgrTypeUuid;
    }

    RpcObjectSetType(&ClientUuid, &MgrTypeUuid);  // associate type UUID with nil UUID
    printf_s("RpcObjectSetType returned 0x%x\n", status);
    if (status) {
        exit(status);
    }
	
    /* User did not specify spn, construct one. */
    if (pszSpn == NULL) {
        MakeSpn(&pszSpn);
    }

    /* Using Negotiate as security provider. */
    status = RpcServerRegisterAuthInfo(pszSpn,
                                       RPC_C_AUTHN_GSS_NEGOTIATE,
                                       NULL,
                                       NULL);
	
    printf_s("RpcServerRegisterAuthInfo returned 0x%x\n", status);
    if (status) {
        exit(status);
    }	

    status = RpcServerRegisterIfEx(cluuid_ServerIfHandle, NULL, NULL, 0, RPC_C_LISTEN_MAX_CALLS_DEFAULT, NULL );


    /* register the second manager epv and associate it with the
       specified uuid.  the second uuid must be non-null so that
       it will not conflict with the NULL uuid already registered
       for this interface
       */
    epv2.HelloProc = HelloProc2;
    epv2.Shutdown = Shutdown;
  

    status = RpcServerRegisterIfEx(cluuid_ServerIfHandle, &MgrTypeUuid,  &epv2, 0, RPC_C_LISTEN_MAX_CALLS_DEFAULT, NULL ); 

    printf_s("RpcServerRegisterIfEx returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf_s("Calling RpcServerListen\n");
    status = RpcServerListen(cMinCalls,
                             cMaxCalls,
                             fDontWait);
    printf_s("RpcServerListen returned: 0x%x\n", status);
    if (status) {
        exit(status);
    }

    if (fDontWait) {
        printf_s("Calling RpcMgmtWaitServerListen\n");
        status = RpcMgmtWaitServerListen();  //  wait operation
        printf_s("RpcMgmtWaitServerListen returned: 0x%x\n", status);
        if (status) {
            exit(status);
        }
    }

} // end main()