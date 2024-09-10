int
qldap_get_dn(qldap *q, stralloc *dn)
{
	char *d;
	
	CHECK(q, EXTRACT);

	d = ldap_get_dn(q->ld, q->msg);
	if (d == (char *)0)
		return NOSUCH;
	if (!stralloc_copys(dn, d) || !stralloc_0(dn))
		return ERRNO;
#ifdef LDAP_OPT_PROTOCOL_VERSION
	/*
	 * OpenLDAP 1.x does not have ldap_memfree() use free() instead.
	 */
	ldap_memfree(d);
#else
	free(d);
#endif
	return OK;
}