static size_t getUnderestimatedStackSize()
{
#if defined(__GLIBC__) || OS(ANDROID) || OS(FREEBSD)
    // We cannot get the stack size in these platforms because
    // pthread_getattr_np() can fail for the main thread.
    // This is OK because ThreadState::current() doesn't use the stack size
    // in these platforms.
    return 0;
#elif OS(MACOSX)
    return pthread_get_stacksize_np(pthread_self());
#elif OS(WIN) && COMPILER(MSVC)
    // On Windows stack limits for the current thread are available in
    // the thread information block (TIB). Its fields can be accessed through
    // FS segment register on x86 and GS segment register on x86_64.
#ifdef _WIN64
    return __readgsqword(offsetof(NT_TIB64, StackBase)) - __readgsqword(offsetof(NT_TIB64, StackLimit));
#else
    return __readfsdword(offsetof(NT_TIB, StackBase)) - __readfsdword(offsetof(NT_TIB, StackLimit));
#endif
#else
    return 0;
#endif
}