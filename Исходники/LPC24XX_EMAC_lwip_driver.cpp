BOOL LPC24XX_EMAC_LWIP_Driver::Close( )
{
    LwipUpTimeCompletion.Abort();

    /* Disable the interrupt */
    CPU_INTC_DeactivateInterrupt(LPC24XX_VIC::c_IRQ_INDEX_EMAC);

    InterruptTaskContinuation.Abort();

    LwipNetworkStatus = 0;

    netif_set_down( &g_LPC24XX_EMAC_NetIF );
    netif_remove( &g_LPC24XX_EMAC_NetIF );

    LPC24XX_EMAC_lwip_close( &g_LPC24XX_EMAC_NetIF );
    
    memset( &g_LPC24XX_EMAC_NetIF, 0, sizeof g_LPC24XX_EMAC_NetIF);

    return TRUE;
}