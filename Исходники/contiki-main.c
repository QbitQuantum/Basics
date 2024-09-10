/*---------------------------------------------------------------------------*/
static void
set_rime_addr(void)
{
    uint8_t *addr_long = NULL;
    uint16_t addr_short = 0;
    char i;

    __xdata unsigned char * macp = &X_IEEE_ADDR;

    PUTSTRING("Rime is 0x");
    PUTHEX(sizeof(rimeaddr_t));
    PUTSTRING(" bytes long\n");

    PUTSTRING("Reading MAC from Info Page\n");

    for(i = (RIMEADDR_SIZE - 1); i >= 0; --i) {
        rimeaddr_node_addr.u8[i] = *macp;
        macp++;
    }

    /* Now the address is stored MSB first */
#if STARTUP_VERBOSE
    PUTSTRING("Rime configured with address ");
    for(i = 0; i < RIMEADDR_SIZE - 1; i++) {
        PUTHEX(rimeaddr_node_addr.u8[i]);
        PUTCHAR(':');
    }
    PUTHEX(rimeaddr_node_addr.u8[i]);
    PUTCHAR('\n');
#endif

    cc2530_rf_set_addr(IEEE802154_PANID);
}