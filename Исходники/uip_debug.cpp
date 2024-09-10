/**
 * @brief
 * @note
 * @param
 * @retval
 */
void UIPDebug::uip_debug_printconns(void) {
    for(uint8_t i = 0; i < UIP_CONNS; i++) {
        if(uip_debug_printcon(&con[i], &uip_conns[i])) {
            pc.printf("connection[");
            pc.printf("%d", i);
            pc.printf("] changed.\n");
        }
    }
}