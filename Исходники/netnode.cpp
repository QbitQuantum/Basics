void TERMWINDOWMEMBER shownode(const NodesCitC *nd, ModemConsoleE W)
    {
    assert (nd);

    if (!read_node_ddata())
        {
        wPrintf(W, getmsg(59));
        return;
        }

    const char **nettypes = (const char **) nddd->next->aux;
    const char **nodemsgs = (const char **) nddd->next->next->aux;

    wPrintf(W, getnodemsg(14), nd->GetName());                  wDoCR(W);
    wPrintf(W, getnodemsg(15), nd->GetOldRegion());             wDoCR(W);
    wPrintf(W, getnodemsg(16), nd->GetAlias(), nd->GetLocID()); wDoCR(W);
#ifdef WINCIT
    wPrintf(W, "IpAddress:   %s", nd->GetIpAddress());          wDoCR(W);
    wPrintf(W, "IpPort:      %d", nd->GetIpPort());             wDoCR(W);
#endif
    wPrintf(W, getnodemsg(17), nd->GetPreDial());               wDoCR(W);
    wPrintf(W, getnodemsg(18), nd->GetDialOut());               wDoCR(W);
    wPrintf(W, getnodemsg(19), bauds[nd->GetBaud()]);           wDoCR(W);
    wPrintf(W, getnodemsg(20), nd->GetLoginMacro());            wDoCR(W);
    wPrintf(W, getnodemsg(21), nd->GetDialTimeout());           wDoCR(W);
    wPrintf(W, getnodemsg(22), nd->GetProtocol());              wDoCR(W);
    wPrintf(W, getnodemsg(23), nd->GetWaitTimeout());           wDoCR(W);
    wPrintf(W, getnodemsg(24), nd->GetMailFileName());          wDoCR(W);

    label Buffer;
    wPrintf(W, getnodemsg(25), nd->GetAutoHall() > 0 ?
            HallData[nd->GetAutoHall()].GetName(Buffer, sizeof(Buffer)) : getnodemsg(28));
    wDoCR(W);

    wPrintf(W, getnodemsg(26), nd->GetAutoGroup() > 0 ?
            GroupData[nd->GetAutoGroup()].GetName(Buffer, sizeof(Buffer)) : getnodemsg(28));
    wDoCR(W);

    wPrintf(W, getnodemsg(27), GroupData[nd->GetMapUnknownGroup()].GetName(Buffer, sizeof(Buffer)));
    wDoCR(W);

    wPrintf(W, getnodemsg(29), nettypes[nd->GetNetworkType()],
            nd->GetNetworkRevisionNumber() ? nd->GetNetworkRevisionNumber() + '@' : ' ');
    wDoCR(W);

    wPrintf(W, getnodemsg(30), nd->GetCreatePacket());          wDoCR(W);
    wPrintf(W, getnodemsg(31), nd->GetExtractPacket());         wDoCR(W);
    wPrintf(W, getnodemsg(32), nd->IsAutoRoom());               wDoCR(W);
    wPrintf(W, getnodemsg(33), nd->GetRequest());               wDoCR(W);
    wPrintf(W, getnodemsg(34), nd->IsGateway());                wDoCR(W);
    wPrintf(W, getnodemsg(35), nd->GetFetch());                 wDoCR(W);
    wPrintf(W, getnodemsg(36), nd->GetNetFail());               wDoCR(W);
    wPrintf(W, getnodemsg(37), nd->GetRedial());                wDoCR(W);
    wPrintf(W, getnodemsg(38), nd->GetOutputPace());            wDoCR(W);

    dump_node_ddata();
    }