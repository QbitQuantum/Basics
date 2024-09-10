static struct PCP_new_eventid *readnewevent(struct PCP *pcp)
{
	struct PCP_save_event se;
	struct readnewevent_s rne;
	struct PCP_new_eventid *ne;
	const char *cp;
	struct proxy_list *p;
	int first_save=1;

	if (!deleted_eventid)
		proxy_list_rset();

	/* Open new proxy connections */

	while ((cp=strtok(NULL, " ")) != NULL)
	{
		char *errmsg, *q;
		char *n=strdup(cp);
		struct proxy_list *pcp;

		if (!n)
		{
			syslog(LOG_ALERT, "Out of memory.");
			exit(1);
		}

		if (proxy_userid)
		{
			printf("500-Cannot create proxy in proxy mode.\n");
			free(n);
			errno=EIO;
			return (NULL);
		}

		strcpy(n, cp);
		pcp=proxy(n, &errmsg);

		if (pcp)
		{
			pcp->flags |= PROXY_NEW;
			free(n);
			continue;
		}

		if (force_flag)
		{
			pcp->flags |= PROXY_IGNORE;
			free(n);
			continue;
		}

		while (errmsg && (q=strchr(errmsg, '\n')) != 0)
			*q='/';
		printf("500-%s: %s\n", n, errmsg ? errmsg:"Failed to create a proxy connection.");
		free(n);
		proxy_list_rset();
		return (NULL);
	}

	memset(&se, 0, sizeof(se));
	if ((rne.tmpfile=tmpfile()) == NULL)
		return (NULL);
	time(&rne.last_noop_time);

	rne.seeneol=1;
	rne.seendot=0;
	rne.seeneof=0;
	rne.cnt=0;
	rne.pcp=pcp;
	pcpdtimer_init(&rne.inactivity_timeout);
	rne.inactivity_timeout.handler=&inactive;
	pcpdtimer_install(&rne.inactivity_timeout, 300);

	for (p=proxy_list; p; p=p->next)
	{
		struct PCP_save_event se;

		if ( !(p->flags & PROXY_NEW))
			continue;

		if (fseek(rne.tmpfile, 0L, SEEK_SET) < 0
		    || lseek(fileno(rne.tmpfile), 0L, SEEK_SET) < 0)
		{
			int save_errno=errno;
			proxy_list_rset();
			pcpdtimer_triggered(&rne.inactivity_timeout);
			fclose(rne.tmpfile);
			errno=save_errno;
			return (NULL);
		}

		memset(&se, 0, sizeof(se));
		if (first_save)
		{
			se.write_event_func_misc_ptr= &rne;
			se.write_event_func=readnewevent_callback;
		}
		else
			se.write_event_fd=fileno(rne.tmpfile);

		if ((p->newevent=pcp_new_eventid(p->proxy,
						 p->old_event_id,
						 &se)) == NULL)
		{
			pcpdtimer_triggered(&rne.inactivity_timeout);

			if (force_flag)
			{
				/* Force it through */

				p->flags &= ~PROXY_NEW;
				p->flags |= PROXY_IGNORE;
				continue;
			}

			proxy_error(p->userid,
				    pcp_errmsg(p->proxy));
			proxy_list_rset();
			fclose(rne.tmpfile);
			errno=EIO;
			return (NULL);
		}
		if (first_save)
			pcpdtimer_triggered(&rne.inactivity_timeout);
		first_save=0;
	}


	if (first_save)
	{
		se.write_event_func_misc_ptr= &rne;
		se.write_event_func=readnewevent_callback;
	}
	else
		se.write_event_fd=fileno(rne.tmpfile);

	if (mkparticipants(&se) || fseek(rne.tmpfile, 0L, SEEK_SET) < 0
	    || lseek(fileno(rne.tmpfile), 0L, SEEK_SET) < 0)
	{
		int save_errno=errno;

		proxy_list_rset();
		fclose(rne.tmpfile);
		errno=save_errno;
		return (NULL);
	}

	if ((ne=pcp_new_eventid(pcp, deleted_eventid, &se)) == NULL)
	{
		while (!rne.seeneof)
		{
			char buf[512];

			readnewevent_callback(buf, sizeof(buf), &se);
		}
	}
	pcpdtimer_triggered(&rne.inactivity_timeout);
	if (first_save)
	{
		if (fflush(rne.tmpfile) || ferror(rne.tmpfile))
		{
			int save_errno=errno;

			proxy_list_rset();
			fclose(rne.tmpfile);
			errno=save_errno;
			return (NULL);
		}
	}

	notbooked=1;
	fclose(rne.tmpfile);
	return (ne);
}