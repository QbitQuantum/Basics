int net_if_set_eui64(int if_id, net_if_eui64_t *eui64)
{
    if (eui64 == NULL) {
        return 0;
    }

    uint64_t tmp = NTOHLL(eui64->uint64);

    if (if_id < 0 || if_id >= NET_IF_MAX || !interfaces[if_id].initialized) {
        DEBUG("Set EUI-64: No interface initialized with ID %d.\n", if_id);
        return 0;
    }

    net_if_transceiver_get_set_handler(if_id, SET_LONG_ADDR, (void *) &tmp);

    return eui64->uint64 != 0;
}