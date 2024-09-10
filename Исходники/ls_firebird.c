/*
** Returns a row of data from the query
** Lua Returns:
**   list of results or table of results depending on call
**   nil and error message otherwise.
*/
static int cur_fetch (lua_State *L) {
    ISC_STATUS fetch_stat;
    int i;
    cur_data *cur = getcursor(L,1);
    const char *opts = luaL_optstring (L, 3, "n");
    int num = strchr(opts, 'n') != NULL;
    int alpha = strchr(opts, 'a') != NULL;

    if ((fetch_stat = isc_dsql_fetch(cur->env->status_vector, &cur->stmt, 1, cur->out_sqlda)) == 0) {
        if (lua_istable (L, 2)) {
            /* remove the option string */
            lua_settop(L, 2);

            /* loop through the columns */
            for (i = 0; i < cur->out_sqlda->sqld; i++) {
                push_column(L, i, cur);

                if( num ) {
                    lua_pushnumber(L, i+1);
                    lua_pushvalue(L, -2);
                    lua_settable(L, 2);
                }

                if( alpha ) {
                    lua_pushlstring(L, cur->out_sqlda->sqlvar[i].aliasname, cur->out_sqlda->sqlvar[i].aliasname_length);
                    lua_pushvalue(L, -2);
                    lua_settable(L, 2);
                }

                lua_pop(L, 1);
            }

            /* returning given table */
            return 1;
        } else {
            for (i = 0; i < cur->out_sqlda->sqld; i++)
                push_column(L, i, cur);

            /* returning a list of values */
            return cur->out_sqlda->sqld;
        }
    }

    /* isc_dsql_fetch returns 100 if no more rows remain to be retrieved
       so this can be ignored */
    if (fetch_stat != 100L)
        return return_db_error(L, cur->env->status_vector);

    /* last row has been fetched, close cursor */
    isc_dsql_free_statement(cur->env->status_vector, &cur->stmt, DSQL_drop);
    if ( CHECK_DB_ERROR(cur->env->status_vector) )
        return return_db_error(L, cur->env->status_vector);

    /* free the cursor data */
    free_cur(cur);

    cur->closed = 1;

    /* remove cursor from lock count */
    --cur->conn->lock;

    /* return sucsess */
    return 0;
}