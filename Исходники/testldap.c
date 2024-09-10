static void test_ldap_connection(abts_case *tc, LDAP *ldap)
{
    int version  = LDAP_VERSION3;
    int failures, result;
    
    /* always default to LDAP V3 */
    ldap_set_option(ldap, LDAP_OPT_PROTOCOL_VERSION, &version);

    for (failures=0; failures<10; failures++)
    {
        result = ldap_simple_bind_s(ldap,
                                    (char *)NULL,
                                    (char *)NULL);
        if (LDAP_SERVER_DOWN != result)
            break;
    }

    ABTS_TRUE(tc, result == LDAP_SUCCESS);
    if (result != LDAP_SUCCESS) {
        abts_log_message("%s\n", ldap_err2string(result));
    }

    ldap_unbind_s(ldap);

    return;
}