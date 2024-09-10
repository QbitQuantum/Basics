static void server_addrs_add(
    IN OUT struct server_addrs *addrs,
    IN const netaddr4 *addr)
{
    /* we keep a list of addrs used to connect to each server. once it gets
     * bigger than NFS41_ADDRS_PER_SERVER, overwrite the oldest addrs. use
     * server_addrs.next_index to implement a circular array */

    AcquireSRWLockExclusive(&addrs->lock);

    if (multi_addr_find(&addrs->addrs, addr, NULL)) {
        dprintf(SRVLVL, "server_addrs_add() found existing addr '%s'.\n",
            addr->uaddr);
    } else {
        /* overwrite the address at 'next_index' */
        StringCchCopyA(addrs->addrs.arr[addrs->next_index].netid,
            NFS41_NETWORK_ID_LEN+1, addr->netid);
        StringCchCopyA(addrs->addrs.arr[addrs->next_index].uaddr,
            NFS41_UNIVERSAL_ADDR_LEN+1, addr->uaddr);

        /* increment/wrap next_index */
        addrs->next_index = (addrs->next_index + 1) % NFS41_ADDRS_PER_SERVER;
        /* update addrs.count if necessary */
        if (addrs->addrs.count < addrs->next_index)
            addrs->addrs.count = addrs->next_index;

        dprintf(SRVLVL, "server_addrs_add() added new addr '%s'.\n",
            addr->uaddr);
    }
    ReleaseSRWLockExclusive(&addrs->lock);
}