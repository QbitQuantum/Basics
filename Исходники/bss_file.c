static long MS_CALLBACK file_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;
    FILE *fp = (FILE *)b->ptr;
    FILE **fpp;
    char p[4];
    int st;

    switch (cmd) {
    case BIO_C_FILE_SEEK:
    case BIO_CTRL_RESET:
        if (b->flags & BIO_FLAGS_UPLINK)
            ret = (long)UP_fseek(b->ptr, num, 0);
        else
            ret = (long)fseek(fp, num, 0);
        break;
    case BIO_CTRL_EOF:
        if (b->flags & BIO_FLAGS_UPLINK)
            ret = (long)UP_feof(fp);
        else
            ret = (long)feof(fp);
        break;
    case BIO_C_FILE_TELL:
    case BIO_CTRL_INFO:
        if (b->flags & BIO_FLAGS_UPLINK)
            ret = UP_ftell(b->ptr);
        else
            ret = ftell(fp);
        break;
    case BIO_C_SET_FILE_PTR:
        file_free(b);
        b->shutdown = (int)num & BIO_CLOSE;
        b->ptr = ptr;
        b->init = 1;
#  if BIO_FLAGS_UPLINK!=0
#   if defined(__MINGW32__) && defined(__MSVCRT__) && !defined(_IOB_ENTRIES)
#    define _IOB_ENTRIES 20
#   endif
        /* Safety net to catch purely internal BIO_set_fp calls */
#   if defined(_MSC_VER) && _MSC_VER>=1900
        if (ptr == stdin || ptr == stdout || ptr == stderr)
            BIO_clear_flags(b, BIO_FLAGS_UPLINK);
#   elif defined(_IOB_ENTRIES)
        if ((size_t)ptr >= (size_t)stdin &&
            (size_t)ptr < (size_t)(stdin + _IOB_ENTRIES))
            BIO_clear_flags(b, BIO_FLAGS_UPLINK);
#   endif
#  endif
#  ifdef UP_fsetmod
        if (b->flags & BIO_FLAGS_UPLINK)
            UP_fsetmod(b->ptr, (char)((num & BIO_FP_TEXT) ? 't' : 'b'));
        else
#  endif
        {
#  if defined(OPENSSL_SYS_WINDOWS)
            int fd = _fileno((FILE *)ptr);
            if (num & BIO_FP_TEXT)
                _setmode(fd, _O_TEXT);
            else
                _setmode(fd, _O_BINARY);
#  elif defined(OPENSSL_SYS_NETWARE) && defined(NETWARE_CLIB)
            int fd = fileno((FILE *)ptr);
            /* Under CLib there are differences in file modes */
            if (num & BIO_FP_TEXT)
                setmode(fd, O_TEXT);
            else
                setmode(fd, O_BINARY);
#  elif defined(OPENSSL_SYS_MSDOS)
            int fd = fileno((FILE *)ptr);
            /* Set correct text/binary mode */
            if (num & BIO_FP_TEXT)
                _setmode(fd, _O_TEXT);
            /* Dangerous to set stdin/stdout to raw (unless redirected) */
            else {
                if (fd == STDIN_FILENO || fd == STDOUT_FILENO) {
                    if (isatty(fd) <= 0)
                        _setmode(fd, _O_BINARY);
                } else
                    _setmode(fd, _O_BINARY);
            }
#  elif defined(OPENSSL_SYS_OS2) || defined(OPENSSL_SYS_WIN32_CYGWIN)
            int fd = fileno((FILE *)ptr);
            if (num & BIO_FP_TEXT)
                setmode(fd, O_TEXT);
            else
                setmode(fd, O_BINARY);
#  endif
        }
        break;
    case BIO_C_SET_FILENAME:
        file_free(b);
        b->shutdown = (int)num & BIO_CLOSE;
        if (num & BIO_FP_APPEND) {
            if (num & BIO_FP_READ)
                BUF_strlcpy(p, "a+", sizeof p);
            else
                BUF_strlcpy(p, "a", sizeof p);
        } else if ((num & BIO_FP_READ) && (num & BIO_FP_WRITE))
            BUF_strlcpy(p, "r+", sizeof p);
        else if (num & BIO_FP_WRITE)
            BUF_strlcpy(p, "w", sizeof p);
        else if (num & BIO_FP_READ)
            BUF_strlcpy(p, "r", sizeof p);
        else {
            BIOerr(BIO_F_FILE_CTRL, BIO_R_BAD_FOPEN_MODE);
            ret = 0;
            break;
        }
#  if defined(OPENSSL_SYS_MSDOS) || defined(OPENSSL_SYS_WINDOWS) || defined(OPENSSL_SYS_OS2) || defined(OPENSSL_SYS_WIN32_CYGWIN)
        if (!(num & BIO_FP_TEXT))
            strcat(p, "b");
        else
            strcat(p, "t");
#  endif
#  if defined(OPENSSL_SYS_NETWARE)
        if (!(num & BIO_FP_TEXT))
            strcat(p, "b");
        else
            strcat(p, "t");
#  endif
        fp = file_fopen(ptr, p);
        if (fp == NULL) {
            SYSerr(SYS_F_FOPEN, get_last_sys_error());
            ERR_add_error_data(5, "fopen('", ptr, "','", p, "')");
            BIOerr(BIO_F_FILE_CTRL, ERR_R_SYS_LIB);
            ret = 0;
            break;
        }
        b->ptr = fp;
        b->init = 1;
        BIO_clear_flags(b, BIO_FLAGS_UPLINK); /* we did fopen -> we disengage
                                               * UPLINK */
        break;
    case BIO_C_GET_FILE_PTR:
        /* the ptr parameter is actually a FILE ** in this case. */
        if (ptr != NULL) {
            fpp = (FILE **)ptr;
            *fpp = (FILE *)b->ptr;
        }
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = (long)b->shutdown;
        break;
    case BIO_CTRL_SET_CLOSE:
        b->shutdown = (int)num;
        break;
    case BIO_CTRL_FLUSH:
        st = b->flags & BIO_FLAGS_UPLINK
                ? UP_fflush(b->ptr) : fflush((FILE *)b->ptr);
        if (st == EOF) {
            SYSerr(SYS_F_FFLUSH, get_last_sys_error());
            ERR_add_error_data(1, "fflush()");
            BIOerr(BIO_F_FILE_CTRL, ERR_R_SYS_LIB);
            ret = 0;
        }
        break;
    case BIO_CTRL_DUP:
        ret = 1;
        break;

    case BIO_CTRL_WPENDING:
    case BIO_CTRL_PENDING:
    case BIO_CTRL_PUSH:
    case BIO_CTRL_POP:
    default:
        ret = 0;
        break;
    }
    return (ret);
}