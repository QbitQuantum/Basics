/***********************************************************************
 *      ber_printf     (WLDAP32.@)
 *
 * Encode a berelement structure.
 *
 * PARAMS
 *  berelement [I/O] Pointer to a berelement structure.
 *  fmt        [I]   Format string.
 *  ...        [I]   Values to encode.
 *
 * RETURNS
 *  Success: Non-negative number. 
 *  Failure: LBER_ERROR
 *
 * NOTES
 *  berelement must have been allocated with ber_alloc_t. This function
 *  can be called multiple times to append data.
 */
INT CDECL WLDAP32_ber_printf( BerElement *berelement, PCHAR fmt, ... )
{
#ifdef HAVE_LDAP
    __ms_va_list list;
    int ret = 0;
    char new_fmt[2];

    new_fmt[1] = 0;
    __ms_va_start( list, fmt );
    while (*fmt)
    {
        new_fmt[0] = *fmt++;
        switch(new_fmt[0])
        {
        case 'b':
        case 'e':
        case 'i':
            {
                int i = va_arg( list, int );
                ret = ber_printf( berelement, new_fmt, i );
                break;
            }
        case 'o':
        case 's':
            {
                char *str = va_arg( list, char * );
                ret = ber_printf( berelement, new_fmt, str );
                break;
            }
        case 't':
            {
                unsigned int tag = va_arg( list, unsigned int );
                ret = ber_printf( berelement, new_fmt, tag );
                break;
            }
        case 'v':
            {
                char **array = va_arg( list, char ** );
                ret = ber_printf( berelement, new_fmt, array );
                break;
            }
        case 'V':
            {
                struct berval **array = va_arg( list, struct berval ** );
                ret = ber_printf( berelement, new_fmt, array );
                break;
            }
        case 'X':
            {
                char *str = va_arg( list, char * );
                int len = va_arg( list, int );
                new_fmt[0] = 'B';  /* 'X' is deprecated */
                ret = ber_printf( berelement, new_fmt, str, len );
                break;
            }
        case 'n':
        case '{':
        case '}':
        case '[':
        case ']':
            ret = ber_printf( berelement, new_fmt );
            break;
        default:
            FIXME( "Unknown format '%c'\n", new_fmt[0] );
            ret = -1;
            break;
        }
        if (ret == -1) break;
    }
    __ms_va_end( list );
    return ret;
#else
    return LBER_ERROR;
#endif
}