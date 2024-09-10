U_CAPI
UPlugTokenReturn U_EXPORT2 debugMemoryPlugin (
                  UPlugData *data,
                  UPlugReason reason,
                  UErrorCode *status) {
    fprintf(stderr,"debugMemoryPlugin: data=%p, reason=%s, status=%s\n", (void*)data, udbg_enumName(UDBG_UPlugReason,(int32_t)reason), u_errorName(*status));
    
    if(reason==UPLUG_REASON_QUERY) {
        uplug_setPlugLevel(data, UPLUG_LEVEL_LOW);
        uplug_setPlugName(data, "Memory Plugin");
    } else if(reason==UPLUG_REASON_LOAD) {
        u_setMemoryFunctions(uplug_getContext(data), &myMemAlloc, &myMemRealloc, &myMemFree, status);
        fprintf(stderr, "MEM: status now %s\n", u_errorName(*status));
    } else if(reason==UPLUG_REASON_UNLOAD) {
        fprintf(stderr, "MEM: not possible to unload this plugin (no way to reset memory functions)...\n");
        uplug_setPlugNoUnload(data, TRUE);
    }

    return UPLUG_TOKEN;
}