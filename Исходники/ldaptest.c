void run_ldap_tests(service_t *ldaptest, int sslcertcheck, int querytimeout)
{
#ifdef HAVE_LDAP
	ldap_data_t *req;
	testitem_t *t;
	struct timespec starttime;
	struct timespec endtime;

	/* Pick a sensible default for the timeout setting */
	if (querytimeout == 0) querytimeout = 30;

	for (t = ldaptest->items; (t); t = t->next) {
		LDAPURLDesc	*ludp;
		LDAP		*ld;
		int		rc, finished;
		int		msgID = -1;
		struct timeval	ldaptimeout;
		struct timeval	openldaptimeout;
		LDAPMessage	*result;
		LDAPMessage	*e;
		strbuffer_t	*response;
		char		buf[MAX_LINE_LEN];

		req = (ldap_data_t *) t->privdata;
		if (req->skiptest) continue;

		ludp = (LDAPURLDesc *) req->ldapdesc;

		getntimer(&starttime);

		/* Initiate session with the LDAP server */
		dbgprintf("Initiating LDAP session for host %s port %d\n",
			ludp->lud_host, ludp->lud_port);

		if( (ld = ldap_init(ludp->lud_host, ludp->lud_port)) == NULL ) {
			dbgprintf("ldap_init failed\n");
			req->ldapstatus = XYMON_LDAP_INITFAIL;
			continue;
		}

		/* 
		 * There is apparently no standard way of defining a network
		 * timeout for the initial connection setup. 
		 */
#if (LDAP_VENDOR == OpenLDAP) && defined(LDAP_OPT_NETWORK_TIMEOUT)
		/* 
		 * OpenLDAP has an undocumented ldap_set_option(ld, LDAP_OPT_NETWORK_TIMEOUT, &tv)
		 */
		openldaptimeout.tv_sec = querytimeout;
		openldaptimeout.tv_usec = 0;
		ldap_set_option(ld, LDAP_OPT_NETWORK_TIMEOUT, &openldaptimeout);
#else
		/*
		 * So using an alarm() to interrupt any pending operations
		 * seems to be the least insane way of doing this.
		 *
		 * Note that we must do this right after ldap_init(), as
		 * any operation on the session handle (ld) may trigger the
		 * network connection to be established.
		 */
		connect_timeout = 0;
		signal(SIGALRM, ldap_alarmhandler);
		alarm(querytimeout);
#endif

		/*
		 * This is completely undocumented in the OpenLDAP docs.
		 * But apparently it is documented in 
		 * http://www.ietf.org/proceedings/99jul/I-D/draft-ietf-ldapext-ldap-c-api-03.txt
		 *
		 * Both of these routines appear in the <ldap.h> file 
		 * from OpenLDAP 2.1.22. Their use to enable TLS has
		 * been deciphered from the ldapsearch() utility
		 * sourcecode.
		 *
		 * According to Manon Goo <*****@*****.**>, recent (Jan. 2005)
		 * OpenLDAP implementations refuse to talk LDAPv2.
		 */
#ifdef LDAP_OPT_PROTOCOL_VERSION 
		{
			int protocol = LDAP_VERSION3;

			dbgprintf("Attempting to select LDAPv3\n");
			if ((rc = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &protocol)) != LDAP_SUCCESS) {
				dbgprintf("Failed to select LDAPv3, trying LDAPv2\n");
				protocol = LDAP_VERSION2;
				if ((rc = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &protocol)) != LDAP_SUCCESS) {
					req->output = strdup(ldap_err2string(rc));
					req->ldapstatus = XYMON_LDAP_TLSFAIL;
				}
				continue;
			}
		}
#endif

		if (req->usetls) {
			dbgprintf("Trying to enable TLS for session\n");
			if ((rc = ldap_start_tls_s(ld, NULL, NULL)) != LDAP_SUCCESS) {
				dbgprintf("ldap_start_tls failed\n");
				req->output = strdup(ldap_err2string(rc));
				req->ldapstatus = XYMON_LDAP_TLSFAIL;
				continue;
			}
		}

		if (!connect_timeout) {
			msgID = ldap_simple_bind(ld, (t->host->ldapuser ? t->host->ldapuser : ""), 
					 (t->host->ldappasswd ? t->host->ldappasswd : ""));
		}

		/* Cancel any pending alarms */
		alarm(0);
		signal(SIGALRM, SIG_DFL);

		/* Did we connect? */
		if (connect_timeout || (msgID == -1)) {
			req->ldapstatus = XYMON_LDAP_BINDFAIL;
			req->output = "Cannot connect to server";
			continue;
		}

		/* Wait for bind to complete */
		rc = 0; finished = 0; 
		ldaptimeout.tv_sec = querytimeout;
		ldaptimeout.tv_usec = 0L;
		while( ! finished ) {
			int rc2;

			rc = ldap_result(ld, msgID, LDAP_MSG_ONE, &ldaptimeout, &result);
			dbgprintf("ldap_result returned %d for ldap_simple_bind()\n", rc);
			if(rc == -1) {
				finished = 1;
				req->ldapstatus = XYMON_LDAP_BINDFAIL;

				if (result == NULL) {
					errprintf("LDAP library problem - NULL result returned\n");
					req->output = strdup("LDAP BIND failed\n");
				}
				else {
					rc2 = ldap_result2error(ld, result, 1);
					req->output = strdup(ldap_err2string(rc2));
				}
				ldap_unbind(ld);
			}
			else if (rc == 0) {
				finished = 1;
				req->ldapstatus = XYMON_LDAP_BINDFAIL;
				req->output = strdup("Connection timeout");
				ldap_unbind(ld);
			}
			else if( rc > 0 ) {
				finished = 1;
				if (result == NULL) {
					errprintf("LDAP library problem - got a NULL resultcode for status %d\n", rc);
					req->ldapstatus = XYMON_LDAP_BINDFAIL;
					req->output = strdup("LDAP library problem: ldap_result2error returned a NULL result for status %d\n");
					ldap_unbind(ld);
				}
				else {
					rc2 = ldap_result2error(ld, result, 1);
					if(rc2 != LDAP_SUCCESS) {
						req->ldapstatus = XYMON_LDAP_BINDFAIL;
						req->output = strdup(ldap_err2string(rc));
						ldap_unbind(ld);
					}
				}
			}
		} /* ... while() */

		/* We're done connecting. If something went wrong, go to next query. */
		if (req->ldapstatus != 0) continue;

		/* Now do the search. With a timeout */
		ldaptimeout.tv_sec = querytimeout;
		ldaptimeout.tv_usec = 0L;
		rc = ldap_search_st(ld, ludp->lud_dn, ludp->lud_scope, ludp->lud_filter, ludp->lud_attrs, 0, &ldaptimeout, &result);

		if(rc == LDAP_TIMEOUT) {
			req->ldapstatus = XYMON_LDAP_TIMEOUT;
			req->output = strdup(ldap_err2string(rc));
	  		ldap_unbind(ld);
			continue;
		}
		if( rc != LDAP_SUCCESS ) {
			req->ldapstatus = XYMON_LDAP_SEARCHFAILED;
			req->output = strdup(ldap_err2string(rc));
	  		ldap_unbind(ld);
			continue;
		}

		getntimer(&endtime);

		response = newstrbuffer(0);
		sprintf(buf, "Searching LDAP for %s yields %d results:\n\n", 
			t->testspec, ldap_count_entries(ld, result));
		addtobuffer(response, buf);

		for(e = ldap_first_entry(ld, result); (e != NULL); e = ldap_next_entry(ld, e) ) {
			char 		*dn;
			BerElement	*ber;
			char		*attribute;
			char		**vals;

			dn = ldap_get_dn(ld, e);
			sprintf(buf, "DN: %s\n", dn); 
			addtobuffer(response, buf);

			/* Addtributes and values */
			for (attribute = ldap_first_attribute(ld, e, &ber); (attribute != NULL); attribute = ldap_next_attribute(ld, e, ber) ) {
				if ((vals = ldap_get_values(ld, e, attribute)) != NULL) {
					int i;

					for(i = 0; (vals[i] != NULL); i++) {
						sprintf(buf, "\t%s: %s\n", attribute, vals[i]);
						addtobuffer(response, buf);
					}
				}
				/* Free memory used to store values */
				ldap_value_free(vals);
			}

			/* Free memory used to store attribute */
			ldap_memfree(attribute);
			ldap_memfree(dn);
			if (ber != NULL) ber_free(ber, 0);

			addtobuffer(response, "\n");
		}
		req->ldapstatus = XYMON_LDAP_OK;
		req->output = grabstrbuffer(response);
		tvdiff(&starttime, &endtime, &req->duration);

		ldap_msgfree(result);
		ldap_unbind(ld);
		ldap_free_urldesc(ludp);
	}
#endif
}