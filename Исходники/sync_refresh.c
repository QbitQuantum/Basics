int
sync_send_entry_from_changelog(Slapi_PBlock *pb,int chg_req, char *uniqueid)
{
	Slapi_Entry *db_entry = NULL;
	int chg_type = LDAP_SYNC_ADD;
	int rv;
	Slapi_PBlock *search_pb = NULL;
    	Slapi_Entry **entries = NULL;
	char *origbase;
	char *filter = slapi_ch_smprintf("(nsuniqueid=%s)",uniqueid);

	slapi_pblock_get( pb, SLAPI_ORIGINAL_TARGET_DN, &origbase );
	search_pb = slapi_pblock_new();
    	slapi_search_internal_set_pb(search_pb, origbase,
           				LDAP_SCOPE_SUBTREE, filter,
            				NULL, 0, NULL, NULL, plugin_get_default_component_id(), 0);
 	slapi_search_internal_pb(search_pb);
	slapi_pblock_get(search_pb, SLAPI_PLUGIN_INTOP_RESULT, &rv);
	if ( rv == LDAP_SUCCESS) {
		slapi_pblock_get(search_pb, SLAPI_PLUGIN_INTOP_SEARCH_ENTRIES, &entries);
    		if (entries)
			db_entry = *entries; /* there can only be one */
	}

	if (db_entry && sync_is_entry_in_scope(pb, db_entry)) {
		LDAPControl **ctrl = (LDAPControl **)slapi_ch_calloc(2, sizeof (LDAPControl *));
		sync_create_state_control(db_entry, &ctrl[0], chg_type, NULL);
		slapi_send_ldap_search_entry (pb, db_entry, ctrl, NULL, 0);
		ldap_controls_free(ctrl);
	}
	slapi_free_search_results_internal(search_pb);
	slapi_pblock_destroy(search_pb);
	slapi_ch_free((void **)&filter);
	return (0);
}