/**
   \details Test the NspiSeekEntries RPC operation (0x04)

   \param mt pointer on the top-level mapitest structure

   \return true on success, otherwise false
 */
_PUBLIC_ bool mapitest_nspi_SeekEntries(struct mapitest *mt)
{
	TALLOC_CTX		*mem_ctx;
	enum MAPISTATUS		retval;
	struct nspi_context	*nspi_ctx;
	struct PropertyValue_r	pTarget;
	struct SPropTagArray	*pPropTags;
	struct PropertyRowSet_r		*RowSet;
	struct emsmdb_context	*emsmdb;
	bool			ret = true;

	mem_ctx = talloc_named(NULL, 0, "mapitest_nspi_SeekEntries");
	nspi_ctx = (struct nspi_context *) mt->session->nspi->ctx;

	emsmdb = (struct emsmdb_context *) mt->session->emsmdb->ctx;
	RowSet = talloc_zero(mem_ctx, struct PropertyRowSet_r);
	
	pTarget.ulPropTag = PR_DISPLAY_NAME;
	pTarget.dwAlignPad = 0x0;
	pTarget.value.lpszA = emsmdb->info.szDisplayName;

	pPropTags = set_SPropTagArray(mem_ctx, 0x1, PR_ACCOUNT);
	retval = nspi_SeekEntries(nspi_ctx, mem_ctx, SortTypeDisplayName, &pTarget, pPropTags, NULL, &RowSet);
	if (retval != MAPI_E_SUCCESS) {
		ret = false;
	}

	mapitest_print_retval_clean(mt, "NspiSeekEntries", retval);
	MAPIFreeBuffer(RowSet);
	MAPIFreeBuffer(pPropTags);

	RowSet = talloc_zero(mem_ctx, struct PropertyRowSet_r);

	pTarget.ulPropTag = PR_DISPLAY_NAME_UNICODE;
	pTarget.dwAlignPad = 0x0;
	pTarget.value.lpszA = emsmdb->info.szDisplayName;

	pPropTags = set_SPropTagArray(mem_ctx, 0x1, PR_ACCOUNT);
	retval = nspi_SeekEntries(nspi_ctx, mem_ctx, SortTypeDisplayName, &pTarget, pPropTags, NULL, &RowSet);
	if (retval != MAPI_E_SUCCESS) {
		ret = false;
	}

	mapitest_print_retval_clean(mt, "NspiSeekEntries", retval);
	MAPIFreeBuffer(RowSet);
	MAPIFreeBuffer(pPropTags);

	talloc_free(mem_ctx);

	return ret;
}