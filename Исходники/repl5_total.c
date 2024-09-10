/*
 * Extract the payload from a total update extended operation,
 * decode it, and produce a Slapi_Entry structure representing a new
 * entry to be added to the local database.
 */
static int
decode_total_update_extop(Slapi_PBlock *pb, Slapi_Entry **ep)
{
	BerElement *tmp_bere = NULL;
	Slapi_Entry *e = NULL;
	Slapi_Attr *attr = NULL;
	char *str = NULL;
	struct berval *extop_value = NULL;
	char *extop_oid = NULL;
	ber_len_t len;
	char *lasto;
	ber_tag_t tag;
	int rc;
	PRBool deleted;
	
	PR_ASSERT(NULL != pb);
	PR_ASSERT(NULL != ep);

	slapi_pblock_get(pb, SLAPI_EXT_OP_REQ_OID, &extop_oid);
	slapi_pblock_get(pb, SLAPI_EXT_OP_REQ_VALUE, &extop_value);

	if ((NULL == extop_oid) || 
		((strcmp(extop_oid, REPL_NSDS50_REPLICATION_ENTRY_REQUEST_OID) != 0) && 
		 (strcmp(extop_oid, REPL_NSDS71_REPLICATION_ENTRY_REQUEST_OID) != 0)) ||
		!BV_HAS_DATA(extop_value))
	{
		/* Bogus */
		goto loser;
	}

	if ((tmp_bere = ber_init(extop_value)) == NULL)
	{
		goto loser;
	}

	if ((e = slapi_entry_alloc()) == NULL)
	{
		goto loser;
	}

	if (ber_scanf(tmp_bere, "{") == LBER_ERROR) /* Begin outer sequence */
	{
		goto loser;
	}

	/* The entry's uniqueid is first */
	if (ber_scanf(tmp_bere, "a", &str) == LBER_ERROR)
	{
		goto loser;
	}
	slapi_entry_set_uniqueid(e, str);
	str = NULL;	/* Slapi_Entry now owns the uniqueid */

	/* The entry's DN is next */
	if (ber_scanf(tmp_bere, "a", &str) == LBER_ERROR)
	{
		goto loser;
	}
	slapi_entry_set_dn(e, str);
	str = NULL; /* Slapi_Entry now owns the dn */

	/* Get the attributes */
	for ( tag = ber_first_element( tmp_bere, &len, &lasto );
		tag != LBER_ERROR && tag != LBER_END_OF_SEQORSET;
		tag = ber_next_element( tmp_bere, &len, lasto ) )
	{

        if (my_ber_scanf_attr (tmp_bere, &attr, &deleted) != 0)
        {
            goto loser;
        }
		
	    /* Add the attribute to the entry */
        if (deleted)
            entry_add_deleted_attribute_wsi(e, attr); /* entry now owns attr */
        else
		    entry_add_present_attribute_wsi(e, attr); /* entry now owns attr */
        attr = NULL;
	}

    if (ber_scanf(tmp_bere, "}") == LBER_ERROR) /* End sequence for this entry */
	{
		goto loser;
	}

	/* Check for ldapsubentries and tombstone entries to set flags properly */
	slapi_entry_attr_find(e, "objectclass", &attr);
	if (attr != NULL) {
		struct berval bv;
		bv.bv_val = "ldapsubentry";
		bv.bv_len = strlen(bv.bv_val);
		if (slapi_attr_value_find(attr, &bv) == 0) {
			slapi_entry_set_flag(e, SLAPI_ENTRY_LDAPSUBENTRY);
		}
		bv.bv_val = SLAPI_ATTR_VALUE_TOMBSTONE;
		bv.bv_len = strlen(bv.bv_val);
		if (slapi_attr_value_find(attr, &bv) == 0) {
			slapi_entry_set_flag(e, SLAPI_ENTRY_FLAG_TOMBSTONE);
		}
	}
	
	/* If we get here, the entry is properly constructed. Return it. */

	rc = 0;
	*ep = e;
	goto free_and_return;

loser:
	rc = -1;
	/* slapi_ch_free accepts NULL pointer */
	slapi_ch_free((void **)&str);

    if (attr != NULL)
    {
        slapi_attr_free (&attr);
    }
    
    if (NULL != e)
    {
        slapi_entry_free (e);
    }
	*ep = NULL;
	slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "Error: could not decode extended "
		"operation containing entry for total update.\n");

free_and_return:
    if (NULL != tmp_bere)
	{
		ber_free(tmp_bere, 1); 
		tmp_bere = NULL;
	}
	return rc;
}