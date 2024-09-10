/**
 * compare attribute to LDAP in case of LDAP_INAPPROPRIATE_MATCHING
 *
 * \param ld AddressBook resource
 * \param server Reference to server
 * \param dn dn for the entry
 * \param attr Attribute
 * \param value New value
 * \return int, return will be LDAP_MOD_ADD, LDAP_MOD_REPLACE, or LDAP_MOD_DELETE
 */
int ldapsvr_compare_manual_attr(LDAP *ld, LdapServer *server, gchar *dn, char *attr, char *value) {
    LDAPMessage *res, *e = NULL;
    BerElement *ber;
    struct berval **vals;
    int rc;
    LdapControl *ctl;
    gchar *filter;
    gchar *attribute;
    int retVal = -2, i;
    AttrKeyValue *mail;

    cm_return_val_if_fail(ld != NULL || server != NULL || attr != NULL, -1);
    ctl = server->control;
    mail = get_mail(dn);
    if (! mail)
        return -2;
    filter = g_strdup_printf("(&(mail=%s)(%s=*))", mail->value, attr);
    attrkeyvalue_free(mail);
    if (ctl) {

        rc = ldap_search_ext_s(ld, ctl->baseDN, LDAP_SCOPE_ONELEVEL, filter, NULL, 0, NULL, NULL, NULL, 0, &res);

        if (rc) {
            g_printerr("ldap_search for attr=%s\" failed[0x%x]: %s\n",attr, rc, ldaputil_get_error(ld));
            retVal = -2;
        }
        else {
            e = ldap_first_entry(ld, res);
            /* entry has this attribute */
            if (e) {
                attribute = ldap_first_attribute( ld, e, &ber );
                if (attribute) {
                    if (value) {
                        if( ( vals = ldap_get_values_len( ld, e, attr ) ) != NULL ) {
                            for( i = 0; vals[i] != NULL; i++ ) {
                                debug_print("Compare: %s=%s\n", attr, vals[i]->bv_val);
                                /* attribute has same value */
                                if (strcmp(vals[i]->bv_val, value) == 0)
                                    retVal = -1;
                                /* attribute has new value */
                                else
                                    retVal = LDAP_MOD_REPLACE;
                            }
                        }
                        ldap_value_free_len(vals);
                    }
                    else
                        retVal = LDAP_MOD_DELETE;
                }
                if( ber != NULL ) {
                    ber_free( ber, 0 );
                }
                ldap_memfree(attribute);
            }
            /* entry does not have this attribute */
            else {
                /* Only add if this is a real attribute */
                if (value)
                    retVal = LDAP_MOD_ADD;
                /* This is dummy value used to avoid ldap_compare error */
                else
                    retVal = -1;
            }
        }
    }
    else
        retVal = -2;
    g_free(filter);
    return retVal;
}