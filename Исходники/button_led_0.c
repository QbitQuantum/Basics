void main() {
    /* Configure GPI and GPO as Mode 0 (Direct Connect) */
    CT_CFG.GPCFG0 = 0x0000;

    /* Clear GPO pins */
    __R30 &= 0xFFFF0000;

    /* Configure INTC */
    configIntc();

    while(1) {
        /* Wait for SW1 to be pressed */
        if ((__R31 & SW1) != SW1) {
            /* Interrupt PRU1, wait 500ms for cheap "debounce" */
            /* TODO: Trigger interrupt - see #defines */
        }
    }

    /* Halt the PRU core - shouldn't get here */
    __halt();
}