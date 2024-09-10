int main(int argc, char* argv[])
{
    char hostName[200] = DEFAULT_HOSTNAME;
    int port = DEFAULT_RESMGR_TPM_PORT;

    TPMI_DH_OBJECT objectHandle;
    char outFilePath[PATH_MAX] = {0};
    char *contextFile = NULL;

    setbuf(stdout, NULL);
    setvbuf (stdout, NULL, _IONBF, BUFSIZ);

    int opt = -1;
    const char *optstring = "hvH:o:p:d:c:";
    static struct option long_options[] = {
      {"help",0,NULL,'h'},
      {"version",0,NULL,'v'},
      {"object",1,NULL,'H'},
      {"opu",1,NULL,'o'},
      {"port",1,NULL,'p'},
      {"debugLevel",1,NULL,'d'},
      {"contextObject",1,NULL,'c'},
      {0,0,0,0}
    };

    int returnVal = 0;
    int flagCnt = 0;
    int h_flag = 0,
        v_flag = 0,
        H_flag = 0,
        c_flag = 0,
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
        case 'H':
            if(getSizeUint32Hex(optarg,&objectHandle) != 0)
            {
                returnVal = -1;
                break;
            }
            printf("\nobject handle: 0x%x\n\n",objectHandle);
            H_flag = 1;
            break;
        case 'o':
            safeStrNCpy(outFilePath, optarg, sizeof(outFilePath));
            if(checkOutFile(outFilePath) != 0)
            {
                returnVal = -2;
                break;
            }
            o_flag = 1;
            break;
        case 'p':
            if( getPort(optarg, &port) )
            {
                printf("Incorrect port number.\n");
                returnVal = -3;
            }
            break;
        case 'd':
            if( getDebugLevel(optarg, &debugLevel) )
            {
                printf("Incorrect debug level.\n");
                returnVal = -4;
            }
            break;
        case 'c':
            contextFile = optarg;
            if(contextFile == NULL || contextFile[0] == '\0')
            {
                returnVal = -5;
                break;
            }
            printf("contextFile = %s\n", contextFile);
            c_flag = 1;
            break;
        case ':':
//              printf("Argument %c needs a value!\n",optopt);
            returnVal = -6;
            break;
        case '?':
//              printf("Unknown Argument: %c\n",optopt);
            returnVal = -7;
            break;
        //default:
        //  break;
        }
        if(returnVal)
            break;
    };

    if(returnVal != 0)
        return returnVal;

    flagCnt = h_flag + v_flag + H_flag + o_flag + c_flag;
    if(flagCnt == 1)
    {
        if(h_flag == 1)
            showHelp(argv[0]);
        else if(v_flag == 1)
            showVersion(argv[0]);
        else
        {
            showArgMismatch(argv[0]);
            return -8;
        }
    }
    else if(flagCnt == 2 && (H_flag == 1 || c_flag) && o_flag == 1)
    {
        prepareTest(hostName, port, debugLevel);

        if(c_flag)
            returnVal = loadTpmContextFromFile(sysContext, &objectHandle, contextFile);
        if(returnVal == 0)
            returnVal = readPublic(objectHandle, outFilePath);

        finishTest();

        if(returnVal)
            return -9;
    }
    else
    {
        showArgMismatch(argv[0]);
        return -10;
    }

    return 0;
}