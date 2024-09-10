int main(int argc, char *argv[])
{
    char hostName[200] = DEFAULT_HOSTNAME;
    int port = DEFAULT_RESMGR_TPM_PORT;

    setbuf(stdout, NULL);
    setvbuf (stdout, NULL, _IONBF, BUFSIZ);

    int opt = -1;
    const char *optstring = "hvk:c:P:l:g:o:p:d:";
    static struct option long_options[] = {
        {"help",0,NULL,'h'},
        {"version",0,NULL,'v'},
        {"akHandle",1,NULL,'k'},
        {"akContext",1,NULL,'c'},
        {"akPassword",1,NULL,'P'},  //add ak auth
        {"idList",1,NULL,'l'},
        {"algorithm",1,NULL,'g'},
        {"outFile",1,NULL,'o'},
        {"port",1,NULL,'p'},
        {"debugLevel",1,NULL,'d'},
        {0,0,0,0}
    };

    char *contextFilePath = NULL;
    TPM_HANDLE akHandle;
    TPMI_ALG_HASH algorithmId;
    PCR_LIST pcrList;

    int returnVal = 0;
    int flagCnt = 0;
    int h_flag = 0,
        v_flag = 0,
        k_flag = 0,
        c_flag = 0,
        P_flag = 0,
        l_flag = 0,
        g_flag = 0,
        o_flag = 0;

    if(argc == 1)
    {
        showHelp(argv[0]);
        return 0;
    }
    while((opt = getopt_long(argc,argv,optstring,long_options,NULL)) != -1)
    {
        switch(opt)
        {
        case 'h':
            h_flag = 1;
            break;
        case 'v':
            v_flag = 1;
            break;
        case 'k':
            if(getSizeUint32Hex(optarg,&akHandle) != 0)
            {
                showArgError(optarg, argv[0]);
                returnVal = -1;
                break;
            }
            k_flag = 1;
            break;
        case 'c':
            contextFilePath = optarg;
            if(contextFilePath == NULL || contextFilePath[0] == '\0')
            {
                returnVal = -2;
                break;
            }
            printf("contextFile = %s\n", contextFilePath);
            c_flag = 1;
            break;

        case 'P':
            sessionData.hmac.t.size = sizeof(sessionData.hmac.t) - 2;
            if(str2ByteStructure(optarg,&sessionData.hmac.t.size,sessionData.hmac.t.buffer) != 0)
            {
                returnVal = -3;
                break;
            }
            P_flag = 1;
            break;
        case 'l':
            if(parseList(optarg, &pcrList) != 0)
            {
                returnVal = -4;
                break;
            }
            l_flag = 1;
            break;
        case 'g':
            if(getSizeUint16Hex(optarg,&algorithmId) != 0)
            {
                showArgError(optarg, argv[0]);
                returnVal = -5;
                break;
            }
            g_flag = 1;
            break;
        case 'o':
            safeStrNCpy(outFilePath, optarg, sizeof(outFilePath));
            if(checkOutFile(outFilePath) != 0)
            {
                returnVal = -6;
                break;
            }
            o_flag = 1;
            break;
        case 'p':
            if( getPort(optarg, &port) )
            {
                printf("Incorrect port number.\n");
                returnVal = -7;
            }
            break;
        case 'd':
            if( getDebugLevel(optarg, &debugLevel) )
            {
                printf("Incorrect debug level.\n");
                returnVal = -8;
            }
            break;
       case ':':
            //              printf("Argument %c needs a value!\n",optopt);
            returnVal = -9;
            break;
        case '?':
            //              printf("Unknown Argument: %c\n",optopt);
            returnVal = -10;
            break;
            //default:
            //  break;
        }
        if(returnVal)
            break;
    };

    if(returnVal != 0)
        return returnVal;

    flagCnt = h_flag + v_flag + k_flag + c_flag + l_flag + g_flag + o_flag;
    if(flagCnt == 1)
    {
        if(h_flag == 1)
            showHelp(argv[0]);
        else if(v_flag == 1)
            showVersion(argv[0]);
        else
        {
            showArgMismatch(argv[0]);
            return -11;
        }
    }
    else if(flagCnt == 4 && ((k_flag || c_flag) && l_flag && g_flag && o_flag))
    {
        if(P_flag == 0)
            sessionData.hmac.t.size = 0;

        prepareTest(hostName, port, debugLevel);

        if(c_flag)
            returnVal = loadTpmContextFromFile(sysContext, &akHandle, contextFilePath);
        if(returnVal == TPM_RC_SUCCESS)
            returnVal = quote(akHandle, pcrList, algorithmId);

        finishTest();

        if(returnVal)
            return -12;
    }
    else
    {
        showArgMismatch(argv[0]);
        return -13;
    }

    return 0;
}