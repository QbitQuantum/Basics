/*
 * Query 3Dfx hardware presence/kind
 */
static GLboolean GLAPIENTRY fxQueryHardware (void)
{
 if (TDFX_DEBUG & VERBOSE_DRIVER) {
    fprintf(stderr, "fxQueryHardware()\n");
 }

 if (!glbGlideInitialized) {
    grGlideInit();
    glb3DfxPresent = FX_grSstQueryHardware(&glbHWConfig);

    glbGlideInitialized = 1;

#if defined(__WIN32__)
    _onexit((_onexit_t) cleangraphics);
#elif defined(__linux__)
    /* Only register handler if environment variable is not defined. */
    if (!getenv("MESA_FX_NO_SIGNALS")) {
       atexit(cleangraphics);
    }
#endif
 }

 return glb3DfxPresent;
}