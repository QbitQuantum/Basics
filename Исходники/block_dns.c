DWORD
add_block_dns_filters(HANDLE *engine_handle,
                      int index,
                      const WCHAR *exe_path,
                      block_dns_msg_handler_t msg_handler
                      )
{
    FWPM_SESSION0 session = {0};
    FWPM_SUBLAYER0 *sublayer_ptr = NULL;
    NET_LUID tapluid;
    UINT64 filterid;
    FWP_BYTE_BLOB *openvpnblob = NULL;
    FWPM_FILTER0 Filter = {0};
    FWPM_FILTER_CONDITION0 Condition[2] = {0};
    DWORD err = 0;

    if (!msg_handler)
    {
        msg_handler = default_msg_handler;
    }

    /* Add temporary filters which don't survive reboots or crashes. */
    session.flags = FWPM_SESSION_FLAG_DYNAMIC;

    *engine_handle = NULL;

    err = FwpmEngineOpen0(NULL, RPC_C_AUTHN_WINNT, NULL, &session, engine_handle);
    CHECK_ERROR(err, "FwpEngineOpen: open fwp session failed");
    msg_handler(0, "Block_DNS: WFP engine opened");

    /* Check sublayer exists and add one if it does not. */
    if (FwpmSubLayerGetByKey0(*engine_handle, &OPENVPN_BLOCK_OUTSIDE_DNS_SUBLAYER, &sublayer_ptr)
        == ERROR_SUCCESS)
    {
        msg_handler(0, "Block_DNS: Using existing sublayer");
        FwpmFreeMemory0((void **)&sublayer_ptr);
    }
    else
    {  /* Add a new sublayer -- as another process may add it in the meantime,
        * do not treat "already exists" as an error */
        err = add_sublayer(OPENVPN_BLOCK_OUTSIDE_DNS_SUBLAYER);

        if (err == FWP_E_ALREADY_EXISTS || err == ERROR_SUCCESS)
        {
            msg_handler(0, "Block_DNS: Added a persistent sublayer with pre-defined UUID");
        }
        else
        {
            CHECK_ERROR(err, "add_sublayer: failed to add persistent sublayer");
        }
    }

    err = ConvertInterfaceIndexToLuid(index, &tapluid);
    CHECK_ERROR(err, "Convert interface index to luid failed");

    err = FwpmGetAppIdFromFileName0(exe_path, &openvpnblob);
    CHECK_ERROR(err, "Get byte blob for openvpn executable name failed");

    /* Prepare filter. */
    Filter.subLayerKey = OPENVPN_BLOCK_OUTSIDE_DNS_SUBLAYER;
    Filter.displayData.name = FIREWALL_NAME;
    Filter.weight.type = FWP_UINT8;
    Filter.weight.uint8 = 0xF;
    Filter.filterCondition = Condition;
    Filter.numFilterConditions = 2;

    /* First filter. Permit IPv4 DNS queries from OpenVPN itself. */
    Filter.layerKey = FWPM_LAYER_ALE_AUTH_CONNECT_V4;
    Filter.action.type = FWP_ACTION_PERMIT;

    Condition[0].fieldKey = FWPM_CONDITION_IP_REMOTE_PORT;
    Condition[0].matchType = FWP_MATCH_EQUAL;
    Condition[0].conditionValue.type = FWP_UINT16;
    Condition[0].conditionValue.uint16 = 53;

    Condition[1].fieldKey = FWPM_CONDITION_ALE_APP_ID;
    Condition[1].matchType = FWP_MATCH_EQUAL;
    Condition[1].conditionValue.type = FWP_BYTE_BLOB_TYPE;
    Condition[1].conditionValue.byteBlob = openvpnblob;

    err = FwpmFilterAdd0(*engine_handle, &Filter, NULL, &filterid);
    CHECK_ERROR(err, "Add filter to permit IPv4 port 53 traffic from OpenVPN failed");

    /* Second filter. Permit IPv6 DNS queries from OpenVPN itself. */
    Filter.layerKey = FWPM_LAYER_ALE_AUTH_CONNECT_V6;

    err = FwpmFilterAdd0(*engine_handle, &Filter, NULL, &filterid);
    CHECK_ERROR(err, "Add filter to permit IPv6 port 53 traffic from OpenVPN failed");

    msg_handler(0, "Block_DNS: Added permit filters for exe_path");

    /* Third filter. Block all IPv4 DNS queries. */
    Filter.layerKey = FWPM_LAYER_ALE_AUTH_CONNECT_V4;
    Filter.action.type = FWP_ACTION_BLOCK;
    Filter.weight.type = FWP_EMPTY;
    Filter.numFilterConditions = 1;

    err = FwpmFilterAdd0(*engine_handle, &Filter, NULL, &filterid);
    CHECK_ERROR(err, "Add filter to block IPv4 DNS traffic failed");

    /* Forth filter. Block all IPv6 DNS queries. */
    Filter.layerKey = FWPM_LAYER_ALE_AUTH_CONNECT_V6;

    err = FwpmFilterAdd0(*engine_handle, &Filter, NULL, &filterid);
    CHECK_ERROR(err, "Add filter to block IPv6 DNS traffic failed");

    msg_handler(0, "Block_DNS: Added block filters for all interfaces");

    /* Fifth filter. Permit IPv4 DNS queries from TAP.
     * Use a non-zero weight so that the permit filters get higher priority
     * over the block filter added with automatic weighting */

    Filter.weight.type = FWP_UINT8;
    Filter.weight.uint8 = 0xE;
    Filter.layerKey = FWPM_LAYER_ALE_AUTH_CONNECT_V4;
    Filter.action.type = FWP_ACTION_PERMIT;
    Filter.numFilterConditions = 2;

    Condition[1].fieldKey = FWPM_CONDITION_IP_LOCAL_INTERFACE;
    Condition[1].matchType = FWP_MATCH_EQUAL;
    Condition[1].conditionValue.type = FWP_UINT64;
    Condition[1].conditionValue.uint64 = &tapluid.Value;

    err = FwpmFilterAdd0(*engine_handle, &Filter, NULL, &filterid);
    CHECK_ERROR(err, "Add filter to permit IPv4 DNS traffic through TAP failed");

    /* Sixth filter. Permit IPv6 DNS queries from TAP.
     * Use same weight as IPv4 filter */
    Filter.layerKey = FWPM_LAYER_ALE_AUTH_CONNECT_V6;

    err = FwpmFilterAdd0(*engine_handle, &Filter, NULL, &filterid);
    CHECK_ERROR(err, "Add filter to permit IPv6 DNS traffic through TAP failed");

    msg_handler(0, "Block_DNS: Added permit filters for TAP interface");

out:

    if (openvpnblob)
    {
        FwpmFreeMemory0((void **)&openvpnblob);
    }

    if (err && *engine_handle)
    {
        FwpmEngineClose0(*engine_handle);
        *engine_handle = NULL;
    }

    return err;
}