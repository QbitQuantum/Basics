    /**
     * Print stack trace (using a specified stack context) to "os"
     * 
     * @param context   CONTEXT record for stack trace
     * @param os        ostream& to receive printed stack backtrace
     */
    void printWindowsStackTrace( CONTEXT& context, std::ostream& os ) {
        SimpleMutex::scoped_lock lk(_stackTraceMutex);
        HANDLE process = GetCurrentProcess();
        BOOL ret = SymInitialize(process, getSymbolSearchPath(process), TRUE);
        if ( ret == FALSE ) {
            DWORD dosError = GetLastError();
            log() << "Stack trace failed, SymInitialize failed with error " <<
                    std::dec << dosError << std::endl;
            return;
        }
        DWORD options = SymGetOptions();
        options |= SYMOPT_LOAD_LINES | SYMOPT_FAIL_CRITICAL_ERRORS;
        SymSetOptions( options );

        STACKFRAME64 frame64;
        memset( &frame64, 0, sizeof(frame64) );

#if defined(_M_AMD64)
        DWORD imageType = IMAGE_FILE_MACHINE_AMD64;
        frame64.AddrPC.Offset = context.Rip;
        frame64.AddrFrame.Offset = context.Rbp;
        frame64.AddrStack.Offset = context.Rsp;
#elif defined(_M_IX86)
        DWORD imageType = IMAGE_FILE_MACHINE_I386;
        frame64.AddrPC.Offset = context.Eip;
        frame64.AddrFrame.Offset = context.Ebp;
        frame64.AddrStack.Offset = context.Esp;
#else
#error Neither _M_IX86 nor _M_AMD64 were defined
#endif
        frame64.AddrPC.Mode = AddrModeFlat;
        frame64.AddrFrame.Mode = AddrModeFlat;
        frame64.AddrStack.Mode = AddrModeFlat;

        const size_t nameSize = 1024;
        const size_t symbolBufferSize = sizeof(SYMBOL_INFO) + nameSize;
        std::unique_ptr<char[]> symbolCharBuffer( new char[symbolBufferSize] );
        memset( symbolCharBuffer.get(), 0, symbolBufferSize );
        SYMBOL_INFO* symbolBuffer = reinterpret_cast<SYMBOL_INFO*>( symbolCharBuffer.get() );
        symbolBuffer->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbolBuffer->MaxNameLen = nameSize;

        // build list
        std::vector<TraceItem> traceList;
        TraceItem traceItem;
        size_t moduleWidth = 0;
        size_t sourceWidth = 0;
        for ( size_t i = 0; i < maxBackTraceFrames; ++i ) {
            ret = StackWalk64( imageType,
                               process,
                               GetCurrentThread(),
                               &frame64,
                               &context,
                               NULL,
                               NULL,
                               NULL,
                               NULL );
            if ( ret == FALSE || frame64.AddrReturn.Offset == 0 ) {
                break;
            }
            DWORD64 address = frame64.AddrPC.Offset;
            getModuleName( process, address, &traceItem.moduleName );
            size_t width = traceItem.moduleName.length();
            if ( width > moduleWidth ) {
                moduleWidth = width;
            }
            getSourceFileAndLineNumber( process, address, &traceItem.sourceAndLine );
            width = traceItem.sourceAndLine.length();
            if ( width > sourceWidth ) {
                sourceWidth = width;
            }
            getsymbolAndOffset( process, address, symbolBuffer, &traceItem.symbolAndOffset );
            traceList.push_back( traceItem );
        }
        SymCleanup( process );

        // print list
        ++moduleWidth;
        ++sourceWidth;
        size_t frameCount = traceList.size();
        for ( size_t i = 0; i < frameCount; ++i ) {
            std::stringstream ss;
            ss << traceList[i].moduleName << " ";
            size_t width = traceList[i].moduleName.length();
            while ( width < moduleWidth ) {
                ss << " ";
                ++width;
            }
            ss << traceList[i].sourceAndLine << " ";
            width = traceList[i].sourceAndLine.length();
            while ( width < sourceWidth ) {
                ss << " ";
                ++width;
            }
            ss << traceList[i].symbolAndOffset;
            log() << ss.str() << std::endl;
        }
    }