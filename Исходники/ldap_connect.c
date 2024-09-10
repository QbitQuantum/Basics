int ldap_reconnect(char* _ld_name)
{
	int rc;
	
	if (ldap_disconnect(_ld_name) != 0)
	{
		LM_ERR("[%s]: disconnect failed\n", _ld_name);
		return -1;
	}

	if ((rc = ldap_connect(_ld_name)) != 0)
	{
		LM_ERR("[%s]: reconnect failed\n",
				_ld_name);
	}
	else
	{
		LM_ERR("[%s]: LDAP reconnect successful\n",
				_ld_name);
	}
	return rc;
}