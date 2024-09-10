/** 
 * Should be called on an event requiring an ldap search, 
 * will return an slack_ldap_event_t struct. The event 
 * struct will provide all the necessary information 
 * and pointers to relevant information. The function 
 * itself uses the ldap_query_t tree to make a series 
 * of ldap searches to find out information about the 
 * nick provided, or the lack of it. 
 */
void
slack_ldap_search(const char *qval) { 
    slack_ldap_query_t *shead = &head; //Local searches event head 
       
    while(shead->next != NULL) { 
        LDAPMessage *result; 
        syslog(LOG_INFO, "Performing ldap search for %s", qval); 

        char newfilter[strlen(shead->filterstr) + strlen(qval)]; 
        sprintf(newfilter, shead->filterstr, qval); 

        int search_status = ldap_search_ext_s(
                ldap, shead->basednstr, LDAP_SCOPE_SUBTREE, newfilter, NULL, 
                0, NULL, NULL, &timeout, 1, &result);
        syslog(LOG_INFO, "Search Status: %s", ldap_err2string(search_status));
        //if(search_status != LDAP_SUCCESS) { return; } // We should probably die 

        syslog(LOG_INFO, "Parsing ldap search result"); 
    
        LDAPMessage *entry = ldap_first_entry(ldap, result); 
        char *attribute; 
        BerElement *ber; 
        char **vals; 
        int i;
        if(entry != NULL) { 
            syslog(LOG_INFO, "Found LDAP Entry..."); 
            /* For each attribute of the entry that has been parsed */
            for(attribute = ldap_first_attribute(ldap, entry, &ber); 
                    attribute != NULL; // if NULL then we are at the end
                    attribute = ldap_next_attribute(ldap, entry, ber)) {
                /* For each attribute print the attribute name and values */ 
                if ((vals = ldap_get_values(ldap, entry, attribute)) != NULL) { 
                    for(i=0; vals[i] != NULL; i++) { 
                        syslog(LOG_INFO, "FOUND VALUE %s: %s", attribute, vals[i]); 
                        /* We now have to call the ldap event, which allows the 
                        * custom handling from the configuration. */ 
                    }
                    ldap_value_free(vals); // MY 
                }
                ldap_memfree(attribute); // GOD
            }
            if(ber != NULL) { 
                ber_free(ber, 0); // MEMLEAK
            }
        }
        ldap_msgfree(result); // AVERTED

        /* Iterate through to the next ldap search event */ 
        shead = shead->next; 
    } // End While 
}          