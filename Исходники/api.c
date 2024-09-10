LUA_EXPORT(int openldap_uv_lua_search(lua_State *L))
{
    openldap_uv_lua_handle_t *ldap = luaL_checkudata(L, 1, META_TABLE);

    if(!ldap->ldap)
    {
        luaL_error(L, "Handle is not connected");
    }

    const char *dn = openldap_uv_lua__string_or_null(L, 2);
    const char *scope = luaL_checkstring(L, 3);

    int _scope;
    if(strcmp(scope, "LDAP_SCOPE_BASE") == 0 || strcmp(scope, "LDAP_SCOPE_BASEOBJECT") == 0) _scope = LDAP_SCOPE_BASEOBJECT;
    else if(strcmp(scope, "LDAP_SCOPE_ONE") == 0 || strcasecmp(scope, "LDAP_SCOPE_ONELEVEL") == 0) _scope = LDAP_SCOPE_ONELEVEL;
    else if(strcmp(scope, "LDAP_SCOPE_SUB") == 0 || strcasecmp(scope, "LDAP_SCOPE_SUBTREE") == 0) _scope = LDAP_SCOPE_SUBTREE;
    else if(strcmp(scope, "LDAP_SCOPE_CHILDREN") == 0 || strcasecmp(scope, "LDAP_SCOPE_SUBORDINATE") == 0) _scope = LDAP_SCOPE_CHILDREN;
    else luaL_error(L, "Unsupported scope %s", scope);

    const char *filter = openldap_uv_lua__string_or_null(L, 4);

    char **fieldSelector = NULL;

    if(!lua_isnil(L, 5))
    {
        luaL_checktype(L, 5, LUA_TTABLE);
        int size = lua_objlen(L, 5);

        fieldSelector = malloc(sizeof(*fieldSelector) * (size + 1));

        lua_pushnil(L);

        for(int i = 0; lua_next(L, 5); i++)
        {
            fieldSelector[i] = (char *)lua_tostring(L, -1);
            fieldSelector[i+1] = 0;
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

    int onlyFieldNames = lua_toboolean(L, 6) ? 1 : 0;

    LDAPMessage *message = 0;
    int err = ldap_search_ext_s(ldap->ldap, dn, _scope, filter, fieldSelector, onlyFieldNames, 0, 0, 0, LDAP_NO_LIMIT, &message);

    if(err != 0)
    {
        ldap_msgfree(message);
        openldap_uv_lua__check_error(L, ldap, err);
    }

    LDAPMessage *entry = ldap_first_entry(ldap->ldap, message);

    lua_newtable(L);

    while(entry)
    {
        char *dn = ldap_get_dn(ldap->ldap, entry);
        lua_pushstring(L, dn);
        free(dn);

        lua_newtable(L);

        BerElement *ber;
        char *attr = ldap_first_attribute(ldap->ldap, entry, &ber);

        int j = 0;
        while(attr)
        {
            struct berval **vals = ldap_get_values_len(ldap->ldap, entry, attr );

            if(vals)
            {
                for(int i = 0; vals[i]; i++)
                {
                    lua_pushnumber(L, ++j);

                    lua_newtable(L);

                    lua_pushnumber(L, 1);
                    lua_pushstring(L, attr);
                    lua_rawset(L, -3);

                    lua_pushnumber(L, 2);
                    lua_pushlstring(L, vals[i]->bv_val, vals[i]->bv_len);
                    lua_rawset(L, -3);

                    lua_rawset(L, -3);
                }

                ldap_value_free_len( vals );
            }

            ldap_memfree( attr );

            attr = ldap_next_attribute( ldap->ldap, entry, ber);
        }

        lua_rawset(L, -3);

        entry = ldap_next_entry(ldap->ldap, entry);
    }

    ldap_msgfree(message);

    return 1;
}