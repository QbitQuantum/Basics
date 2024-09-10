/*
 * parses the result returned by an ldap query
 */
static err_t
parse_ldap_result(LDAP * ldap, LDAPMessage *result, chunk_t *blob)
{
    err_t ugh = NULL;

    LDAPMessage * entry = ldap_first_entry(ldap, result);

    if (entry != NULL)
    {
	BerElement *ber = NULL;
	char *attr;
	
	attr = ldap_first_attribute(ldap, entry, &ber);

	if (attr != NULL)
	{
	    struct berval **values = ldap_get_values_len(ldap, entry, attr);

	    if (values != NULL)
	    {
		if (values[0] != NULL)
		{
		    blob->len = values[0]->bv_len;
		    blob->ptr = alloc_bytes(blob->len, "ldap blob");
		    memcpy(blob->ptr, values[0]->bv_val, blob->len);
		    if (values[1] != NULL)
		    {
			plog("warning: more than one value was fetched from LDAP URL");
		    }
		}
		else
		{
		    ugh = "no values in attribute";
		}
		ldap_value_free_len(values);
	    }
	    else
	    {
		ugh = ldap_err2string(ldap_result2error(ldap, entry, 0));
	    }
	    ldap_memfree(attr);
	}
	else
	{
	    ugh = ldap_err2string(ldap_result2error(ldap, entry, 0));
	}
	ber_free(ber, 0);
    }
    else
    {
	ugh = ldap_err2string(ldap_result2error(ldap, result, 0));
    }
    return ugh;
}