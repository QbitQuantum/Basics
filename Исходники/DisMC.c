int main(int ac, char **av)
{
    int	i, dRet, dVerCount;

    if( (dRet = dGetUserPermission()) == 0)
    {
        sprintf(errbuf, "INAVLID USER PERMISSION\n" );
        PrintOut(TIFB_FAIL, errbuf);
        return EXIT_FAILURE;
    }

    if( (dVerCount = dGetVerBlock(FILE_MC_INIT, STR_VER_COM)) < 0)
    {
        sprintf(errbuf, "ERROR IN dGetVerBlock(%s)\n", FILE_MC_INIT);
        PrintOut(TIFB_FAIL, errbuf);
        return EXIT_FAILURE;
    }

    if( (dRet = dGetBlocks(FILE_MC_INIT, STR_TSW_COM)) < 0)
    {
        sprintf(errbuf, "FAILED IN McInit\n" );
        PrintOut(TIFB_FAIL, errbuf);
        return EXIT_FAILURE;
    }
    else
        dCurrBlockCnt = dRet;

    //debug flag setting
    if( ac == 2 && av[1][0] == '-' && av[1][1] == 'd' ) {
        debug_flag = 1;
    } else {
        debug_flag = 0;
    }

    Init_Value();
    for(i = 0; i < dCurrBlockCnt; i++)
    {
        if(STR_TSW_COM[i] == NULL)
            continue;

        stProc.mpswinfo[i].pid = GetProcessID(STR_TSW_COM[i]);
        if(stProc.mpswinfo[i].pid > 0)
        {
            stProc.mpsw[i]			= NORMAL;
            stProc.mpswinfo[i].when	= starttime;
        }
        else
            stProc.mpsw[i] = CRITICAL;
    }

    for(i = 0; i < dCurrBlockCnt; i++)
    {
        if(stProc.mpsw[i] == NORMAL)
        {
            if(InitVersionShm() < 0)
            {
                sprintf(errbuf, "SHARED MEMORY( VERSION ) INIT FAILURE\n");
                PrintOut(TIFB_FAIL, errbuf);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    dInit_fidb();
    PrintResult(dVerCount);

    return EXIT_SUCCESS;
}