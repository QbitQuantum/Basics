int main(int argc, char* argv[])
{
    char hostName[200] = DEFAULT_HOSTNAME;
    int port = DEFAULT_RESMGR_TPM_PORT; //DEFAULT_TPM_PORT;
    char *contextFilePath = NULL;
    char *keyContextFilePath = NULL;

    setbuf(stdout, NULL);
    setvbuf (stdout, NULL, _IONBF, BUFSIZ);

    int opt = -1;
    const char *optstring = "hvH:c:k:C:P:K:f:o:p:d:";
    struct option long_options[] = {
      {"help",0,NULL,'h'},
      {"version",0,NULL,'v'},
      {"handle",1,NULL,'H'},
      {"context",1,NULL,'c'},
      {"keyHandle",1,NULL,'k'},
      {"keyContext",1,NULL,'C'},
      {"Password",1,NULL,'P'},
      {"keyPassword",1,NULL,'K'},
      {"inFile",1,NULL,'f'},
      {"outFile",1,NULL,'o'},
      {"port",1,NULL,'p'},
      {"debugLevel",1,NULL,'d'},
      {0,0,0,0},
    };

    int returnVal = 0;
    int flagCnt = 0;
    int h_flag = 0,
        v_flag = 0,
        H_flag = 0,
        c_flag = 0,
        k_flag = 0,
        C_flag = 0,
        K_flag = 0,
        P_flag = 0,
        f_flag = 0,
        o_flag = 0;

    if(argc == 1)
    {
        showHelp(argv[0]);
        return 0;
    }

    cmdAuth.hmac.t.size = 0;
    cmdAuth2.hmac.t.size = 0;

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
        case 'H':
            if(getSizeUint32Hex(optarg,&activateHandle) != 0)
            {
                returnVal = -1;
                break;
            }
            H_flag = 1;
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
        case 'k':
            if(getSizeUint32Hex(optarg,&keyHandle) != 0)
            {
                returnVal = -3;
                break;
            }
            k_flag = 1;
            break;
        case 'C':
            keyContextFilePath = optarg;
            if(keyContextFilePath == NULL || keyContextFilePath[0] == '\0')
            {
                returnVal = -4;
                break;
            }
            printf("keyContextFile = %s\n", keyContextFilePath);
            C_flag = 1;
            break;
        case 'P':
            cmdAuth.hmac.t.size = sizeof(cmdAuth.hmac.t) - 2;
            if(str2ByteStructure(optarg,&cmdAuth.hmac.t.size,cmdAuth.hmac.t.buffer) != 0)
            {
                returnVal = -5;
                break;
            }
            P_flag = 1;
            break;
        case 'K':
            cmdAuth2.hmac.t.size = sizeof(cmdAuth2.hmac.t) - 2;
            if(str2ByteStructure(optarg,&cmdAuth2.hmac.t.size,cmdAuth2.hmac.t.buffer) != 0)
            {
                returnVal = -6;
                break;
            }
            K_flag = 1;
            break;
        case 'f':
            if(readCrtSecFromFile(optarg,&credentialBlob,&secret) != 0)
            {
                returnVal = -7;
                break;
            }
            f_flag = 1;
            break;
        case 'o':
            safeStrNCpy(outFilePath, optarg, sizeof(outFilePath));
#if 0
            if(checkOutFile(outFilePath) != 0)
            {
                returnVal = -1;
                break;
            }
#endif
            o_flag = 1;
            break;
        case 'p':
            if( getPort(optarg, &port) )
            {
                printf("Incorrect port number.\n");
                returnVal = -8;
            }
            break;
        case 'd':
            if( getDebugLevel(optarg, &debugLevel) )
            {
                printf("Incorrect debug level.\n");
                returnVal = -9;
            }
            break;
        case ':':
//              printf("Argument %c needs a value!\n",optopt);
            returnVal = -10;
            break;
        case '?':
//              printf("Unknown Argument: %c\n",optopt);
            returnVal = -11;
            break;
        //default:
        //  break;
        }
        if(returnVal)
            break;
    };

    if(returnVal != 0)
        return returnVal;
    flagCnt = h_flag + v_flag + H_flag + c_flag + k_flag + C_flag + f_flag + o_flag;

    if(flagCnt == 1)
    {
        if(h_flag == 1)
            showHelp(argv[0]);
        else if(v_flag == 1)
            showVersion(argv[0]);
        else
        {
            showArgMismatch(argv[0]);
            return -12;
        }
    }
    else if((flagCnt == 4) && (H_flag == 1 || c_flag == 1) && (k_flag == 1 || C_flag == 1) && (f_flag == 1) && (o_flag == 1))
    {
        prepareTest(hostName, port, debugLevel);

        if(c_flag)
            returnVal = loadTpmContextFromFile(sysContext, &activateHandle, contextFilePath);
        if(C_flag && returnVal == 0)
            returnVal = loadTpmContextFromFile(sysContext, &keyHandle, keyContextFilePath);
        if(returnVal == 0)
            returnVal = activateCredential();

        finishTest();

        if(returnVal)
            return -13;
    }
    else
    {
        showArgMismatch(argv[0]);
        return -14;
    }
    return 0;
}