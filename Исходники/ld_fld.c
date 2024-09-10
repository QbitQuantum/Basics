/** Frees memory used by a ld_fld structure.
 * This function frees all memory used by a ld_fld structure
 * @param fld Generic db_fld_t* structure being freed.
 * @param payload The ldap extension structure to be freed
 */
static void ld_fld_free(db_fld_t* fld, struct ld_fld* payload)
{
	db_drv_free(&payload->gen);
	if (payload->values) ldap_value_free_len(payload->values);	
	payload->values = NULL;
	if (payload->filter) pkg_free(payload->filter);
	payload->filter = NULL;
	pkg_free(payload);
}