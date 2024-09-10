	void BuildReply(int res, LDAPRequest *req)
	{
		LDAPResult *ldap_result = req->result = new LDAPResult();
		req->result->type = req->type;

		if (res != LDAP_SUCCESS)
		{
			ldap_result->error = ldap_err2string(res);
			return;
		}

		if (req->message == NULL)
		{
			return;
		}

		/* a search result */

		for (LDAPMessage *cur = ldap_first_message(this->con, req->message); cur; cur = ldap_next_message(this->con, cur))
		{
			LDAPAttributes attributes;

			char *dn = ldap_get_dn(this->con, cur);
			if (dn != NULL)
			{
				attributes["dn"].push_back(dn);
				ldap_memfree(dn);
				dn = NULL;
			}

			BerElement *ber = NULL;

			for (char *attr = ldap_first_attribute(this->con, cur, &ber); attr; attr = ldap_next_attribute(this->con, cur, ber))
			{
				berval **vals = ldap_get_values_len(this->con, cur, attr);
				int count = ldap_count_values_len(vals);

				std::vector<Anope::string> attrs;
				for (int j = 0; j < count; ++j)
					attrs.push_back(vals[j]->bv_val);
				attributes[attr] = attrs;

				ldap_value_free_len(vals);
				ldap_memfree(attr);
			}

			if (ber != NULL)
				ber_free(ber, 0);

			ldap_result->messages.push_back(attributes);
		}
	}