    void debugf(const char* format, ...)
    {
        if (g_bOutput)
        {
            const size_t size = 2048; //Avalanche: Changed to handle longer messages (from 512)
            char         bfr[size];

            va_list vl;
            va_start(vl, format);
            _vsnprintf_s(bfr, size, (size-1), format, vl); //Avalanche: Fix off by one error. 
            va_end(vl);

            ZDebugOutputImpl(bfr);
        }
    }