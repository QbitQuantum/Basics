/*@-globs -mods@*/	/* XXX hide rpmGlobalMacroContext mods for now. */
rpmlua rpmluaNew(void)
{
    rpmlua lua = rpmluaGetPool(_rpmluaPool);
    lua_State *L = lua_open();
    /*@-readonlytrans -nullassign @*/
    /*@observer@*/ /*@unchecked@*/
    static const luaL_reg lualibs[] = {
        /* standard LUA libraries */
        {"", luaopen_base},
        /* XXX 5.1.4 internal has not */
#if defined(LUA_COLIBNAME) && LUA_VERSION_NUM > 501
        {LUA_COLIBNAME, luaopen_coroutine},
#endif
#if defined(LUA_TABLIBNAME)
        {LUA_TABLIBNAME, luaopen_table},
#endif
#if defined(LUA_IOLIBNAME)
        {LUA_IOLIBNAME, luaopen_io},
#endif
#if defined(LUA_OSLIBNAME)
        {LUA_OSLIBNAME, luaopen_os},
#endif
#if defined(LUA_STRLIBNAME)
        {LUA_STRLIBNAME, luaopen_string},
#endif
#if defined(LUA_BITLIBNAME)	/* XXX lua >= 5.2.0 only */
        {LUA_BITLIBNAME, luaopen_bit32},
#endif
#if defined(LUA_MATHLIBNAME)
        {LUA_MATHLIBNAME, luaopen_math},
#endif
#if defined(LUA_DBLIBNAME)
        {LUA_DBLIBNAME, luaopen_debug},
#endif
#if defined(LUA_LOADLIBNAME)
        {LUA_LOADLIBNAME, luaopen_package},
#endif
#ifdef	WITH_SYCK
        {"lsyck", luaopen_syck},
#endif	/* WITH_SYCK */
        /* local LUA libraries (RPM only) */
#ifdef WITH_LUA_INTERNAL
        {"posix", luaopen_posix},
#ifdef	HACK
        {"rex_posix", luaopen_rex_posix},
        {"rex_pcre", luaopen_rex_pcre},
#endif
        {"uuid", luaopen_uuid},
        {"wrs", luaopen_wrs},
#ifdef	USE_LUA_CRYPTO		/* XXX external lua modules instead. */
        {"crypto", luaopen_crypto},
        {"lxp", luaopen_lxp},
#endif
#ifdef	USE_LUA_SOCKET		/* XXX external lua modules instead. */
        {"socket", luaopen_socket_core},
#endif
        {"local", luaopen_local},
#endif
        {"rpm", luaopen_rpm},
        {NULL, NULL},
    };
    /*@=readonlytrans =nullassign @*/
    /*@observer@*/ /*@unchecked@*/
    const luaL_reg *lib = lualibs;
    char *path_buf;
    char *path_next;
    char *path;

    lua->L = L;
    lua->pushsize = 0;
    lua->storeprint = 0;
    /* XXX TODO: use an rpmiob here. */
    lua->printbufsize = 0;
    lua->printbufused = 0;
    lua->printbuf = NULL;

    for (; lib->name; lib++) {
        /*@-noeffectuncon@*/
        lua_pushcfunction(L, lib->func);
        lua_pushstring(L, lib->name);
        lua_call(L, 1, 0);
        /*@=noeffectuncon@*/
    }
    {   const char * _lua_path = rpmGetPath(rpmluaPath, NULL);
        if (_lua_path != NULL) {
            lua_pushliteral(L, "LUA_PATH");
            lua_pushstring(L, _lua_path);
            _lua_path = _free(_lua_path);
        }
    }
#if defined(LUA_GLOBALSINDEX)
    lua_rawset(L, LUA_GLOBALSINDEX);
#else
    lua_pushglobaltable(L);
#endif
    lua_pushliteral(L, "print");
    lua_pushcfunction(L, rpm_print);
#if defined(LUA_GLOBALSINDEX)
    lua_rawset(L, LUA_GLOBALSINDEX);
#else
    lua_pushglobaltable(L);
#endif
    rpmluaSetData(lua, "lua", lua);

    /* load all standard RPM Lua script files */
    path_buf = xstrdup(rpmluaFiles);
    for (path = path_buf; path != NULL && *path != '\0'; path = path_next) {
        const char **av;
        struct stat st;
        int ac, i;

        /* locate start of next path element */
        path_next = strchr(path, ':');
        if (path_next != NULL && *path_next == ':')
            *path_next++ = '\0';
        else
            path_next = path + strlen(path);

        /* glob-expand the path element */
        ac = 0;
        av = NULL;
        if ((i = rpmGlob(path, &ac, &av)) != 0)
            continue;

        /* work-off each resulting file from the path element */
        for (i = 0; i < ac; i++) {
            const char *fn = av[i];
            if (fn[0] == '@' /* attention */) {
                fn++;
#if defined(RPM_VENDOR_OPENPKG) /* stick-with-rpm-file-sanity-checking */ || \
    !defined(POPT_ERROR_BADCONFIG)	/* XXX POPT 1.15 retrofit */
                if (!rpmSecuritySaneFile(fn))
#else
                if (!poptSaneFile(fn))
#endif
                {
                    rpmlog(RPMLOG_WARNING, "existing RPM Lua script file \"%s\" considered INSECURE -- not loaded\n", fn);
                    /*@innercontinue@*/ continue;
                }
            }
            if (Stat(fn, &st) != -1)
                (void)rpmluaRunScriptFile(lua, fn);
            av[i] = _free(av[i]);
        }
        av = _free(av);
    }
    path_buf = _free(path_buf);

    return ((rpmlua)rpmioLinkPoolItem((rpmioItem)lua, __FUNCTION__, __FILE__, __LINE__));
}