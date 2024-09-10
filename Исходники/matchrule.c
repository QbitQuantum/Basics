/*
 * This routine returns pointer to memory which is owned by the plugin, so don't 
 * free it. Gets freed by the next call to this routine, or when the indexer
 * is destroyed
 */
int
matchrule_values_to_keys_sv(Slapi_PBlock *pb,Slapi_Value **input_values,Slapi_Value ***output_values)
{
	IFP mrINDEX = NULL;

	slapi_pblock_get (pb, SLAPI_PLUGIN_MR_INDEX_SV_FN, &mrINDEX);
	if (NULL == mrINDEX) { /* old school - does not have SV function */
		int rc;
		struct berval **bvi = NULL, **bvo = NULL;
		valuearray_get_bervalarray(input_values, &bvi);
		rc = matchrule_values_to_keys(pb, bvi, &bvo);
		ber_bvecfree(bvi);
		/* note - the indexer owns bvo and will free it when destroyed */
		valuearray_init_bervalarray(bvo, output_values);
		/* store output values in SV form - caller expects SLAPI_PLUGIN_MR_KEYS is Slapi_Value** */
		slapi_pblock_set(pb, SLAPI_PLUGIN_MR_KEYS, *output_values);
		return rc;
	}

	slapi_pblock_set (pb, SLAPI_PLUGIN_MR_VALUES, input_values);
	mrINDEX (pb);
	slapi_pblock_get (pb, SLAPI_PLUGIN_MR_KEYS, output_values);
	return 0;
}