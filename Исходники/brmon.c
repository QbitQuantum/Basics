static int dump_msg(const struct sockaddr_nl *who, struct nlmsghdr *n,
                    void *arg)
{
    FILE *fp = arg;
    struct ifinfomsg *ifi = NLMSG_DATA(n);
    struct rtattr * tb[IFLA_MAX + 1];
    int len = n->nlmsg_len;
    char b1[IFNAMSIZ];
    int af_family = ifi->ifi_family;
    bool newlink;
    int br_index;

    if(n->nlmsg_type == NLMSG_DONE)
        return 0;

    len -= NLMSG_LENGTH(sizeof(*ifi));
    if(len < 0)
    {
        return -1;
    }

    if(af_family != AF_BRIDGE && af_family != AF_UNSPEC)
        return 0;

    if(n->nlmsg_type != RTM_NEWLINK && n->nlmsg_type != RTM_DELLINK)
        return 0;

    parse_rtattr(tb, IFLA_MAX, IFLA_RTA(ifi), len);

    /* Check if we got this from bonding */
    if(tb[IFLA_MASTER] && af_family != AF_BRIDGE)
        return 0;

    if(tb[IFLA_IFNAME] == NULL)
    {
        fprintf(stderr, "BUG: nil ifname\n");
        return -1;
    }

    if(n->nlmsg_type == RTM_DELLINK)
        fprintf(fp, "Deleted ");

    fprintf(fp, "%d: %s ", ifi->ifi_index, (char*)RTA_DATA(tb[IFLA_IFNAME]));

    if(tb[IFLA_OPERSTATE])
    {
        int state = *(int*)RTA_DATA(tb[IFLA_OPERSTATE]);
        switch (state)
        {
            case IF_OPER_UNKNOWN:
                fprintf(fp, "Unknown ");
                break;
            case IF_OPER_NOTPRESENT:
                fprintf(fp, "Not Present ");
                break;
            case IF_OPER_DOWN:
                fprintf(fp, "Down ");
                break;
            case IF_OPER_LOWERLAYERDOWN:
                fprintf(fp, "Lowerlayerdown ");
                break;
            case IF_OPER_TESTING:
                fprintf(fp, "Testing ");
                break;
            case IF_OPER_DORMANT:
                fprintf(fp, "Dormant ");
                break;
            case IF_OPER_UP:
                fprintf(fp, "Up ");
                break;
            default:
                fprintf(fp, "State(%d) ", state);
        }
    }

    if(tb[IFLA_MTU])
        fprintf(fp, "mtu %u ", *(int*)RTA_DATA(tb[IFLA_MTU]));

    if(tb[IFLA_MASTER])
    {
        fprintf(fp, "master %s ",
                if_indextoname(*(int*)RTA_DATA(tb[IFLA_MASTER]), b1));
    }

    if(tb[IFLA_PROTINFO])
    {
        uint8_t state = *(uint8_t *)RTA_DATA(tb[IFLA_PROTINFO]);
        if(state <= BR_STATE_BLOCKING)
            fprintf(fp, "state %s", port_states[state]);
        else
            fprintf(fp, "state (%d)", state);
    }

    fprintf(fp, "\n");
    fflush(fp);

    newlink = (n->nlmsg_type == RTM_NEWLINK);

    if(tb[IFLA_MASTER])
        br_index = *(int*)RTA_DATA(tb[IFLA_MASTER]);
    else if(is_bridge((char*)RTA_DATA(tb[IFLA_IFNAME])))
        br_index = ifi->ifi_index;
    else
        br_index = -1;

    bridge_notify(br_index, ifi->ifi_index, newlink, ifi->ifi_flags);

    return 0;
}