static int search_iterator(lua_State *L)
{
  LDAPMessage *result, *message, *entry;
  lua_apr_ldap_object *object;
  struct timeval *timeout;
  int status, msgid;

  object = lua_touserdata(L, lua_upvalueindex(1));
  msgid = lua_tointeger(L, lua_upvalueindex(2));
  timeout = lua_touserdata(L, lua_upvalueindex(3));
  status = ldap_result(object->ldap, msgid, LDAP_MSG_ONE, timeout, &result);

  if (status == 0)
    raise_error_status(L, APR_TIMEUP);
  else if (status == -1)
    /* TODO Can we get a more specific error (message) here? ld_errno? */
    raise_error_message(L, "Unspecified error");
  else if (status == LDAP_RES_SEARCH_RESULT) {
    /* end of search results */
    return 0;
  } else {
    message = ldap_first_message(object->ldap, result);
    switch (ldap_msgtype(message)) {
      case LDAP_RES_SEARCH_ENTRY:
        entry = ldap_first_entry(object->ldap, message);
        push_distinguished_name(L, object->ldap, entry);
        lua_newtable(L);
        set_attributes(L, object->ldap, entry, lua_gettop(L));
        ldap_msgfree(result);
        return 2;
      /* No reference to LDAP_RES_SEARCH_REFERENCE on MSDN. Maybe is has a replacement? */
#     ifdef LDAP_RES_SEARCH_REFERENCE
      case LDAP_RES_SEARCH_REFERENCE: {
        LDAPMessage *reference = ldap_first_reference(object->ldap, message);
        push_distinguished_name(L, object->ldap, reference); /* is this supposed to work? */
        ldap_msgfree(result);
        return 1;
      }
#     endif
      case LDAP_RES_SEARCH_RESULT:
        /* end of search results */
        ldap_msgfree(result);
        return 0;
      default:
        ldap_msgfree(result);
        raise_error_message(L, "unhandled message type in search results");
    }
  }

  /* shouldn't be reached. */
  ldap_msgfree(result);
  return 0;
}