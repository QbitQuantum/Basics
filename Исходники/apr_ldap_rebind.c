/* LDAP_rebindproc() openLDAP V3 style
 * ON ENTRY:
 *     ld       Pointer to an LDAP control structure. (input only)
 *     url      Unused in this routine
 *     request  Unused in this routine
 *     msgid    Unused in this routine
 */
static int LDAP_rebindproc(LDAP *ld, LDAP_CONST char *url, int request, ber_int_t msgid)
{

    apr_ldap_rebind_entry_t *my_conn;
    const char *bindDN = NULL;
    const char *bindPW = NULL;

    my_conn = apr_ldap_rebind_lookup(ld);

    if ((my_conn) && (my_conn->bindDN != NULL)) {
        bindDN = my_conn->bindDN;
        bindPW = my_conn->bindPW;
    }

    return (ldap_bind_s(ld, bindDN, bindPW, LDAP_AUTH_SIMPLE));
}