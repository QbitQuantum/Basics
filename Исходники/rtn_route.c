GOS_ERROR_CODE rtn_ipv6_route(int wanIndex)
{
    int   i = 0, prefix = 0;
    char  cmdStr[512] = {0};
    char  tempcmd[256] = {0};
    char  buf[64] = {0}, appname[32] = {0};
    RG_IPV6_SROUTE_RULE_T *pData;

    if (gRtnParams.wan_cfg[wanIndex].ip6State != RG_WAN_IF_UP)
    {
        RTN_LOG("Cfg ipv6 route wan%d not up, state:%d, return!", wanIndex, gRtnParams.wan_cfg[wanIndex].ip6State);
        return GOS_OK;
    }

    RTN_LOG("IPv6 Routing count = %d", gRtnParams.route_cfg.sroutev6.count);
    for(i = 0; i <gRtnParams.route_cfg.sroutev6.count; i++)
    {
        pData = &gRtnParams.route_cfg.sroutev6.rules[i];

        if(pData->wan_index == 0)
        {
            sprintf(appname, "br0");
        }
        else if (pData->wan_index != (wanIndex+1))
        {
            continue;
        }
        else
        {
            memset(appname, 0, sizeof(appname));
            strcpy(appname, gRtnParams.wan_cfg[wanIndex].wanInfo.appName);
        }

        if(pData->static_mode == TRUE)
        {
            inet_ntop(AF_INET6, pData->dest_ip, buf, sizeof(buf));
            prefix = pData->dest_prefixlen;
            sprintf(cmdStr, "ip -6 route add %s/%d ", buf, prefix);

            inet_ntop(AF_INET6, pData->next_hop, buf, sizeof(buf));
            sprintf(tempcmd, "via %s ", buf);
            strcat(cmdStr, tempcmd);

            sprintf(tempcmd, "dev %s ", appname);
            strcat(cmdStr, tempcmd);
            RTN_LOG("%s\n", cmdStr);

            system(cmdStr);
        }
        else
        {
            inet_ntop(AF_INET6, pData->src_ip, buf, sizeof(buf));
            prefix = pData->src_prefixlen;
            sprintf(cmdStr, "ip -6 rule add from %s/%d table %d pref %d ", buf, prefix, i + POLICY_ROUTEV6_OFFSET, i + POLICY_ROUTEV6_OFFSET);
            system(cmdStr);
            RTN_LOG("%s", cmdStr);

            sprintf(cmdStr, "ip -6 route add default ");

            inet_ntop(AF_INET6, pData->next_hop, buf, sizeof(buf));
            sprintf(tempcmd, "via %s ", buf);
            strcat(cmdStr, tempcmd);

            sprintf(tempcmd, "dev %s table %d ", appname, i + POLICY_ROUTEV6_OFFSET);
            strcat(cmdStr, tempcmd);

            system(cmdStr);
            RTN_LOG("%s\n", cmdStr);
        }
    }

    return GOS_OK;
}