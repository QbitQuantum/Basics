static int wxDoVsnprintf(CharType *buf, size_t lenMax,
                         const CharType *format, va_list argptr)
{
    // useful for debugging, to understand if we are really using this function
    // rather than the system implementation
#if 0
    wprintf(L"Using wxCRT_VsnprintfW\n");
#endif

    wxPrintfConvSpecParser<CharType> parser(format);

    wxPrintfArg argdata[wxMAX_SVNPRINTF_ARGUMENTS];

    size_t i;

    // number of characters in the buffer so far, must be less than lenMax
    size_t lenCur = 0;

    if (parser.posarg_present && parser.nonposarg_present)
    {
        buf[0] = 0;
        return -1;      // format strings with both positional and
    }                   // non-positional conversion specifier are unsupported !!

    // on platforms where va_list is an array type, it is necessary to make a
    // copy to be able to pass it to LoadArg as a reference.
    bool ok = true;
    va_list ap;
    wxVaCopy(ap, argptr);

    // now load arguments from stack
    for (i=0; i < parser.nargs && ok; i++)
    {
        // !pspec[i] means that the user forgot a positional parameter (e.g. %$1s %$3s);
        // LoadArg == false means that wxPrintfConvSpec::Parse failed to set the
        // conversion specifier 'type' to a valid value...
        ok = parser.pspec[i] && parser.pspec[i]->LoadArg(&argdata[i], ap);
    }

    va_end(ap);

    // something failed while loading arguments from the variable list...
    // (e.g. the user repeated twice the same positional argument)
    if (!ok)
    {
        buf[0] = 0;
        return -1;
    }

    // finally, process each conversion specifier with its own argument
    const CharType *toparse = format;
    for (i=0; i < parser.nspecs; i++)
    {
        wxPrintfConvSpec<CharType>& spec = parser.specs[i];

        // skip any asterisks, they're processed as part of the conversion they
        // apply to
        if ( spec.m_type == wxPAT_STAR )
            continue;

        // copy in the output buffer the portion of the format string between
        // last specifier and the current one
        size_t tocopy = ( spec.m_pArgPos - toparse );

        lenCur += wxCopyStrWithPercents(lenMax - lenCur, buf + lenCur,
                                        tocopy, toparse);
        if (lenCur == lenMax)
        {
            buf[lenMax - 1] = 0;
            return lenMax+1;      // not enough space in the output buffer !
        }

        // process this specifier directly in the output buffer
        int n = spec.Process(buf+lenCur, lenMax - lenCur,
                                      &argdata[spec.m_pos], lenCur);
        if (n == -1)
        {
            buf[lenMax-1] = wxT('\0');  // be sure to always NUL-terminate the string
            return lenMax+1;      // not enough space in the output buffer !
        }
        lenCur += n;

        // the +1 is because wxPrintfConvSpec::m_pArgEnd points to the last character
        // of the format specifier, but we are not interested to it...
        toparse = spec.m_pArgEnd + 1;
    }

    // copy portion of the format string after last specifier
    // NOTE: toparse is pointing to the character just after the last processed
    //       conversion specifier
    // NOTE2: the +1 is because we want to copy also the '\0'
    size_t tocopy = wxStrlen(format) + 1  - ( toparse - format ) ;

    lenCur += wxCopyStrWithPercents(lenMax - lenCur, buf + lenCur,
                                    tocopy, toparse) - 1;
    if (buf[lenCur])
    {
        buf[lenCur] = 0;
        return lenMax+1;     // not enough space in the output buffer !
    }

    // Don't do:
    //      wxASSERT(lenCur == wxStrlen(buf));
    // in fact if we embedded NULLs in the output buffer (using %c with a '\0')
    // such check would fail

    return lenCur;
}