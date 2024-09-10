/*
 * delete a principal from the directory.
 */
krb5_error_code
krb5_ldap_delete_principal(krb5_context context,
                           krb5_const_principal searchfor)
{
    char                      *user=NULL, *DN=NULL, *strval[10] = {NULL};
    LDAPMod                   **mods=NULL;
    LDAP                      *ld=NULL;
    int                       j=0, ptype=0, pcount=0, attrsetmask=0;
    krb5_error_code           st=0;
    krb5_boolean              singleentry=FALSE;
    KEY                       *secretkey=NULL;
    kdb5_dal_handle           *dal_handle=NULL;
    krb5_ldap_context         *ldap_context=NULL;
    krb5_ldap_server_handle   *ldap_server_handle=NULL;
    krb5_db_entry             *entry = NULL;

    /* Clear the global error string */
    krb5_clear_error_message(context);

    SETUP_CONTEXT();
    /* get the principal info */
    if ((st=krb5_ldap_get_principal(context, searchfor, 0, &entry)))
        goto cleanup;

    if (((st=krb5_get_princ_type(context, entry, &(ptype))) != 0) ||
        ((st=krb5_get_attributes_mask(context, entry, &(attrsetmask))) != 0) ||
        ((st=krb5_get_princ_count(context, entry, &(pcount))) != 0) ||
        ((st=krb5_get_userdn(context, entry, &(DN))) != 0))
        goto cleanup;

    if (DN == NULL) {
        st = EINVAL;
        krb5_set_error_message(context, st, "DN information missing");
        goto cleanup;
    }

    GET_HANDLE();

    if (ptype == KDB_STANDALONE_PRINCIPAL_OBJECT) {
        st = ldap_delete_ext_s(ld, DN, NULL, NULL);
        if (st != LDAP_SUCCESS) {
            st = set_ldap_error (context, st, OP_DEL);
            goto cleanup;
        }
    } else {
        if (((st=krb5_unparse_name(context, searchfor, &user)) != 0)
            || ((st=krb5_ldap_unparse_principal_name(user)) != 0))
            goto cleanup;

        memset(strval, 0, sizeof(strval));
        strval[0] = user;
        if ((st=krb5_add_str_mem_ldap_mod(&mods, "krbprincipalname", LDAP_MOD_DELETE,
                                          strval)) != 0)
            goto cleanup;

        singleentry = (pcount == 1) ? TRUE: FALSE;
        if (singleentry == FALSE) {
            if (secretkey != NULL) {
                if ((st=krb5_add_ber_mem_ldap_mod(&mods, "krbprincipalkey", LDAP_MOD_DELETE | LDAP_MOD_BVALUES,
                                                  secretkey->keys)) != 0)
                    goto cleanup;
            }
        } else {
            /*
             * If the Kerberos user principal to be deleted happens to be the last one associated
             * with the directory user object, then it is time to delete the other kerberos
             * specific attributes like krbmaxticketlife, i.e, unkerberize the directory user.
             * From the attrsetmask value, identify the attributes set on the directory user
             * object and delete them.
             * NOTE: krbsecretkey attribute has per principal entries. There can be chances that the
             * other principals' keys are exisiting/left-over. So delete all the values.
             */
            while (attrsetmask) {
                if (attrsetmask & 1) {
                    if ((st=krb5_add_str_mem_ldap_mod(&mods, attributes_set[j], LDAP_MOD_DELETE,
                                                      NULL)) != 0)
                        goto cleanup;
                }
                attrsetmask >>= 1;
                ++j;
            }

            /* the same should be done with the objectclass attributes */
            {
                char *attrvalues[] = {"krbticketpolicyaux", "krbprincipalaux", NULL};
/*              char *attrvalues[] = {"krbpwdpolicyrefaux", "krbticketpolicyaux", "krbprincipalaux", NULL};  */
                int p, q, r=0, amask=0;

                if ((st=checkattributevalue(ld, DN, "objectclass", attrvalues, &amask)) != 0)
                    goto cleanup;
                memset(strval, 0, sizeof(strval));
                for (p=1, q=0; p<=4; p<<=1, ++q)
                    if (p & amask)
                        strval[r++] = attrvalues[q];
                strval[r] = NULL;
                if (r > 0) {
                    if ((st=krb5_add_str_mem_ldap_mod(&mods, "objectclass", LDAP_MOD_DELETE,
                                                      strval)) != 0)
                        goto cleanup;
                }
            }
        }
        st=ldap_modify_ext_s(ld, DN, mods, NULL, NULL);
        if (st != LDAP_SUCCESS) {
            st = set_ldap_error(context, st, OP_MOD);
            goto cleanup;
        }
    }

cleanup:
    if (user)
        free (user);

    if (DN)
        free (DN);

    if (secretkey != NULL) {
        int i=0;
        while (i < secretkey->nkey) {
            free (secretkey->keys[i]->bv_val);
            free (secretkey->keys[i]);
            ++i;
        }
        free (secretkey->keys);
        free (secretkey);
    }

    krb5_ldap_free_principal(context, entry);

    ldap_mods_free(mods, 1);
    krb5_ldap_put_handle_to_pool(ldap_context, ldap_server_handle);
    return st;
}