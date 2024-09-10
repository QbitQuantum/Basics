/**
 * @brief
 * 		add_privilege - add_privilege: returns 0 if privname has been added for account
 * 		referenced by sid; otherwise, 1.
 *
 * @param[in]	sid	-	The security identifier (SID) structure is a variable-length structure
 * 						 used to uniquely identify users or groups.
 * @param[in]	privname	-	privilege name
 *
 * @return	int
 * @retval	1	: if privname has not been added for account referenced by sid
 * @retval	0	: if privname has been added for account referenced by sid
 */
int
add_privilege(SID *sid, char *privname)
{
	LSA_UNICODE_STRING rights;
	LSA_HANDLE h_policy = INVALID_HANDLE_VALUE;
	LSA_OBJECT_ATTRIBUTES  obj_attrs;
	NTSTATUS lsa_stat;
	BOOL	rval = 1;
	WCHAR	*privnameW = NULL;
	int	priv_len = 0;

	if (privname == NULL) {
		fprintf(stderr, "add_privilege: NULL privname\n");
		return (1);
	}

	if (!IsValidSid(sid)) {
		fprintf(stderr, "add_privilege: Not a valid sid\n");
		return (1);
	}

	priv_len = strlen(privname) + 1;
	privnameW = (WCHAR *)malloc(priv_len * sizeof(WCHAR));

	if (privnameW == NULL) {
		fprintf(stderr, "add_privilege: malloc failed\n");
		return (1);
	}

	mbstowcs(privnameW, privname, priv_len);
	init_lsa_string(&rights, privnameW);

	ZeroMemory(&obj_attrs, sizeof(obj_attrs));
	if( LsaOpenPolicy(NULL, &obj_attrs, POLICY_ALL_ACCESS, &h_policy) \
							!= ERROR_SUCCESS ) {
		fprintf(stderr, "add_privilege: Unable to open policy!\n");
		goto add_privilege_end;
	}

	if( (lsa_stat=LsaAddAccountRights( h_policy, sid, &rights, 1 )) != \
							ERROR_SUCCESS ) {
		fprintf(stderr,
			"add_privilege: adding privilege %s failed! - err %d\n",
			privname, LsaNtStatusToWinError(lsa_stat));
		goto add_privilege_end;
	}

	printf("\tadded %s\n", privname);
	rval = 0;

add_privilege_end:
	if (h_policy != INVALID_HANDLE_VALUE)
		LsaClose(h_policy);

	if (privnameW != NULL)
		(void)free(privnameW);

	return (rval);
}