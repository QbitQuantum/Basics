void * dlopen(const char * path, int mode)
{
    const struct stat * sbuf;
    struct dlstatus * dls;
    const char * fullPath;
    if (!path)
    {
        return &mainStatus;
    }    
    if (!(sbuf = findFile(path, &fullPath)))
    {
        error("file \"%s\" not found", path);
        return NULL;
    }
    /* Now checks that it hasn't been closed already */
    if ((dls = lookupStatus(sbuf)) && (dls->refs > 0))
    {
        /* debug("status found"); */
        return reference(dls, mode);    
    }
    if (isFlagSet(mode, RTLD_NOLOAD))
    {
        error("no existing handle and RTLD_NOLOAD specified");
        return NULL;
    }
    return reference(loadModule(fullPath, sbuf, mode),mode);
}