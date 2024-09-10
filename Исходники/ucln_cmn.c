U_CAPI void U_EXPORT2 ucln_cleanupOne(ECleanupLibraryType libType)
{
    if(libType==UCLN_COMMON) {
#if UCLN_DEBUG_CLEANUP
        fprintf(stderr, "Cleaning up: UCLN_COMMON with u_cleanup, type %d\n", (int)libType);
#endif
        u_cleanup();
    } else {
#if UCLN_DEBUG_CLEANUP
        fprintf(stderr, "Cleaning up: using ucln_cleanup_internal, type %d\n", (int)libType);
#endif
        ucln_cleanup_internal(libType);
    }
}