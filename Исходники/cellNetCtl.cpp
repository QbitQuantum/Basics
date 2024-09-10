s32 cellNetCtlGetState(vm::ptr<u32> state)
{
    cellNetCtl.trace("cellNetCtlGetState(state=*0x%x)", state);

    switch (rpcs3::config.misc.net.status.value())
    {
    case misc_net_status::ip_obtained:
        *state = CELL_NET_CTL_STATE_IPObtained;
        break;
    case misc_net_status::obtaining_ip:
        *state = CELL_NET_CTL_STATE_IPObtaining;
        break;
    case misc_net_status::connecting:
        *state = CELL_NET_CTL_STATE_Connecting;
        break;
    case misc_net_status::disconnected:
        *state = CELL_NET_CTL_STATE_Disconnected;
        break;

    default:
        *state = CELL_NET_CTL_STATE_Disconnected;
        break;
    }

    return CELL_OK;
}