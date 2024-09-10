static void linphone_ldap_contact_provider_handle_search_result( LinphoneLDAPContactProvider* obj, LinphoneLDAPContactSearch* req, LDAPMessage* message )
{
	int msgtype = ldap_msgtype(message);

	switch(msgtype){

	case LDAP_RES_SEARCH_ENTRY:
	case LDAP_RES_EXTENDED:
	{
		LDAPMessage *entry = ldap_first_entry(obj->ld, message);
		LinphoneCore*   lc = LINPHONE_CONTACT_PROVIDER(obj)->lc;

		while( entry != NULL ){

			struct LDAPFriendData ldap_data = {0};
			bool_t contact_complete = FALSE;
			BerElement*  ber = NULL;
			char*       attr = ldap_first_attribute(obj->ld, entry, &ber);

			while( attr ){
				struct berval** values = ldap_get_values_len(obj->ld, entry, attr);
				struct berval**     it = values;

				while( values && *it && (*it)->bv_val && (*it)->bv_len )
				{
					contact_complete = linphone_ldap_contact_provider_complete_contact(obj, &ldap_data, attr, (*it)->bv_val);
					if( contact_complete ) break;

					it++;
				}

				if( values ) ldap_value_free_len(values);
				ldap_memfree(attr);

				if( contact_complete ) break;

				attr = ldap_next_attribute(obj->ld, entry, ber);
			}

			if( contact_complete ) {
				LinphoneAddress* la = linphone_core_interpret_url(lc, ldap_data.sip);
				if( la ){
					LinphoneFriend* lf = linphone_core_create_friend(lc);
					linphone_friend_set_address(lf, la);
					linphone_friend_set_name(lf, ldap_data.name);
					req->found_entries = bctbx_list_append(req->found_entries, lf);
					req->found_count++;
					//ms_message("Added friend %s / %s", ldap_data.name, ldap_data.sip);
					ms_free(ldap_data.sip);
					ms_free(ldap_data.name);
					linphone_address_destroy(la);
				}
			}

			if( ber ) ber_free(ber, 0);

			entry = ldap_next_entry(obj->ld, entry);
		}
	}
	break;

	case LDAP_RES_SEARCH_RESULT:
	{
		// this one is received when a request is finished
		req->complete = TRUE;
		linphone_contact_search_invoke_cb(LINPHONE_CONTACT_SEARCH(req), req->found_entries);
	}
	break;


	default: ms_message("[LDAP] Unhandled message type %x", msgtype); break;
	}
}