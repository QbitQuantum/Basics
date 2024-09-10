int StackTraceResolverImpl<ObjectFileFormat::Windows>::resolve(
                                                    StackTrace *stackTrace,
                                                    bool              demangle)
    // Given a specified stack trace object 'stackTrace' of stack trace frames
    // with only their 'address' fields valid, set as many other fields of the
    // frames as possible.  The 'demangle' argument is ignored, demangling
    // always happens on Windows.  Return 0 if successful and a non-zero value
    // otherwise.
{
    typedef bsl::map<HMODULE, const char *> LibNameMap;

    bdlma::HeapBypassAllocator hbpAlloc;

    bslmt::QLockGuard guard(&DbghelpDllImpl_Windows::qLock());

    DbghelpDllImpl_Windows::symSetOptions(SYMOPT_NO_PROMPTS
                                          | SYMOPT_LOAD_LINES
                                          | SYMOPT_DEFERRED_LOADS);

    //                                    | SYMOPT_DEBUG);

    int numFrames = stackTrace->length();
    LibNameMap libNameMap(&hbpAlloc);
    char *libNameBuf = (char *) hbpAlloc.allocate(MAX_PATH);

    enum { MAX_SYMBOL_BUF_NAME_LENGTH = 2000 };
#ifdef BSLS_PLATFORM_CPU_32_BIT
    enum { SIZEOF_SEGMENT = sizeof(SYMBOL_INFO) +
                                  MAX_SYMBOL_BUF_NAME_LENGTH * sizeof(TCHAR) };
    SYMBOL_INFO *sym = (SYMBOL_INFO*) hbpAlloc.allocate(SIZEOF_SEGMENT);
#else
    enum { SIZEOF_SEGMENT = sizeof(IMAGEHLP_SYMBOL64) +
                                  MAX_SYMBOL_BUF_NAME_LENGTH * sizeof(TCHAR) };
    IMAGEHLP_SYMBOL64 *sym = (IMAGEHLP_SYMBOL64 *)
                                             hbpAlloc.allocate(SIZEOF_SEGMENT);
#endif

    for (int i = 0; i < numFrames; ++i) {
        StackTraceFrame *frame = &(*stackTrace)[i];
        DWORD64 address = (DWORD64) frame->address();

        IMAGEHLP_LINE64 line;
        ZeroMemory(&line, sizeof(IMAGEHLP_LINE64));

        line.SizeOfStruct = sizeof(line);
        DWORD offsetFromLine;
        int rc = DbghelpDllImpl_Windows::symGetLineFromAddr64(address,
                                                              &offsetFromLine,
                                                              &line);
        if (rc) {
            frame->setSourceFileName(line.FileName);
            frame->setLineNumber(line.LineNumber);
        }
        else {
            reportError("stack trace resolver error: symGetLineFromAddr64"
                        " error code: ");
        }
        DWORD64 offsetFromSymbol = 0;
        ZeroMemory(sym, SIZEOF_SEGMENT);
        sym->SizeOfStruct = sizeof(*sym);
#ifdef BSLS_PLATFORM_CPU_32_BIT
        sym->MaxNameLen = MAX_SYMBOL_BUF_NAME_LENGTH;
        rc = DbghelpDllImpl_Windows::symFromAddr(address,
                                                 &offsetFromSymbol,
                                                 sym);
#else
        BSLMF_ASSERT(sizeof(void *) == 8);
        sym->MaxNameLength = MAX_SYMBOL_BUF_NAME_LENGTH;
        rc = DbghelpDllImpl_Windows::symGetSymFromAddr64(address,
                                                         &offsetFromSymbol,
                                                         sym);
#endif
        if (rc) {
            // windows is always demangled

            ((TCHAR *) sym)[SIZEOF_SEGMENT - 1] = 0;
            frame->setMangledSymbolName(sym->Name);
            frame->setSymbolName(frame->mangledSymbolName());
            frame->setOffsetFromSymbol((bsl::size_t) offsetFromSymbol);
        }
        else {
#ifdef BSLS_PLATFORM_CPU_32_BIT
            reportError("stack trace resolver error: SymFromAddr"
                        " error code: ");
#else
            reportError("stack trace resolver error: SymGetSymFromAddr64"
                        " error code: ");
#endif
        }

        HMODULE hModule = NULL;
        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery((LPCVOID) address, &mbi, sizeof(mbi))) {
            hModule = (HMODULE)(mbi.AllocationBase);
        }
        LibNameMap::iterator it = libNameMap.find(hModule);
        if (libNameMap.end() != it) {
            // If the library name in the map is "", leave the library file
            // name in the frame null.

            if (*it->second) {
                frame->setLibraryFileName(it->second);
            }
        }
        else {
            rc = GetModuleFileNameA(hModule,
                                    libNameBuf,
                                    MAX_PATH);
            libNameBuf[MAX_PATH-1] = 0;
            if (!rc) {
                // Failed.  Put a null lib name into the map so we won't waste
                // time looking up the same library again.  Leave the
                // libraryFileName in the frame null.

                libNameMap[hModule] = bdlb::String::copy("", &hbpAlloc);
            }
            else {
                frame->setLibraryFileName(libNameBuf);
                libNameMap[hModule] = frame->libraryFileName().c_str();
            }
        }
    }

    return 0;
}