/* Get or Set the username for the fko context spa data.
*/
int
fko_set_username(fko_ctx_t ctx, const char * const spoof_user)
{
    char   *username = NULL;
    int     res = FKO_SUCCESS, is_user_heap_allocated=0;

#if HAVE_LIBFIU
    fiu_return_on("fko_set_username_init", FKO_ERROR_CTX_NOT_INITIALIZED);
#endif

    /* Must be initialized
    */
    if(!CTX_INITIALIZED(ctx))
        return FKO_ERROR_CTX_NOT_INITIALIZED;

    /* If spoof_user was not passed in, check for a SPOOF_USER enviroment
     * variable.  If it is set, use its value.
    */
    if(spoof_user != NULL && spoof_user[0] != '\0')
    {
#if HAVE_LIBFIU
        fiu_return_on("fko_set_username_strdup", FKO_ERROR_MEMORY_ALLOCATION);
#endif
        username = strdup(spoof_user);
        if(username == NULL)
            return(FKO_ERROR_MEMORY_ALLOCATION);
        is_user_heap_allocated = 1;
    }
    else
        username = getenv("SPOOF_USER");

    /* Try to get the username from the system.
    */
    if(username == NULL)
    {
        /* Since we've already tried looking at an env variable, try
         * LOGNAME next (and the cuserid() man page recommends this)
        */
        if((username = getenv("LOGNAME")) == NULL)
        {
#ifdef _XOPEN_SOURCE
            /* cuserid will return the effective user (i.e. su or setuid).
            */
            username = cuserid(NULL);
#else
            username = getlogin();
#endif
            /* if we still didn't get a username, continue falling back
            */
            if(username == NULL)
            {
                if((username = getenv("USER")) == NULL)
                {
                    username = strdup("NO_USER");
                    if(username == NULL)
                        return(FKO_ERROR_MEMORY_ALLOCATION);
                    is_user_heap_allocated = 1;
                }
            }
        }
    }

    /* Truncate the username if it is too long.
    */
    if(strnlen(username, MAX_SPA_USERNAME_SIZE) == MAX_SPA_USERNAME_SIZE)
        *(username + MAX_SPA_USERNAME_SIZE - 1) = '\0';

    if((res = validate_username(username)) != FKO_SUCCESS)
    {
        if(is_user_heap_allocated == 1)
            free(username);
#if HAVE_LIBFIU
        fiu_return_on("fko_set_username_valuser", FKO_ERROR_INVALID_DATA);
#endif
        return res;
    }

    /* Just in case this is a subsquent call to this function.  We
     * do not want to be leaking memory.
    */
    if(ctx->username != NULL)
        free(ctx->username);

    ctx->username = strdup(username);

    ctx->state |= FKO_DATA_MODIFIED;

    if(is_user_heap_allocated == 1)
        free(username);

    if(ctx->username == NULL)
        return(FKO_ERROR_MEMORY_ALLOCATION);

    return(FKO_SUCCESS);
}