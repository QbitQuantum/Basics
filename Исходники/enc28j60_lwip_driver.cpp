BOOL ENC28J60_LWIP_Driver::Close( ENC28J60_LWIP_DRIVER_CONFIG* config, int index )
{
    NATIVE_PROFILE_HAL_DRIVERS_ETHERNET();

    if(config == NULL) return FALSE;

    LwipUpTimeCompletion.Abort();

    netif_set_link_down( &g_ENC28J60_NetIF );
    netif_set_down( &g_ENC28J60_NetIF );
    netif_remove( &g_ENC28J60_NetIF );

    /* Disable the INTERRUPT pin */                            
    CPU_GPIO_EnableInputPin2(config->INT_Pin, 
                              FALSE,                         /* Glitch filter enable */
                              NULL,                          /* ISR                  */
                              0,                             /* minor number         */
                              GPIO_INT_NONE,                 /* Interrupt edge       */
                              RESISTOR_PULLUP);              /* Resistor State       */

    InterruptTaskContinuation.Abort();

    LwipNetworkStatus = FALSE;
    
    enc28j60_lwip_close( &g_ENC28J60_NetIF );

    memset(&g_ENC28J60_NetIF, 0, sizeof(g_ENC28J60_NetIF));

    return TRUE;

}