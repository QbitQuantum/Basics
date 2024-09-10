static NTSTATUS
v2v_get_remote_state_internal(xenbus_transaction_t xbt,
                              struct v2v_channel *channel,
                              enum v2v_endpoint_state *state)
{
    NTSTATUS status;
    char *raw;
    STRING s1, s2;

    XM_ASSERT(channel != NULL);
    XM_ASSERT(state != NULL);

    *state = v2v_state_unknown;

    status = v2v_xenstore_readv_string(&raw,
                                       xbt,
                                       channel->remote_prefix,
                                       "state",
                                       NULL);
    if (!NT_SUCCESS(status))
        return status;

    RtlInitString(&s1, raw);

    if (RtlCompareString(&s1, v2v_make_cs(&s2, "unready"), FALSE) == 0)
        *state = v2v_state_unready;
    else if (RtlCompareString(&s1, v2v_make_cs(&s2, "listening"), FALSE) == 0)
        *state = v2v_state_listening;
    else if (RtlCompareString(&s1, v2v_make_cs(&s2, "connected"), FALSE) == 0)
        *state = v2v_state_connected;
    else if (RtlCompareString(&s1, v2v_make_cs(&s2, "disconnecting"), FALSE) == 0)
        *state = v2v_state_disconnecting;
    else if (RtlCompareString(&s1, v2v_make_cs(&s2, "disconnected"), FALSE) == 0)
        *state = v2v_state_disconnected;
    else if (RtlCompareString(&s1, v2v_make_cs(&s2, "crashed"), FALSE) == 0)
        *state = v2v_state_crashed;    

    ExFreePoolWithTag(raw, V2V_TAG);    
    
    return (*state != v2v_state_unknown ? STATUS_SUCCESS : STATUS_DATA_ERROR); 
}