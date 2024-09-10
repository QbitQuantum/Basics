		~zn_ldap()
		{
			if (_ldap != NULL) ldap_unbind(_ldap);
		}