BOOL SH7264_SMSC_LWIP_Driver::Close(void)
{
    LwipUpTimeCompletion.Abort();

    //CPU_INTC_DeactivateInterrupt(SH7264C_ID_EDMAC);
    CPU_INTC_DeactivateInterrupt(81);

    InterruptTaskContinuation.Abort();

    LwipNetworkStatus = 0;

    netif_set_down( &g_SH7264_SMSC_NetIF );
    netif_remove( &g_SH7264_SMSC_NetIF );

    SH7264_SMSC_lwip_close( &g_SH7264_SMSC_NetIF );
    
    memset( &g_SH7264_SMSC_NetIF, 0, sizeof g_SH7264_SMSC_NetIF);

    return TRUE;
}