size_t __cdecl _wcstombs_lk
#else
size_t __cdecl wcstombs
#endif
        (
        char * s,
        const wchar_t * pwcs,
        size_t n
        )
{
        size_t count = 0;
#ifdef _WIN32
        int i, retval;
        char buffer[MB_LEN_MAX];
        BOOL defused = 0;
#endif
        if (s && n == 0)
            /* dest string exists, but 0 bytes converted */
            return (size_t) 0;

        _ASSERTE(pwcs != NULL);

#ifdef _WIN32
#if !defined( _NTSUBSET_ ) && !defined(_POSIX_)

        /* if destination string exists, fill it in */
        if (s)
        {
            if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
            {
                /* C locale: easy and fast */
                while(count < n)
                {
                    if (*pwcs > 255)  /* validate high byte */
                    {
                        errno = EILSEQ;
                        return (size_t)-1;  /* error */
                    }
                    s[count] = (char) *pwcs;
                    if (*pwcs++ == L'\0')
                        return count;
                    count++;
                }
                return count;
            } else {

                if (1 == MB_CUR_MAX)
                {
                    /* If SBCS, one wchar_t maps to one char */

                    /* WideCharToMultiByte will compare past NULL - reset n */
                    if (n > 0)
                        n = wcsncnt(pwcs, n);

                    if (((count=WideCharToMultiByte(__lc_codepage,
                        WC_COMPOSITECHECK | WC_SEPCHARS,
                        pwcs, n, s, n, NULL, &defused)) != 0) && (!defused))
                    {
                        if (*(s+count-1) == '\0')
                            count--; /* don't count NUL */

                        return count;
                    }

                    errno = EILSEQ;
                    return (size_t)-1;
                }
                else {

                    /* If MBCS, wchar_t to char mapping unknown */

                    /* Assume that usually the buffer is large enough */
                    if (((count=WideCharToMultiByte(__lc_codepage,
                        WC_COMPOSITECHECK | WC_SEPCHARS,
                        pwcs, -1, s, n, NULL, &defused)) != 0) && (!defused))
                    {
                        return count - 1; /* don't count NUL */
                    }

                    if (defused || GetLastError() != ERROR_INSUFFICIENT_BUFFER)
                    {
                        errno = EILSEQ;
                        return (size_t)-1;
                    }

                    /* buffer not large enough, must do char by char */
                    while (count < n)
                    {
                        if (((retval = WideCharToMultiByte (__lc_codepage, 0,
                        pwcs, 1, buffer, MB_CUR_MAX, NULL, &defused)) == 0) || defused)
                        {
                            errno = EILSEQ;
                            return (size_t)-1;
                        }

                        if (count + retval > n)
                            return count;

                        for (i = 0; i < retval; i++, count++) /* store character */
                            if((s[count] = buffer[i])=='\0')
                                return count;

                        pwcs++;
                    }

                    return count;
                }
            }
        }
        else { /* s == NULL, get size only, pwcs must be NUL-terminated */

            if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
                return wcslen(pwcs);
            else {
                if (((count=WideCharToMultiByte(__lc_codepage,
                WC_COMPOSITECHECK | WC_SEPCHARS,
                pwcs, -1, NULL, 0, NULL, &defused)) == 0) || (defused))
                {
                    errno = EILSEQ;
                    return (size_t)-1;
                }

                return count - 1;
            }
        }

#else /* _NTSUBSET_/_POSIX_ */

        /* if destination string exists, fill it in */
        if (s)
        {
            NTSTATUS Status;

            Status = RtlUnicodeToMultiByteN(s, n, (PULONG)&count, (wchar_t *)pwcs, (wcslen(pwcs)+1)*sizeof(WCHAR));

            if (NT_SUCCESS(Status))
            {
                return count - 1; /* don't count NUL */
            } else {
                errno = EILSEQ;
                count = (size_t)-1;
            }
        } else { /* s == NULL, get size only, pwcs must be NUL-terminated */
            NTSTATUS Status;

            Status = RtlUnicodeToMultiByteSize((PULONG)&count, (wchar_t *)pwcs, (wcslen(pwcs)+1)*sizeof(WCHAR));

            if (NT_SUCCESS(Status))
            {
                return count - 1; /* don't count NUL */
            } else {
                errno = EILSEQ;
                count = (size_t)-1;
            }
        }

#endif  /* _NTSUBSET_/_POSIX_ */
#else /* _WIN32 */

        /* if destination string exists, fill it in */
        if (s)
        {
            /* C locale: easy and fast */
            while(count < n)
            {
                if (*pwcs > 255)  /* validate high byte */
                {
                    errno = EILSEQ;
                    return (size_t)-1;  /* error */
                }
                s[count] = (char) *pwcs;
                if (*pwcs++ == L'\0')
                    return count;
                count++;
            }
            return count;

        } else { /* s == NULL, get size only, pwcs must be NUL-terminated */
	    const wchar_t *eos = pwcs;

	    while( *eos++ ) ;

	    return( (size_t)(eos - pwcs - 1) );
        }

#endif /* _WIN32 */
}