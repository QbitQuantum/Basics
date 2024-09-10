    void* MemDefaultAllocator::ReallocAligned(void* pOldPtr, size_t size, size_t alignment, const char* tag, const char* pFile, unsigned int Line)
    {
        BEHAVIAC_UNUSED_VAR(alignment);
        BEHAVIAC_UNUSED_VAR(tag);
        BEHAVIAC_UNUSED_VAR(pFile);
        BEHAVIAC_UNUSED_VAR(Line);

        if (pOldPtr)
        {
#if BEHAVIAC_DEBUG_MEMORY_STATS

            if (m_bEnablePtrSizeRegister)
            {
                ScopedInt_t scopedInt(GetThreadInt());

                if (scopedInt.equal(1))
                {
                    GetPtrSizeRegister().UnRegisterPtr(pOldPtr);
                }
            }

#endif
        }

#if BEHAVIAC_COMPILER_MSVC
        void* p = _aligned_realloc(pOldPtr, size, alignment);
#else
        void* p = realloc(pOldPtr, size);
#endif//BEHAVIAC_COMPILER_MSVC
#if BEHAVIAC_DEBUG_MEMORY_STATS

        if (m_bEnablePtrSizeRegister)
        {
            ScopedInt_t scopedInt(GetThreadInt());

            if (scopedInt.equal(1))
            {
                GetPtrSizeRegister().RegisterPtrSize(p, size);
            }
        }

#endif
        return p;
    }