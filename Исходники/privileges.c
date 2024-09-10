/* 
   list the rights for an account. This involves traversing the database
*/
NTSTATUS privilege_enum_account_rights(DOM_SID *sid,
				       uint32 *count,
				       char ***rights)
{
	TDB_DATA key, nextkey;
	char *right;

	if (!tdb) {
		return NT_STATUS_INTERNAL_ERROR;
	}

	*rights = NULL;
	*count = 0;

	for (key = tdb_firstkey(tdb); key.dptr; key = nextkey) {
		nextkey = tdb_nextkey(tdb, key);

		right = key.dptr;
		
		if (privilege_sid_has_right(sid, right)) {
			(*rights) = (char **)Realloc(*rights,sizeof(char *) * ((*count)+1));
			if (! *rights) {
				safe_free(nextkey.dptr);
				free(key.dptr);
				return NT_STATUS_NO_MEMORY;
			}

			(*rights)[*count] = strdup(right);
			(*count)++;
		}

		free(key.dptr);
	}

	return NT_STATUS_OK;
}