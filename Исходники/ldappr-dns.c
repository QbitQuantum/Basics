int
prldap_x_install_dns_skipdb(LDAP *ld, const char *skip)
{
    enum __nsw_parse_err		pserr;
    struct __nsw_switchconfig       *conf;
    struct __nsw_lookup             *lkp;
    struct ldap_dns_fns             dns_fns;
    char                            *name_list = NULL;
    char                            *tmp;
    const char                      *name;
    int                             len;
    boolean_t                       got_skip = B_FALSE;

    /*
     * db_root_hosts.lock mutex is used to ensure that the name list
     * is not in use by the name service switch while we are updating
     * the host_service
     */

    (void) mutex_lock(&db_root_hosts.lock);
    conf = __nsw_getconfig("hosts", &pserr);
    if (conf == NULL) {
        (void) mutex_unlock(&db_root_hosts.lock);
        return (0);
    }

    /* check for skip and count other backends */
    for (lkp = conf->lookups; lkp != NULL; lkp = lkp->next) {
        name = lkp->service_name;
        if (strcmp(name, skip) == 0) {
            got_skip = B_TRUE;
            continue;
        }
        if (name_list == NULL)
            name_list = strdup(name);
        else {
            len = strlen(name_list);
            tmp = realloc(name_list, len + strlen(name) + 2);
            if (tmp == NULL) {
                free(name_list);
                name_list = NULL;
            } else {
                name_list = tmp;
                name_list[len++] = ' ';
                (void) strcpy(name_list+len, name);
            }
        }
        if (name_list == NULL) {        /* alloc error */
            (void) mutex_unlock(&db_root_hosts.lock);
            __nsw_freeconfig(conf);
            return (-1);
        }
    }
    __nsw_freeconfig(conf);
    if (!got_skip) {
        /*
         * Since skip name service not used for hosts, we do not need
         * to install our private address resolution function
         */
        (void) mutex_unlock(&db_root_hosts.lock);
        if (name_list != NULL)
            free(name_list);
        return (0);
    }
    if (host_service != NULL)
        free(host_service);
    host_service = name_list;
    (void) mutex_unlock(&db_root_hosts.lock);

    if (ldap_get_option(ld, LDAP_OPT_DNS_FN_PTRS, &dns_fns) != 0)
        return (-1);
    dns_fns.lddnsfn_bufsize = PR_NETDB_BUF_SIZE;
    dns_fns.lddnsfn_gethostbyname = prldap_gethostbyname1;
    if (ldap_set_option(ld, LDAP_OPT_DNS_FN_PTRS, &dns_fns) != 0)
        return (-1);
    return (0);
}