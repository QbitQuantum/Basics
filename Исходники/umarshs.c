/* main:  register the interface, start listening for clients */
void __cdecl main(int argc, char * argv[])
{
    RPC_STATUS status;
    unsigned char * pszProtocolSequence = "ncacn_ip_tcp";
    unsigned char * pszSecurity         = NULL;
    unsigned char * pszEndpoint         = "8765";
    unsigned char * pszSpn              = NULL;	
    unsigned int    cMinCalls           = 1;
    unsigned int    cMaxCalls           = 20;
    unsigned int    fDontWait           = FALSE;

    int i;

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
	  /* case 'i':
		if(!_stricmp(argv[++i],"No_Authenticate"))
			ifFlag = RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH;
		break;*/

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

    /* User did not specify spn, construct one. */
    if (pszSpn == NULL) {
        MakeSpn(&pszSpn);
    }

    /* Using Negotiate as security provider */
    status = RpcServerRegisterAuthInfo(pszSpn,
                                       RPC_C_AUTHN_GSS_NEGOTIATE,
                                       NULL,
                                       NULL);
	
    printf_s("RpcServerRegisterAuthInfo returned 0x%x\n", status);
    if (status) {
        exit(status);
    }	

    status = RpcServerRegisterIfEx(umarsh_ServerIfHandle,
		                           NULL,
		                           NULL,
		                           0,
		                           RPC_C_LISTEN_MAX_CALLS_DEFAULT,
		                           NULL );

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

}  // end main()