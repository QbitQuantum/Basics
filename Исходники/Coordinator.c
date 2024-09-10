/****************************************************************************
 *
 * NAME: vJenie_CbConfigureNetwork
 *
 * DESCRIPTION:
 * Entry point for application from boot loader.
 *
 * RETURNS:
 * Nothing
 *
 ****************************************************************************/
PUBLIC void vJenie_CbConfigureNetwork(void)
{
	/* Set up routing table */
	gJenie_RoutingEnabled    = TRUE;
	gJenie_RoutingTableSize  = ROUTING_TABLE_SIZE;
	gJenie_RoutingTableSpace = (void *) asRoutingTable;

    /* Change default network config */
    gJenie_NetworkApplicationID = APPLICATION_ID;
    gJenie_PanID                = PAN_ID;
    gJenie_Channel              = CHANNEL;
    gJenie_ScanChannels         = SCAN_CHANNELS;

	/* Open UART for printf use {v2} */
	vUART_printInit();
	/* Output function call to UART */
	vPrintf("\nvJenie_CbConfigureNetwork()\n");
}