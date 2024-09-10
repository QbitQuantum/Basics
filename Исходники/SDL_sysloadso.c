void *
SDL_LoadObject(const char *sofile)
{
    LPTSTR tstr = WIN_UTF8ToString(sofile);
#ifdef __WINRT__
    /* WinRT only publically supports LoadPackagedLibrary() for loading .dll
       files.  LoadLibrary() is a private API, and not available for apps
       (that can be published to MS' Windows Store.)
    */
    void *handle = (void *) LoadPackagedLibrary(tstr, 0);
#else
    void *handle = (void *) LoadLibrary(tstr);
#endif
    SDL_free(tstr);

    /* Generate an error message if all loads failed */
    if (handle == NULL) {
        char errbuf[512];
        SDL_strlcpy(errbuf, "Failed loading ", SDL_arraysize(errbuf));
        SDL_strlcat(errbuf, sofile, SDL_arraysize(errbuf));
        WIN_SetError(errbuf);
    }
    return handle;
}