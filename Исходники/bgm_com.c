/* ------------------------------------------------------------------------
   Main thread for the ezbgm module.
   After execution, initialize interrupt environment, register command, and
   then wait until there is a request from the EE.
   ------------------------------------------------------------------------ */
int sce_bgm_loop()
{
    sceSifQueueData qd;
    sceSifServeData sd;

    //-- Initialize interrupt environment in advance.

    CpuEnableIntr();
    EnableIntr( INUM_DMA_4 );
    EnableIntr( INUM_DMA_7 );

    //--- Register function that is called according to request


    sceSifInitRpc(0);

    sceSifSetRpcQueue( &qd, GetThreadId() );
    sceSifRegisterRpc( &sd, EZBGM_DEV, bgmFunc, (void*)gRpcArg, NULL, NULL, &qd );
    PRINTF(("goto bgm cmd loop\n"));

    //--- Command-wait loop

    sceSifRpcLoop(&qd);

    return 0;
}