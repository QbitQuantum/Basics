int main(int argc, char* argv[])
{
    char hostName[200] = DEFAULT_HOSTNAME;
    int port = DEFAULT_RESMGR_TPM_PORT;

    TPMI_DH_OBJECT keyHandle;
    BYTE *msg = NULL;
    UINT16 length = 0;
    UINT16 size = 0;
    long fileSize = 0;

    TPMT_TK_HASHCHECK validation;
    TPMI_ALG_HASH halg;
    char outFilePath[PATH_MAX] = {0};
    char inMsgFileName[PATH_MAX] = {0};
    char *contextKeyFile = NULL;

    setbuf(stdout, NULL);
    setvbuf (stdout, NULL, _IONBF, BUFSIZ);

    int opt = -1;
    const char *optstring = "hvk:P:g:m:t:s:p:d:c:";
    static struct option long_options[] = {
      {"help",0,NULL,'h'},
      {"version",0,NULL,'v'},
      {"keyHandle",1,NULL,'k'},
      {"pwdk",1,NULL,'P'},
      {"halg",1,NULL,'g'},
      {"msg",1,NULL,'m'},
      {"sig",1,NULL,'s'},
      {"ticket",1,NULL,'t'},
      {"port",1,NULL,'p'},
      {"debugLevel",1,NULL,'d'},
      {"keyContext",1,NULL,'c'},
      {0,0,0,0}
    };

    int returnVal = 0;
    int flagCnt = 0;
    int h_flag = 0,
        v_flag = 0,
        k_flag = 0,
        P_flag = 0,
        g_flag = 0,
        m_flag = 0,
        t_flag = 0,
        c_flag = 0,
        s_flag = 0;

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
            if(getSizeUint32Hex(optarg,&keyHandle) != 0)
            {
                returnVal = -1;
                break;
            }
            k_flag = 1;
            break;
        case 'P':
            sessionData.hmac.t.size = sizeof(sessionData.hmac.t) - 2;
            if(str2ByteStructure(optarg,&sessionData.hmac.t.size,sessionData.hmac.t.buffer) != 0)
            {
                returnVal = -2;
                break;
            }
            P_flag = 1;
            break;
        case 'g':
            if(getSizeUint16Hex(optarg,&halg) != 0)
            {
                showArgError(optarg, argv[0]);
                returnVal = -3;
                break;
            }
            printf("halg = 0x%4.4x\n", halg);
            g_flag = 1;
            break;
        case 'm':
            safeStrNCpy(inMsgFileName, optarg, sizeof(inMsgFileName));
            m_flag = 1;
            break;
        case 't':
            size = sizeof(validation);
            if(loadDataFromFile(optarg, (UINT8 *)&validation, &size) != 0)
            {
                returnVal = -4;
                break;
            }
            t_flag = 1;
            break;
        case 's':
            safeStrNCpy(outFilePath, optarg, sizeof(outFilePath));
            if(checkOutFile(outFilePath) != 0)
            {
                returnVal = -5;
                break;
            }
            s_flag = 1;
            break;
        case 'p':
            if( getPort(optarg, &port) )
            {
                printf("Incorrect port number.\n");
                returnVal = -6;
            }
            break;
        case 'd':
            if( getDebugLevel(optarg, &debugLevel) )
            {
                printf("Incorrect debug level.\n");
                returnVal = -7;
            }
            break;
        case 'c':
            contextKeyFile = optarg;
            if(contextKeyFile == NULL || contextKeyFile[0] == '\0')
            {
                returnVal = -8;
                break;
            }
            printf("contextKeyFile = %s\n", contextKeyFile);
            c_flag = 1;
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
        goto end;

    if(m_flag)
    {
        if(getFileSize(inMsgFileName, &fileSize))
        {
            returnVal = -11;
            goto end;
        }
        if(fileSize == 0)
        {
            printf("the message file is empty !\n");
            returnVal = -12;
            goto end;
        }
        if(fileSize > 0xffff)
        {
            printf("the message file was too long !\n");
            returnVal = -13;
            goto end;
        }
        msg = (BYTE*)malloc(fileSize);
        if(msg == NULL)
        {
            returnVal = -14;
            goto end;
        }
        memset(msg, 0, fileSize);

        length = fileSize;
        if(loadDataFromFile(inMsgFileName, msg, &length) != 0)
        {
            returnVal = -15;
            goto end;
        }
#if 0
        printf("\nmsg length: %d\n",length);
        printf("msg content: ");
        for(int i = 0; i < length; i++)
        {
            printf("%02x ", msg[i]);
        }
        printf("\n");
        return -1;
#endif
    }

    if(P_flag == 0)
        sessionData.hmac.t.size = 0;
    if(t_flag == 0)
    {
        validation.tag = TPM_ST_HASHCHECK;
        validation.hierarchy = TPM_RH_NULL;
        validation.digest.t.size = 0;
    }

    flagCnt = h_flag + v_flag + k_flag + g_flag + m_flag + s_flag + c_flag;

    if(flagCnt == 1)
    {
        if(h_flag == 1)
            showHelp(argv[0]);
        else if(v_flag == 1)
            showVersion(argv[0]);
        else
        {
            showArgMismatch(argv[0]);
            returnVal = -16;
        }
    }
    else if((flagCnt == 4) && (k_flag == 1 || c_flag == 1) && (g_flag == 1) && (m_flag == 1) && (s_flag == 1))
    {
        prepareTest(hostName, port, debugLevel);

        if(c_flag)
            returnVal = loadTpmContextFromFile(sysContext, &keyHandle, contextKeyFile);
        if(returnVal == 0)
            returnVal = sign(keyHandle, halg, msg, length, &validation, outFilePath);

        finishTest();

        if(returnVal)
            returnVal = -17;
    }
    else
    {
        showArgMismatch(argv[0]);
        returnVal = -18;
    }

end:
    if(msg)
        free(msg);
    return returnVal;
}