static int knp_query_resolve_srv_name(char *srv_name, unsigned long *addr_array, unsigned int *port_array,
				      int *nb_addr) {
    int error;
    int i, j;
    int used_addr = 0;
    PDNS_RECORD record_list = NULL;
    PDNS_RECORD record;
    karray srv_array;
    
    kmod_log_msg(3, "knp_query_resolve_srv_name() called.\n");
    
    karray_init(&srv_array);
    
    /* Try. */
    do {
	/* Ask Windows to resolve that. */
	error = DnsQuery_A(srv_name, 33, DNS_QUERY_STANDARD, NULL, &record_list, NULL);
	
	if (error) {
            /* No easy way to get the error string? Screw it! */
	    kmo_seterror("cannot resolve %s (error %d)", srv_name, error);
	    error = -1;
	    break;
	}
	
	/* We got the data. */
	record = record_list;
	
        /* Not using constant names since they're not all defined in my
         * environment.
         */
	while (record) {
	    
            /* 1 = DNS_TYPE_A. Resolved address. Ignore. We can't depend on it
             * being set.
             */
	    if (record->wType == 1) {
                /* void */
	    }
	    
	    /* 33 = DNS_TYPE_SRV. SRV entry. */
	    else if (record->wType == 33) {
		karray_add(&srv_array, &record->Data.SRV);
	    }
	    
	    else {
		kmo_seterror("cannot resolve %s (received unexpected DNS entry of type %d)", srv_name, record->wType);
		error = -1;
		break;
	    }
	    
	    record = record->pNext;
	}
	
	if (error) break;
	
	if (! srv_array.size) {
	    kmo_seterror("cannot resolve %s: no addresses returned", srv_name);
	    error = -1;
	    break;
	}
	
	/* Sort the SRV array. */
	qsort(srv_array.data, srv_array.size, sizeof(void *), (int (*)(const void *, const void *)) srv_entry_sort);
	
	/* Resolve each host. */
	for (i = 0; i < srv_array.size && used_addr < *nb_addr; i++) {
	    DNS_SRV_DATA *srv = (DNS_SRV_DATA *) srv_array.data[i];
	    int nb = *nb_addr - used_addr;
	    
	    error = ksock_get_host_addr_list(srv->pNameTarget, addr_array + used_addr, &nb);
	    if (error) {
		error = 0;
		continue;
	    }
	    
	    for (j = 0; j < nb; j++) {
		port_array[used_addr + j] = srv->wPort;
	    }
	    
	    used_addr += nb;
	}
	
    } while (0);
    
    /* Great API MS! Keep it up! */
    if (record_list) DnsRecordListFree(record_list, DnsFreeRecordList);
    
    karray_free(&srv_array);
    
    *nb_addr = used_addr;
    return error;
}