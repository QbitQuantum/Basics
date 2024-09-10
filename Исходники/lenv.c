static int env_getdrivers (lua_State *L) {
    lodbc_env *env = (lodbc_env *) lodbc_getenv (L);
    SQLRETURN ret;
    SQLSMALLINT attrlen,desclen;
    int i = 1;
    char desc[MAX_DESC_LEN];
    char *attr = malloc(MAX_ATTR_LEN+1);
    int is_cb = lua_isfunction(L,2);
    int top = lua_gettop(L);

    if(!attr)
        return LODBC_ALLOCATE_ERROR(L);

    ret = SQLDrivers(env->handle,SQL_FETCH_FIRST,
                     (SQLPOINTER)desc,MAX_DESC_LEN,&desclen,
                     (SQLPOINTER)attr,MAX_ATTR_LEN,&attrlen);
    if(!is_cb) top++,lua_newtable(L);
    if(LODBC_ODBC3_C(SQL_NO_DATA,SQL_NO_DATA_FOUND) == ret) {
        free(attr);
        return is_cb ? 0 : 1;
    }
    while(!lodbc_iserror(ret)) {
        assert(top == lua_gettop(L));
        if(is_cb) lua_pushvalue(L, 2);

        //find our attributes
        if(attr[0]!=0) {
            size_t i=0, last=0, n=1;
            lua_newtable(L);
            do {
                char *p,*a;
                while(attr[++i] != 0);
                a = &(attr[last]);
                p = strchr(a,'=');
                if(p) {
                    lua_pushlstring(L, a, p-a);
                    lua_pushlstring(L, p + 1, (i-last)-(p-a)-1);
                    lua_settable(L,-3);
                }
                else {
                    lua_pushlstring(L,a,(i-last));
                    lua_rawseti(L,-2,n++);
                }
                last=i+1;
            } while(attr[last]!=0);
        }
        else lua_pushnil(L);

        if(!is_cb) {
            lua_newtable(L);
            lua_insert(L,-2);
            lua_rawseti(L,-2,2);
            lua_pushstring(L,desc);
            lua_rawseti(L,-2,1);
            lua_rawseti(L,-2,i++);
        }
        else {
            int ret;
            lua_pushstring(L,desc);
            lua_insert(L,-2);

            lua_call(L,2,LUA_MULTRET);
            ret = lua_gettop(L) - top;
            assert(ret >= 0);
            if(ret) {
                free(attr);
                return ret;
            }
        }

        ret = SQLDrivers(env->handle,SQL_FETCH_NEXT,
                         (SQLPOINTER)desc,MAX_DESC_LEN,&desclen,
                         (SQLPOINTER)attr,MAX_ATTR_LEN,&attrlen);

        if(LODBC_ODBC3_C(SQL_NO_DATA,SQL_NO_DATA_FOUND) == ret) {
            free(attr);
            return is_cb ? 0 : 1;
        }
    }
    free(attr);
    return lodbc_fail(L, hENV, env->handle);
}