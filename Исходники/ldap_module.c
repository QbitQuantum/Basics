void *ldap_table_search(struct ci_lookup_table *table, void *key, void ***vals)
{
    struct ldap_table_data *data = (struct ldap_table_data *)table->data;
    LDAPMessage *msg, *entry;
    BerElement *aber;
    LDAP *ld;
    struct berval **attrs;
    void *return_value=NULL;
    char *attrname;
    int ret = 0, failures, i;
    ci_str_vector_t  *vect = NULL;
    size_t v_size;
    char filter[MAX_LDAP_FILTER_SIZE];
    char buf[2048];

    *vals = NULL;
    failures = 0;
    return_value = NULL;

    if(data->cache && ci_cache_search(data->cache, key, (void **)&vect, NULL, &ci_cache_read_vector_val)) {
        ci_debug_printf(4, "Retrieving from cache....\n");
        if (!vect) /*Negative hit*/
            return NULL;
        *vals = (void **)ci_vector_cast_to_voidvoid(vect);
        return key;
    }

    create_filter(filter, MAX_LDAP_FILTER_SIZE, data->filter,key);

    while ((ld = ldap_connection_open(data->pool)) && failures < 5) {

        ret = ldap_search_ext_s(ld,
                                data->base, /*base*/
                                LDAP_SCOPE_SUBTREE, /*scope*/
                                filter, /*filter*/
                                data->attrs,  /*attrs*/
                                0,    /*attrsonly*/
                                NULL, /*serverctrls*/
                                NULL, /*clientctrls*/
                                NULL, /*timeout*/
                                -1,   /*sizelimit*/
                                &msg /*res*/
                               );

        ci_debug_printf(4, "Contacting LDAP server: %s\n", ldap_err2string(ret));
        if(ret == LDAP_SUCCESS) {
            entry = ldap_first_entry(ld, msg);
            while(entry != NULL) {
                aber = NULL;
                attrname = ldap_first_attribute(ld, entry, &aber);
                while(attrname != NULL) {
                    if (vect == NULL) {
                        vect = ci_str_vector_create(MAX_DATA_SIZE);
                        if (!vect)
                            return NULL;
                    }

                    ci_debug_printf(8, "Retrieve attribute:%s. Values: ", attrname);
                    attrs = ldap_get_values_len(ld, entry, attrname);
                    for(i = 0; attrs[i] != NULL ; ++i) {
                        //OpenLdap nowhere documents that the result is NULL terminated.
                        // copy to an intermediate buffer and terminate it before store to vector
                        v_size = sizeof(buf) <= attrs[i]->bv_len + 1 ? sizeof(buf) : attrs[i]->bv_len;
                        memcpy(buf, attrs[i]->bv_val, v_size);
                        buf[v_size] = '\0';
                        (void)ci_str_vector_add(vect, buf);
                        ci_debug_printf(8, "%s,", buf);
                    }
                    ci_debug_printf(8, "\n");
                    ldap_value_free_len(attrs);
                    attrname = ldap_next_attribute(ld, entry, aber);
                }
                if(aber)
                    ber_free(aber, 0);

                if(!return_value)
                    return_value = key;

                entry = ldap_next_entry(ld, entry);
            }
            ldap_msgfree(msg);
            ldap_connection_release(data->pool, ld, 0);

            if(data->cache) {
                v_size =  vect != NULL ? ci_cache_store_vector_size(vect) : 0;
                ci_debug_printf(4, "adding to cache\n");
                if (!ci_cache_update(data->cache, key, vect, v_size, ci_cache_store_vector_val))
                    ci_debug_printf(4, "adding to cache failed!\n");
            }

            if (!vect)
                return NULL;

            *vals = (void **)ci_vector_cast_to_voidvoid(vect);
            return return_value;
        }

        ldap_connection_release(data->pool, ld, 1);

        if (ret != LDAP_SERVER_DOWN) {
            ci_debug_printf(1, "Error contacting LDAP server: %s\n", ldap_err2string(ret));
            return NULL;
        }

        failures++;
    }

    ci_debug_printf(1, "Error LDAP server is down: %s\n", ldap_err2string(ret));
    return NULL;
}