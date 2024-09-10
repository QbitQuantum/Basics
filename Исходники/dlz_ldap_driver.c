static isc_result_t
ldap_process_results (LDAP * dbc, LDAPMessage * msg, char **attrs, void *ptr, isc_boolean_t allnodes)
{
    isc_result_t result = ISC_R_SUCCESS;

    int i = 0;

    int j;

    int len;

    char *attribute = NULL;

    LDAPMessage *entry;

    char *endp = NULL;

    char *host = NULL;

    char *type = NULL;

    char *data = NULL;

    char **vals = NULL;

    int ttl;

    /* make sure there are at least some attributes to process. */
    REQUIRE (attrs != NULL || attrs[0] != NULL);

    /* get the first entry to process */
    entry = ldap_first_entry (dbc, msg);
    if (entry == NULL)
    {
        isc_log_write (dns_lctx, DNS_LOGCATEGORY_DATABASE,
                       DNS_LOGMODULE_DLZ, ISC_LOG_INFO, "LDAP no entries to process.");
        return (ISC_R_FAILURE);
    }

    /* loop through all entries returned */
    while (entry != NULL)
    {
        /* reset for this loop */
        ttl = 0;
        len = 0;
        i = 0;
        attribute = attrs[i];

        /* determine how much space we need for data string */
        for (j = 0; attrs[j] != NULL; j++)
        {
            /* get the list of values for this attribute. */
            vals = ldap_get_values (dbc, entry, attrs[j]);
            /* skip empty attributes. */
            if (vals == NULL || ldap_count_values (vals) < 1)
                continue;
            /*
             * we only use the first value.  this driver
             * does not support multi-valued attributes.
             */
            len = len + strlen (vals[0]) + 1;
            /* free vals for next loop */
            ldap_value_free (vals);
        }                        /* end for (j = 0; attrs[j] != NULL, j++) loop */

        /* allocate memory for data string */
        data = isc_mem_allocate (ns_g_mctx, len + 1);
        if (data == NULL)
        {
            isc_log_write (dns_lctx, DNS_LOGCATEGORY_DATABASE,
                           DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
                           "LDAP driver unable to allocate memory " "while processing results");
            result = ISC_R_FAILURE;
            goto cleanup;
        }

        /*
         * Make sure data is null termed at the beginning so
         * we can check if any data was stored to it later.
         */
        data[0] = '\0';

        /* reset j to re-use below */
        j = 0;

        /* loop through the attributes in the order specified. */
        while (attribute != NULL)
        {
            /* get the list of values for this attribute. */
            vals = ldap_get_values (dbc, entry, attribute);

            /* skip empty attributes. */
            if (vals == NULL || vals[0] == NULL)
            {
                /* increment attibute pointer */
                attribute = attrs[++i];
                /* start loop over */
                continue;
            }

            /*
             * j initially = 0.  Increment j each time we
             * set a field that way next loop will set
             * next field.
             */
            switch (j)
            {
                case 0:
                    j++;
                    /*
                     * convert text to int, make sure it
                     * worked right
                     */
                    ttl = strtol (vals[0], &endp, 10);
                    if (*endp != '\0' || ttl < 0)
                    {
                        isc_log_write (dns_lctx,
                                       DNS_LOGCATEGORY_DATABASE,
                                       DNS_LOGMODULE_DLZ, ISC_LOG_ERROR, "LDAP driver ttl must " "be a postive number");
                        goto cleanup;
                    }
                    break;
                case 1:
                    j++;
                    type = isc_mem_strdup (ns_g_mctx, vals[0]);
                    break;
                case 2:
                    j++;
                    if (allnodes == isc_boolean_true)
                    {
                        host = isc_mem_strdup (ns_g_mctx, vals[0]);
                    }
                    else
                    {
                        strcpy (data, vals[0]);
                    }
                    break;
                case 3:
                    j++;
                    if (allnodes == isc_boolean_true)
                    {
                        strcpy (data, vals[0]);
                    }
                    else
                    {
                        strcat (data, " ");
                        strcat (data, vals[0]);
                    }
                    break;
                default:
                    strcat (data, " ");
                    strcat (data, vals[0]);
                    break;
            }                    /* end switch(j) */

            /* free values */
            ldap_value_free (vals);
            vals = NULL;

            /* increment attibute pointer */
            attribute = attrs[++i];
        }                        /* end while (attribute != NULL) */

        if (type == NULL)
        {
            isc_log_write (dns_lctx, DNS_LOGCATEGORY_DATABASE,
                           DNS_LOGMODULE_DLZ, ISC_LOG_ERROR, "LDAP driver unable " "to retrieve DNS type");
            result = ISC_R_FAILURE;
            goto cleanup;
        }

        if (strlen (data) < 1)
        {
            isc_log_write (dns_lctx, DNS_LOGCATEGORY_DATABASE,
                           DNS_LOGMODULE_DLZ, ISC_LOG_ERROR, "LDAP driver unable " "to retrieve DNS data");
            result = ISC_R_FAILURE;
            goto cleanup;
        }

        if (allnodes == isc_boolean_true)
        {
            if (strcasecmp (host, "~") == 0)
                result = dns_sdlz_putnamedrr ((dns_sdlzallnodes_t *) ptr, "*", type, ttl, data);
            else
                result = dns_sdlz_putnamedrr ((dns_sdlzallnodes_t *) ptr, host, type, ttl, data);
            if (result != ISC_R_SUCCESS)
                isc_log_write (dns_lctx,
                               DNS_LOGCATEGORY_DATABASE,
                               DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
                               "dlz-ldap: putnamedrr failed "
                               "for \"%s %s %u %s\", %s", host, type, ttl, data, isc_result_totext (result));
        }
        else
        {
            result = dns_sdlz_putrr ((dns_sdlzlookup_t *) ptr, type, ttl, data);
            if (result != ISC_R_SUCCESS)
                isc_log_write (dns_lctx,
                               DNS_LOGCATEGORY_DATABASE,
                               DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
                               "dlz-ldap: putrr failed "
                               "for \"%s %u %s\", %s", type, ttl, data, isc_result_totext (result));
        }

        if (result != ISC_R_SUCCESS)
        {
            isc_log_write (dns_lctx, DNS_LOGCATEGORY_DATABASE,
                           DNS_LOGMODULE_DLZ, ISC_LOG_ERROR, "LDAP driver failed " "while sending data to BIND.");
            goto cleanup;
        }

        /* free memory for type, data and host for next loop */
        isc_mem_free (ns_g_mctx, type);
        isc_mem_free (ns_g_mctx, data);
        if (host != NULL)
            isc_mem_free (ns_g_mctx, host);

        /* get the next entry to process */
        entry = ldap_next_entry (dbc, entry);
    }                            /* end while (entry != NULL) */

  cleanup:
    /* de-allocate memory */
    if (vals != NULL)
        ldap_value_free (vals);
    if (host != NULL)
        isc_mem_free (ns_g_mctx, host);
    if (type != NULL)
        isc_mem_free (ns_g_mctx, type);
    if (data != NULL)
        isc_mem_free (ns_g_mctx, data);

    return (result);
}