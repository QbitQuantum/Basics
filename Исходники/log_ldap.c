static LDAPMessage *pw_ldap_uid_search(LDAP * const ld,
                                       const char *uid,
                                       char *attrs[])
{
    char *alloca_filter;
    size_t uid_size;
    size_t filter_size;
    int rc;
    LDAPMessage *res;

    if (uid == NULL || *uid == 0) {
        return NULL;
    }
    uid_size = strlen(uid);
    if (uid_size > MAX_LDAP_UID_LENGTH) {
        return NULL;
    }
    filter_size = strlen(ldap_filter) + uid_size + (size_t) 1U;
    if ((alloca_filter = ALLOCA(filter_size)) == NULL) {
        return NULL;
    }
    if (SNCHECK(snprintf(alloca_filter, filter_size, ldap_filter, uid),
        filter_size)) {
        ALLOCA_FREE(alloca_filter);
        return NULL;
    }
    rc = ldap_search_s(ld, base, LDAP_SCOPE_SUBTREE,
                       alloca_filter, attrs, 0, &res);
    ALLOCA_FREE(alloca_filter);
    if (rc != LDAP_SUCCESS) {
        return NULL;
    }

    return res;
}