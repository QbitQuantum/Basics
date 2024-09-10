int l_search_ping(struct ldapsearch *s)
{
	char *attrs[2];
	struct timeval tv;
	LDAPMessage *result;
	int rc;
	int msgid;

	if (s->handle == NULL)
	{
		errno=ETIMEDOUT;  /* Timeout previously */
		return -1;
	}

	attrs[0]="objectClass";
	attrs[1]=NULL;

	tv.tv_sec=60*60;
	tv.tv_usec=0;

	if (ldap_search_ext(s->handle, s->base, LDAP_SCOPE_BASE,
			    "objectClass=*", attrs, 0, NULL, NULL, &tv,
			    1000000, &msgid) < 0)
		return -1;

	do
	{
		const char *timeout=getenv("LDAP_SEARCH_TIMEOUT");

		tv.tv_sec=atoi(timeout ? timeout:"30");
		tv.tv_usec=0;

		rc=ldap_result(s->handle, msgid, 0, &tv, &result);

		if (rc <= 0)
		{
			if (rc == 0)
				errno=ETIMEDOUT;

			ldap_unbind_ext(s->handle, NULL, NULL);
			s->handle=NULL;

			return -1;
		}

		ldap_msgfree(result);
	} while (rc != LDAP_RES_SEARCH_RESULT);
	return 0;
}