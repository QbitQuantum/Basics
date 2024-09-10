BOOL AT91_EMAC_LWIP_Driver::Close(void)
{
    LwipUpTimeCompletion.Abort();

    CPU_INTC_DeactivateInterrupt(AT91C_ID_EMAC);

    InterruptTaskContinuation.Abort();

    LwipNetworkStatus = 0;

    netif_set_down( &g_AT91_EMAC_NetIF );
    netif_remove( &g_AT91_EMAC_NetIF );

    AT91_EMAC_LWIP_close( &g_AT91_EMAC_NetIF );
    
    memset( &g_AT91_EMAC_NetIF, 0, sizeof g_AT91_EMAC_NetIF );

    return TRUE;
}