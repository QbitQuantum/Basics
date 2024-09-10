            static INT StaticSprintf(
                char *string,
                SIZE_T sizeInBytes,
                const char *Format,
                ...
                )
            {
                va_list arglist;
                va_start(arglist, Format);

#if FL_COMPILER_MSVC
                return _vsprintf_s_l(string, sizeInBytes, Format, NULL, arglist);
#else
                return vsprintf(string, Format, arglist);
#endif
            }