void
NewHandler::init() {
    JNIEnv *env = (JNIEnv *)JNU_GetEnv(jvm, JNI_VERSION_1_2);

#ifdef OUTOFMEM_TEST
    alloc_lock = new CriticalSection();
    logfile = fopen("java.awt.outofmem.txt", "w");
    DASSERT(logfile);
    thread_seeded = TlsAlloc();
    DASSERT(thread_seeded != TLS_OUT_OF_INDEXES);
#endif

    // use new handler for operator new and malloc
    _set_new_mode(1);

    // set the function which will be called when operator new or
    // malloc runs out of memory
    _set_new_handler((_PNH)NewHandler::handler);
}