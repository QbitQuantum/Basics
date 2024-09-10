int cmd_hide_file_raw(const VSTRING& param)
{
    const char* tfs_name = canonical_param(param[0]);
    char appkey[257];
    int size = param.size();

    TfsUnlinkType unlink_type = CONCEAL;
    if (size > 1)
    {
        unlink_type = static_cast<TfsUnlinkType>(atoi(param[1].c_str()));
    }

    if (size > 2)
    {
        strncpy(appkey, param[2].c_str(), 256);
        appkey[256] = '\0';
    }
    else
    {
        strcpy(appkey, app_key);
    }

    RcClientImpl impl;
    int ret = impl.initialize(rc_addr, appkey, app_ip);
    if (TFS_SUCCESS != ret)
    {
        TBSYS_LOG(DEBUG, "rc client login fail, ret: %d", ret);
    }
    else
    {
        ret = impl.unlink(tfs_name, NULL, unlink_type);
    }

    ToolUtil::print_info(ret, "hide %s %d", tfs_name, unlink_type);

    return ret;
}