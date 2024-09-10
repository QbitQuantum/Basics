/*
** Retrieve next message...
** @return #1 entry's distinguished name.
** @return #2 table with entry's attributes and values.
*/
static int next_message (lua_State *L) {
	search_data *search = getsearch (L);
	conn_data *conn;
	struct timeval *timeout = NULL; /* ??? function parameter ??? */
	LDAPMessage *res;
	int rc;
	int ret;

	lua_rawgeti (L, LUA_REGISTRYINDEX, search->conn);
	conn = (conn_data *)lua_touserdata (L, -1); /* get connection */

	rc = ldap_result (conn->ld, search->msgid, LDAP_MSG_ONE, timeout, &res);
	if (rc == 0)
		return faildirect (L, LUALDAP_PREFIX"result timeout expired");
	else if (rc == -1)
		return faildirect (L, LUALDAP_PREFIX"result error");
	else if (rc == LDAP_RES_SEARCH_RESULT) { /* last message => nil */
		/* close search object to avoid reuse */
		search_close (L, search);
		ret = 0;
	} else {
		LDAPMessage *msg = ldap_first_message (conn->ld, res);
		switch (ldap_msgtype (msg)) {
			case LDAP_RES_SEARCH_ENTRY: {
				LDAPMessage *entry = ldap_first_entry (conn->ld, msg);
				push_dn (L, conn->ld, entry);
				lua_newtable (L);
				set_attribs (L, conn->ld, entry, lua_gettop (L));
				ret = 2; /* two return values */
				break;
			}
/*No reference to LDAP_RES_SEARCH_REFERENCE on MSDN. Maybe there is a replacement to it?*/
#ifdef LDAP_RES_SEARCH_REFERENCE
			case LDAP_RES_SEARCH_REFERENCE: {
				LDAPMessage *ref = ldap_first_reference (conn->ld, msg);
				push_dn (L, conn->ld, ref); /* is this supposed to work? */
				lua_pushnil (L);
				ret = 2; /* two return values */
				break;
			}
#endif
			case LDAP_RES_SEARCH_RESULT:
				/* close search object to avoid reuse */
				search_close (L, search);
				ret = 0;
				break;
			default:
				ldap_msgfree (res);
				return luaL_error (L, LUALDAP_PREFIX"error on search result chain");
		}
	}
	ldap_msgfree (res);
	return ret;
}