static void
merge_one_ip6_config (NMResolvConfData *rc, NMIP6Config *src, const char *iface)
{
    guint32 num, i;

    num = nm_ip6_config_get_num_nameservers (src);
    for (i = 0; i < num; i++) {
        const struct in6_addr *addr;
        char buf[INET6_ADDRSTRLEN];

        addr = nm_ip6_config_get_nameserver (src, i);

        /* inet_ntop is probably supposed to do this for us, but it doesn't */
        if (IN6_IS_ADDR_V4MAPPED (addr)) {
            if (inet_ntop (AF_INET, &(addr->s6_addr32[3]), buf, INET_ADDRSTRLEN) > 0)
                add_string_item (rc->nameservers, buf);
        } else {
            if (inet_ntop (AF_INET6, addr, buf, INET6_ADDRSTRLEN) > 0) {
                if (IN6_IS_ADDR_LINKLOCAL (addr) && strchr (buf, '%') == NULL) {
                    char *tmp;
                    tmp = g_strdup_printf ("%s%%%s", buf, iface);
                    add_string_item (rc->nameservers, tmp);
                    g_free (tmp);
                } else
                    add_string_item (rc->nameservers, buf);
            }
        }
    }

    num = nm_ip6_config_get_num_domains (src);
    for (i = 0; i < num; i++) {
        const char *domain;

        domain = nm_ip6_config_get_domain (src, i);
        if (!rc->domain)
            rc->domain = domain;
        add_string_item (rc->searches, domain);
    }

    num = nm_ip6_config_get_num_searches (src);
    for (i = 0; i < num; i++)
        add_string_item (rc->searches, nm_ip6_config_get_search (src, i));
}