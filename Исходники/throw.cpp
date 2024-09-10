__CxxThrowException(
#endif
        void*           pExceptionObject,   // The object thrown
        _ThrowInfo*     pThrowInfo          // Everything we need to know about it
) {
        EHTRACE_ENTER_FMT1("Throwing object @ 0x%p", pExceptionObject);

        static const EHExceptionRecord ExceptionTemplate = { // A generic exception record
            EH_EXCEPTION_NUMBER,            // Exception number
            EXCEPTION_NONCONTINUABLE,       // Exception flags (we don't do resume)
            NULL,                           // Additional record (none)
            NULL,                           // Address of exception (OS fills in)
            EH_EXCEPTION_PARAMETERS,        // Number of parameters
            {   EH_MAGIC_NUMBER1,           // Our version control magic number
                NULL,                       // pExceptionObject
                NULL,
#if _EH_RELATIVE_OFFSETS
                NULL                        // Image base of thrown object
#endif
            }                      // pThrowInfo
        };
        EHExceptionRecord ThisException = ExceptionTemplate;    // This exception

        ThrowInfo* pTI = (ThrowInfo*)pThrowInfo;
        if (pTI && (THROW_ISWINRT( (*pTI) ) ) )
        {
            ULONG_PTR *exceptionInfoPointer = *reinterpret_cast<ULONG_PTR**>(pExceptionObject);
            exceptionInfoPointer--; // The pointer to the ExceptionInfo structure is stored sizeof(void*) infront of each WinRT Exception Info.

            WINRTEXCEPTIONINFO* wei = reinterpret_cast<WINRTEXCEPTIONINFO*>(*exceptionInfoPointer);
            pTI = wei->throwInfo;
        }

        //
        // Fill in the blanks:
        //
        ThisException.params.pExceptionObject = pExceptionObject;
        ThisException.params.pThrowInfo = pTI;
#if _EH_RELATIVE_OFFSETS
        PVOID ThrowImageBase = RtlPcToFileHeader((PVOID)pTI, &ThrowImageBase);
        ThisException.params.pThrowImageBase = ThrowImageBase;
#endif

        //
        // If the throw info indicates this throw is from a pure region,
        // set the magic number to the Pure one, so only a pure-region
        // catch will see it.
        //
        // Also use the Pure magic number on Win64 if we were unable to
        // determine an image base, since that was the old way to determine
        // a pure throw, before the TI_IsPure bit was added to the FuncInfo
        // attributes field.
        //
        if (pTI != NULL)
        {
            if (THROW_ISPURE(*pTI))
            {
                ThisException.params.magicNumber = EH_PURE_MAGIC_NUMBER1;
            }
#if _EH_RELATIVE_OFFSETS
            else if (ThrowImageBase == NULL)
            {
                ThisException.params.magicNumber = EH_PURE_MAGIC_NUMBER1;
            }
#endif
        }

        //
        // Hand it off to the OS:
        //

        EHTRACE_EXIT;
#if defined(_M_X64) && defined(_NTSUBSET_)
        RtlRaiseException( (PEXCEPTION_RECORD) &ThisException );
#else
        RaiseException( ThisException.ExceptionCode,
                        ThisException.ExceptionFlags,
                        ThisException.NumberParameters,
                        (PULONG_PTR)&ThisException.params );
#endif
}