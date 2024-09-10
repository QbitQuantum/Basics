static VOID AddNetShareIfNeeded(VOID)
{
    if (!OptShareTarget)
        return;

    SHARE_INFO_2 ShareInfo = { 0 };
    NET_API_STATUS NetStatus;

    ShareInfo.shi2_netname = OptShareName;
    ShareInfo.shi2_type = STYPE_DISKTREE;
    ShareInfo.shi2_permissions = ACCESS_ALL;
    ShareInfo.shi2_max_uses = -1;
    ShareInfo.shi2_path = OptShareTarget;

    NetShareDel(0, OptShareName, 0);
    NetStatus = NetShareAdd(0, 2, (PBYTE)&ShareInfo, 0);
    if (NERR_Success != NetStatus)
        ABORT("cannot add network share");
}