    longint LongInt::Parse(const char* s, int /*length*/)
    {
        if (s)
        {
#           if (defined(BIBIM_PLATFORM_WINDOWS))
                return static_cast<longint>(_atoi64(s));
#           else
                return static_cast<longint>(atoll(s));
#           endif
        }
        else
            return 0;
    }