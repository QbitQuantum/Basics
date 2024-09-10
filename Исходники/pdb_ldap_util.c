static NTSTATUS add_new_domain_info(struct smbldap_state *ldap_state,
                                    const char *domain_name)
{
    fstring sid_string;
    fstring algorithmic_rid_base_string;
    char *filter = NULL;
    char *dn = NULL;
    LDAPMod **mods = NULL;
    int rc;
    LDAPMessage *result = NULL;
    int num_result;
    const char **attr_list;
    char *escape_domain_name;

    /* escape for filter */
    escape_domain_name = escape_ldap_string(talloc_tos(), domain_name);
    if (!escape_domain_name) {
        DEBUG(0, ("Out of memory!\n"));
        return NT_STATUS_NO_MEMORY;
    }

    if (asprintf(&filter, "(&(%s=%s)(objectclass=%s))",
                 get_attr_key2string(dominfo_attr_list, LDAP_ATTR_DOMAIN),
                 escape_domain_name, LDAP_OBJ_DOMINFO) < 0) {
        TALLOC_FREE(escape_domain_name);
        return NT_STATUS_NO_MEMORY;
    }

    TALLOC_FREE(escape_domain_name);

    attr_list = get_attr_list(NULL, dominfo_attr_list );
    rc = smbldap_search_suffix(ldap_state, filter, attr_list, &result);
    TALLOC_FREE( attr_list );
    SAFE_FREE(filter);

    if (rc != LDAP_SUCCESS) {
        return NT_STATUS_UNSUCCESSFUL;
    }

    num_result = ldap_count_entries(ldap_state->ldap_struct, result);

    if (num_result > 1) {
        DEBUG (0, ("add_new_domain_info: More than domain with that name exists: bailing "
                   "out!\n"));
        ldap_msgfree(result);
        return NT_STATUS_UNSUCCESSFUL;
    }

    /* Check if we need to add an entry */
    DEBUG(3,("add_new_domain_info: Adding new domain\n"));

    /* this time escape for DN */
    escape_domain_name = escape_rdn_val_string_alloc(domain_name);
    if (!escape_domain_name) {
        DEBUG(0, ("Out of memory!\n"));
        return NT_STATUS_NO_MEMORY;
    }

    if (asprintf(&dn, "%s=%s,%s",
                 get_attr_key2string(dominfo_attr_list, LDAP_ATTR_DOMAIN),
                 escape_domain_name, lp_ldap_suffix(talloc_tos())) < 0) {
        SAFE_FREE(escape_domain_name);
        return NT_STATUS_NO_MEMORY;
    }

    SAFE_FREE(escape_domain_name);

    /* Free original search */
    ldap_msgfree(result);

    /* make the changes - the entry *must* not already have samba
     * attributes */

    smbldap_set_mod(&mods, LDAP_MOD_ADD,
                    get_attr_key2string(dominfo_attr_list,
                                        LDAP_ATTR_DOMAIN),
                    domain_name);

    /* If we don't have an entry, then ask secrets.tdb for what it thinks.
       It may choose to make it up */

    sid_to_fstring(sid_string, get_global_sam_sid());
    smbldap_set_mod(&mods, LDAP_MOD_ADD,
                    get_attr_key2string(dominfo_attr_list,
                                        LDAP_ATTR_DOM_SID),
                    sid_string);

    slprintf(algorithmic_rid_base_string,
             sizeof(algorithmic_rid_base_string) - 1, "%i",
             algorithmic_rid_base());
    smbldap_set_mod(&mods, LDAP_MOD_ADD,
                    get_attr_key2string(dominfo_attr_list,
                                        LDAP_ATTR_ALGORITHMIC_RID_BASE),
                    algorithmic_rid_base_string);
    smbldap_set_mod(&mods, LDAP_MOD_ADD, "objectclass", LDAP_OBJ_DOMINFO);

    /* add the sambaNextUserRid attributes. */

    {
        uint32 rid = BASE_RID;
        fstring rid_str;

        fstr_sprintf( rid_str, "%i", rid );
        DEBUG(10,("add_new_domain_info: setting next available user rid [%s]\n", rid_str));
        smbldap_set_mod(&mods, LDAP_MOD_ADD,
                        get_attr_key2string(dominfo_attr_list,
                                            LDAP_ATTR_NEXT_USERRID),
                        rid_str);
    }


    rc = smbldap_add(ldap_state, dn, mods);

    if (rc!=LDAP_SUCCESS) {
        char *ld_error = NULL;
        ldap_get_option(ldap_state->ldap_struct,
                        LDAP_OPT_ERROR_STRING, &ld_error);
        DEBUG(1,("add_new_domain_info: failed to add domain dn= %s with: %s\n\t%s\n",
                 dn, ldap_err2string(rc),
                 ld_error?ld_error:"unknown"));
        SAFE_FREE(ld_error);
        SAFE_FREE(dn);
        ldap_mods_free(mods, True);
        return NT_STATUS_UNSUCCESSFUL;
    }

    DEBUG(2,("add_new_domain_info: added: domain = %s in the LDAP database\n", domain_name));
    ldap_mods_free(mods, True);
    SAFE_FREE(dn);
    return NT_STATUS_OK;
}