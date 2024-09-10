APR_DECLARE(apr_status_t) apr_file_seek(apr_file_t *thefile, apr_seek_where_t where, apr_off_t *offset)
{
    apr_finfo_t finfo;
    apr_status_t rc = APR_SUCCESS;

    thefile->eof_hit = 0;

    if (thefile->buffered) {
        switch (where) {
            case APR_SET:
                rc = setptr(thefile, *offset);
                break;

            case APR_CUR:
                rc = setptr(thefile, thefile->filePtr - thefile->dataRead 
                                      + thefile->bufpos + *offset);
                break;

            case APR_END:
                rc = apr_file_info_get(&finfo, APR_FINFO_SIZE, thefile);
                if (rc == APR_SUCCESS)
                    rc = setptr(thefile, finfo.size + *offset);
                break;

            default:
                return APR_EINVAL;
        }

        *offset = thefile->filePtr - thefile->dataRead + thefile->bufpos;
        return rc;
    }
    /* A file opened with APR_FOPEN_XTHREAD has been opened for overlapped i/o.
     * APR must explicitly track the file pointer in this case.
     */
    else if (thefile->pOverlapped || thefile->flags & APR_FOPEN_XTHREAD) {
        switch(where) {
            case APR_SET:
                thefile->filePtr = *offset;
                break;
        
            case APR_CUR:
                thefile->filePtr += *offset;
                break;
        
            case APR_END:
                rc = apr_file_info_get(&finfo, APR_FINFO_SIZE, thefile);
                if (rc == APR_SUCCESS && finfo.size + *offset >= 0)
                    thefile->filePtr = finfo.size + *offset;
                break;

            default:
                return APR_EINVAL;
        }
        *offset = thefile->filePtr;
        return rc;
    }
    else {
        DWORD howmove;
        DWORD offlo = (DWORD)*offset;
        DWORD offhi = (DWORD)(*offset >> 32);

        switch(where) {
            case APR_SET:
                howmove = FILE_BEGIN;   break;
            case APR_CUR:
                howmove = FILE_CURRENT; break;
            case APR_END:
                howmove = FILE_END;     break;
            default:
                return APR_EINVAL;
        }
        offlo = SetFilePointer(thefile->filehand, (LONG)offlo, 
                               (LONG*)&offhi, howmove);
        if (offlo == 0xFFFFFFFF)
            rc = apr_get_os_error();
        else
            rc = APR_SUCCESS;
        /* Since we can land at 0xffffffff we will measure our APR_SUCCESS */
        if (rc == APR_SUCCESS)
            *offset = ((apr_off_t)offhi << 32) | offlo;
        return rc;
    }
}