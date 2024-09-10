STDMETHODIMP CLDAPQuery::connect(
	/* [in] */ BSTR username,
	/* [in] */ BSTR password,
	/* [in] */ BSTR host,
	/* [in] */ VARIANT_BOOL usessl,
	/* [retval][out] */ LONG *connect_id)
{
	m_errorCode = 0L;
	const ULONG no_limit = LDAP_NO_LIMIT;

	PLDAP ld = NULL;
	bool useSSL = (usessl==VARIANT_TRUE)? true : false;
	bool canFindFromRoot = true;
	CAttributesSchema *attrsSchema = NULL;
	ULONG ulPort = useSSL?LDAP_SSL_PORT:LDAP_PORT;
	
	PTCHAR port = NULL;
	CString defaultNamingContext;
	CString csHost = host;
	CString hostname = _tcstok_s(csHost.GetBuffer(), _T(":"), &port);
	if(port && _tcslen(port) > 0)
		ulPort = _tcstol(port, NULL, 10);
	csHost.ReleaseBuffer();

	try
	{
		if (useSSL)
		{
			if((ld = ldap_sslinit(hostname.GetBuffer(), ulPort, 1))==NULL)
			{
				m_errorCode = LdapGetLastError();
				return S_FALSE;
			}

			m_errorCode = ldap_set_option(ld, LDAP_OPT_SERVER_CERTIFICATE, &CertRoutine);
			if (m_errorCode != LDAP_SUCCESS)
				throw _T("error LDAP_OPT_SERVER_CERTIFICATE");
		}
		else
		{
			if((ld = ldap_init(hostname.GetBuffer(), ulPort))==NULL)
			{
				m_errorCode = LdapGetLastError();
				return S_FALSE;
			}
		}

		const ULONG version = LDAP_VERSION3;
		m_errorCode = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, (void*)&version);
		if (m_errorCode != LDAP_SUCCESS)
			throw _T("error LDAP_OPT_PROTOCOL_VERSION");

		m_errorCode = ldap_set_option(ld, LDAP_OPT_SIZELIMIT, (void*)&no_limit);
		if (m_errorCode != LDAP_SUCCESS)
			throw _T("error LDAP_OPT_SIZELIMIT");
		ld->ld_sizelimit = no_limit;

		m_errorCode = ldap_set_option(ld, LDAP_OPT_TIMELIMIT, (void*)&no_limit);
		if (m_errorCode != LDAP_SUCCESS)
			throw _T("error LDAP_OPT_TIMELIMIT");
		ld->ld_timelimit = no_limit;

		m_errorCode = ldap_connect(ld, 0);
		if (m_errorCode != LDAP_SUCCESS )
			throw _T("error ldap_connect");

		m_errorCode = ldap_bind_s(ld, CString(username).GetBuffer(), CString(password).GetBuffer(), LDAP_AUTH_SIMPLE);
		if (m_errorCode != LDAP_SUCCESS)
			throw _T("error LDAP_AUTH_SIMPLE");

		/* Get the RootDSE and BaseDN attribute (add checks on use this code).*/
		CSimpleArray<PTCHAR> a;
		a.Add(_T("defaultNamingContext"));
		a.Add(_T("subschemaSubentry"));
		a.Add(NULL);
		PLDAPMessage pBaseMsg = NULL;
		if(ldap_search_s(ld, _T(""), LDAP_SCOPE_BASE, _T("(objectClass=*)"), a.GetData(), 0, &pBaseMsg) == LDAP_SUCCESS)
		{
			PLDAPMessage const entry = ldap_first_entry(ld, pBaseMsg);
			if(entry)
			{
				PTCHAR * const pschema = ldap_get_values(ld, entry, _T("subschemaSubentry"));
				if(pschema)
				{
					attrsSchema = new CAttributesSchema(ld, *pschema);
					ldap_value_free(pschema);
				}
				//try to find one item in subtree from root, if found it is Global Catalog search
				PLDAPSearch const pPages = ldap_search_init_page(ld, NULL, LDAP_SCOPE_SUBTREE, _T("(objectClass=*)"), NULL, 0, NULL, NULL, no_limit, 1, NULL);
				if(pPages)
				{
					PLDAPMessage pMsg = NULL;
					canFindFromRoot = (ldap_get_next_page_s(ld, pPages, NULL, 1, NULL, &pMsg) == LDAP_SUCCESS);
					if(pMsg)
						ldap_msgfree(pMsg);
					ldap_search_abandon_page(ld, pPages);
				}
				PTCHAR * const pDefaultNamingContext = ldap_get_values(ld, entry, _T("defaultNamingContext"));
				if(pDefaultNamingContext)
				{
					defaultNamingContext = *pDefaultNamingContext;
					ldap_value_free(pDefaultNamingContext);
				}
			}
			ldap_msgfree(pBaseMsg);
		}

		ÑConnectInfo * const cinfo = new ÑConnectInfo(ld, attrsSchema, defaultNamingContext, canFindFromRoot);
		*connect_id = ++m_maxConnectionId;
		m_connections.Add(*connect_id, cinfo);
	}
	catch (PTCHAR /*e*/)
	{
		if (ld)
			ldap_unbind_s(ld);
		*connect_id = -1;
		return S_FALSE;
	}
	
	return S_OK;
}