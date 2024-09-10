/* 
 * auparse library callback that's called when an event is ready
 */
void
push_event(auparse_state_t * au, auparse_cb_event_t cb_event_type,
           void *user_data)
{
        int rc;
        BerElement *ber;
        int qualifier;
        char timestamp[26];
        char linkValue[ZOS_REMOTE_LINK_VALUE_SIZE];
        char logString[ZOS_REMOTE_LOGSTRING_SIZE];
        unsigned long linkValue_tmp;

        if (cb_event_type != AUPARSE_CB_EVENT_READY)
                return;
                
        const au_event_t *e = auparse_get_timestamp(au);
        if (e == NULL)
                return;
        /*
         * we have an event. Each record will result in a different 'Item'
         * (refer ASN.1 definition in zos-remote-ldap.h) 
         */
        
        /*
         * Create a new BER element to encode the request
         */
        ber = ber_alloc_t(LBER_USE_DER);
        if (ber == NULL) {
            log_err("Error allocating memory for BER element");
            goto fatal;
        }

        /*
         * Collect some information to fill in every item
         */
        const char *node = auparse_get_node(au);
        const char *orig_type = auparse_find_field(au, "type");
        /* roll back event to get 'success' */
        auparse_first_record(au);
        const char *success = auparse_find_field(au, "success");
        /* roll back event to get 'res' */
        auparse_first_record(au);
        const char *res = auparse_find_field(au, "res");
        
        /* check if this event is a success or failure one */
        if (success) {
                if (strncmp(success, "0", 1) == 0 ||
                    strncmp(success, "no", 2) == 0)
                        qualifier = ZOS_REMOTE_QUALIF_FAIL;
                else
                        qualifier = ZOS_REMOTE_QUALIF_SUCCESS;
        } else if (res) {
                if (strncmp(res, "0", 1) == 0
                    || strncmp(res, "failed", 6) == 0)
                        qualifier = ZOS_REMOTE_QUALIF_FAIL;
                else
                        qualifier = ZOS_REMOTE_QUALIF_SUCCESS;
        } else
                qualifier = ZOS_REMOTE_QUALIF_INFO;
                
        /* get timestamp text */
        ctime_r(&e->sec, timestamp);
        timestamp[24] = '\0';    /* strip \n' */
        
        /* prepare linkValue which will be used for every item */
        linkValue_tmp = htonl(e->serial);        /* padronize to use network
                                                  * byte order 
                                                  */
        memset(&linkValue, 0, ZOS_REMOTE_LINK_VALUE_SIZE);
        memcpy(&linkValue, &linkValue_tmp, sizeof(unsigned long));        

        /* 
         * Prepare the logString with some meaningful text
         * We assume the first record type found is the
         * 'originating' audit record
         */
        sprintf(logString, "Linux (%s): type: %s", node, orig_type);

        /* 
         * Start writing to BER element.
         * There's only one field (version) out of the item sequence.
         * Also open item sequence
         */
        rc = ber_printf(ber, "{i{", ICTX_REQUESTVER);
        if (rc < 0)
                goto skip_event;

        /* 
         * Roll back to first record and iterate through all records
         */
        auparse_first_record(au);
        do {
                const char *type = auparse_find_field(au, "type");
                if (type == NULL)
                        goto skip_event;
                
                log_debug("got record: %s", auparse_get_record_text(au));

                /* 
                 * First field is item Version, same as global version
                 */
                rc = ber_printf(ber, "{i", ICTX_REQUESTVER);

                /*
                 * Second field is the itemTag
                 * use our internal event counter, increasing it
                 */
                rc |= ber_printf(ber, "i", conf.counter++);

                /*
                 * Third field is the linkValue
                 * using ber_put_ostring since it is not null-terminated
                 */
                rc |= ber_put_ostring(ber, linkValue,
                                      ZOS_REMOTE_LINK_VALUE_SIZE,
                                      LBER_OCTETSTRING);
                /*
                 * Fourth field is the violation
                 * Don't have anything better yet to put here
                 */
                rc |= ber_printf(ber, "b", 0);
                
                /* 
                 * Fifth field is the event.
                 * FIXME: this might be the place to switch on the
                 * audit record type and map to a more meaningful
                 * SMF type 83, subtype 4 event here
                 */
                rc |= ber_printf(ber, "i", ZOS_REMOTE_EVENT_AUTHORIZATION);
                
                /*
                 * Sixth field is the qualifier. We map 'success' or
                 * 'res' to this field
                 */
                rc |= ber_printf(ber, "i", qualifier);
                
                /* 
                 * Seventh field is the Class
                 * always use '@LINUX' for this version
                 * max size ZOS_REMOTE_CLASS_SIZE
                 */
                rc |= ber_printf(ber, "t", ASN1_IA5STRING_TAG);
                rc |= ber_printf(ber, "s", "@LINUX");
                
                /* 
                 * Eighth field is the resource
                 * use the record type (name) as the resource
                 * max size ZOS_REMOTE_RESOURCE_SIZE
                 */
                rc |= ber_printf(ber, "t", ASN1_IA5STRING_TAG);
                rc |= ber_printf(ber, "s", type);
                
                /* 
                 * Nineth field is the LogString
                 * we try to put something meaningful here
                 * we also start the relocations sequence
                 */
                rc |= ber_printf(ber, "t", ASN1_IA5STRING_TAG);
                rc |= ber_printf(ber, "s{", logString);

                /*
                 * Now we start adding the relocations.
                 * Let's add the timestamp as the first one
                 * so it's out of the field loop
                 */
                rc |= ber_printf(ber, "{i", ZOS_REMOTE_RELOC_TIMESTAMP);
                rc |= ber_printf(ber, "t", ASN1_IA5STRING_TAG);
                rc |= ber_printf(ber, "s}", timestamp);

                /* 
                 * Check that encoding is going OK until now
                 */
                if (rc < 0)
                        goto skip_event;

                /* 
                 * Now go to first field,
                 * and iterate through all fields
                 */
                auparse_first_field(au);
                do {
                        /* 
                         * we set a maximum of 1024 chars for
                         * relocation data (field=value pairs)
                         * Hopefuly this wont overflow too often
                         */
                        char data[1024];
                        const char *name = auparse_get_field_name(au);
                        const char *value = auparse_interpret_field(au);
                        if (name == NULL || value == NULL)
                                goto skip_event;
                        
                        /*
                         * First reloc field is the Relocation type
                         * We use 'OTHER' here since we don't have
                         * anything better
                         */
                        rc |= ber_printf(ber, "{i", ZOS_REMOTE_RELOC_OTHER);
                        
                        /*
                         * Second field is the relocation data
                         * We use a 'name=value' pair here
                         * Use up to 1023 chars (one char left for '\0')
                         */
                        snprintf(data, 1023, "%s=%s", name, value);
                        rc |= ber_printf(ber, "t", ASN1_IA5STRING_TAG);
                        rc |= ber_printf(ber, "s}", data);
                        
                        /*
                         * Check encoding status
                         */
                        if (rc < 0)
                                goto skip_event;
                } while (auparse_next_field(au) > 0);
                
                /* 
                 * After adding all relocations we are done with
                 * this item - finalize relocs and item 
                 */
                rc |= ber_printf(ber, "}}");
                
                /*
                 * Check if we are doing well with encoding
                 */
                if (rc < 0)
                        goto skip_event;            

        } while (auparse_next_record(au) > 0);
        
        /*
         * We have all items in - finalize item sequence & request
         */
        rc |= ber_printf(ber, "}}");

        /*
         * Check if everything went alright with encoding
         */
        if (rc < 0)
                goto skip_event;

        /* 
         * finally, enqueue request and let the other
         * thread process it
         */
        log_debug("Encoding done, enqueuing event");
        enqueue(ber);

        return;
        
skip_event:
        log_warn("Warning - error encoding request, skipping event");
        ber_free(ber, 1);        /* free it since we're not enqueuing it */
        return;

fatal:
        log_err("Error - Fatal error while encoding request. Aborting");
        stop = 1;
}