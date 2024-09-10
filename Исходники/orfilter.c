static int
or_filter_match (void* obj, Slapi_Entry* entry, Slapi_Attr* attr)
/* returns:  0  filter matched
 *	    -1  filter did not match
 *	    >0  an LDAP error code
 */
{
    auto int rc = -1; /* no match */
    auto or_filter_t* or = (or_filter_t*)obj;
    for (; attr != NULL; slapi_entry_next_attr (entry, attr, &attr)) {
	auto char* type = NULL;
	auto struct berval** vals = NULL;

/*
 * XXXmcs 1-March-2001: This code would perform better if it did not make
 * a copy of the values here, but that would require re-writing the code
 * in this file to use Slapi_ValueSet's instead of struct berval **'s
 * (and that is not a small project).
 */
	if (!slapi_attr_get_type (attr, &type) && type != NULL &&
	    !slapi_attr_type_cmp (or->or_type, type, 2/*match subtypes*/) &&
	    !slapi_attr_get_bervals_copy(attr, &vals) && vals != NULL) {

	    if (or->or_op == SLAPI_OP_SUBSTRING) {
		rc = ss_filter_match (or, vals);
	    } else {
		rc = op_filter_match (or, vals);
	    }

	    ber_bvecfree( vals );
	    vals = NULL;
	    if (rc >= 0) break;
	}
    }
    return rc;
}