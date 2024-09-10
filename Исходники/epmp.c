void ept_delete(handle_t h,
                unsigned32 num_ents,
                ept_entry_t entries[],
                error_status_t *status)
{
    unsigned32 i;
    RPC_STATUS rpc_status;

    *status = RPC_S_OK;

    WINE_TRACE("(%p, %lu, %p, %p)\n", h, num_ents, entries, status);

    EnterCriticalSection(&csEpm);

    for (i = 0; i < num_ents; i++)
    {
        struct registered_ept_entry *entry;
        RPC_SYNTAX_IDENTIFIER iface, syntax;
        char *protseq;
        char *endpoint;
        char *address;
        rpc_status = TowerExplode(entries[i].tower, &iface, &syntax, &protseq,
                                  &endpoint, &address);
        if (rpc_status != RPC_S_OK)
            break;
        entry = find_ept_entry(&iface, &syntax, protseq, endpoint, address, &entries[i].object);
        if (entry)
            delete_registered_ept_entry(entry);
        else
        {
            *status = EPT_S_NOT_REGISTERED;
            break;
        }
        I_RpcFree(protseq);
        I_RpcFree(endpoint);
        I_RpcFree(address);
    }

    LeaveCriticalSection(&csEpm);
}