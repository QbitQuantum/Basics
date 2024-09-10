static void can_set_global_mode(int mode) {
    /* set Global mode */
    RSCAN0GCTR = ((RSCAN0GCTR & 0xFFFFFFFC) | mode);
    /* Wait to cahnge into Global XXXX mode */
    while ((RSCAN0GSTS & 0x07) != mode) {
        __NOP();
    }
}