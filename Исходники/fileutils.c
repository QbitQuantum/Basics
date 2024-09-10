static int
decode_current_locale(const char* arg, wchar_t **wstr, size_t *wlen,
                      const char **reason, int surrogateescape)
{
    wchar_t *res;
    size_t argsize;
    size_t count;
#ifdef HAVE_MBRTOWC
    unsigned char *in;
    wchar_t *out;
    mbstate_t mbs;
#endif

#ifdef HAVE_BROKEN_MBSTOWCS
    /* Some platforms have a broken implementation of
     * mbstowcs which does not count the characters that
     * would result from conversion.  Use an upper bound.
     */
    argsize = strlen(arg);
#else
    argsize = mbstowcs(NULL, arg, 0);
#endif
    if (argsize != (size_t)-1) {
        if (argsize > PY_SSIZE_T_MAX / sizeof(wchar_t) - 1) {
            return -1;
        }
        res = (wchar_t *)PyMem_RawMalloc((argsize + 1) * sizeof(wchar_t));
        if (!res) {
            return -1;
        }

        count = mbstowcs(res, arg, argsize + 1);
        if (count != (size_t)-1) {
            wchar_t *tmp;
            /* Only use the result if it contains no
               surrogate characters. */
            for (tmp = res; *tmp != 0 &&
                         !Py_UNICODE_IS_SURROGATE(*tmp); tmp++)
                ;
            if (*tmp == 0) {
                if (wlen != NULL) {
                    *wlen = count;
                }
                *wstr = res;
                return 0;
            }
        }
        PyMem_RawFree(res);
    }

    /* Conversion failed. Fall back to escaping with surrogateescape. */
#ifdef HAVE_MBRTOWC
    /* Try conversion with mbrtwoc (C99), and escape non-decodable bytes. */

    /* Overallocate; as multi-byte characters are in the argument, the
       actual output could use less memory. */
    argsize = strlen(arg) + 1;
    if (argsize > PY_SSIZE_T_MAX / sizeof(wchar_t)) {
        return -1;
    }
    res = (wchar_t*)PyMem_RawMalloc(argsize * sizeof(wchar_t));
    if (!res) {
        return -1;
    }

    in = (unsigned char*)arg;
    out = res;
    memset(&mbs, 0, sizeof mbs);
    while (argsize) {
        size_t converted = mbrtowc(out, (char*)in, argsize, &mbs);
        if (converted == 0) {
            /* Reached end of string; null char stored. */
            break;
        }

        if (converted == (size_t)-2) {
            /* Incomplete character. This should never happen,
               since we provide everything that we have -
               unless there is a bug in the C library, or I
               misunderstood how mbrtowc works. */
            goto decode_error;
        }

        if (converted == (size_t)-1) {
            if (!surrogateescape) {
                goto decode_error;
            }

            /* Conversion error. Escape as UTF-8b, and start over
               in the initial shift state. */
            *out++ = 0xdc00 + *in++;
            argsize--;
            memset(&mbs, 0, sizeof mbs);
            continue;
        }

        if (Py_UNICODE_IS_SURROGATE(*out)) {
            if (!surrogateescape) {
                goto decode_error;
            }

            /* Surrogate character.  Escape the original
               byte sequence with surrogateescape. */
            argsize -= converted;
            while (converted--) {
                *out++ = 0xdc00 + *in++;
            }
            continue;
        }
        /* successfully converted some bytes */
        in += converted;
        argsize -= converted;
        out++;
    }
    if (wlen != NULL) {
        *wlen = out - res;
    }
    *wstr = res;
    return 0;

decode_error:
    PyMem_RawFree(res);
    if (wlen) {
        *wlen = in - (unsigned char*)arg;
    }
    if (reason) {
        *reason = "decoding error";
    }
    return -2;
#else   /* HAVE_MBRTOWC */
    /* Cannot use C locale for escaping; manually escape as if charset
       is ASCII (i.e. escape all bytes > 128. This will still roundtrip
       correctly in the locale's charset, which must be an ASCII superset. */
    return decode_ascii(arg, wstr, wlen, reason, surrogateescape);
#endif   /* HAVE_MBRTOWC */
}