static krb5_error_code
krb5_update_server_info(krb5_ldap_server_handle *ldap_server_handle,
                        krb5_ldap_server_info *server_info)
{
    krb5_error_code            st=0;
    struct timeval             ztime={0, 0};
    LDAPMessage                *result=NULL;

    if (ldap_server_handle == NULL || server_info == NULL)
        return -1;

    while (st == 0) {
        st = ldap_result(ldap_server_handle->ldap_handle, ldap_server_handle->msgid,
                         LDAP_MSG_ALL, &ztime, &result);
        switch (st) {
        case -1:
            server_info->server_status = OFF;
            time(&server_info->downtime);
            break;

        case 0:
            continue;
            break;

        case LDAP_RES_BIND:
            if ((st=ldap_result2error(ldap_server_handle->ldap_handle, result, 1)) == LDAP_SUCCESS) {
                server_info->server_status = ON;
            } else {
                /* ?? */        krb5_set_error_message(0, 0, "%s", ldap_err2string(st));
                server_info->server_status = OFF;
                time(&server_info->downtime);
            }
            ldap_msgfree(result);
            break;
        default:
            ldap_msgfree(result);
            continue;
            break;
        }
    }
    ldap_server_handle->server_info_update_pending = FALSE;
    return 0;
}