*/	DEVICE_CMD Read_IO(REBREQ *req)
/*
**		Low level "raw" standard input function.
**
**		The request buffer must be long enough to hold result.
**
**		Result is NOT terminated (the actual field has length.)
**
***********************************************************************/
{
    long total = 0;
    int len;
    BOOL ok;

    if (GET_FLAG(req->modes, RDM_NULL)) {
        req->data[0] = 0;
        return DR_DONE;
    }

    req->actual = 0;

    if (Std_Inp) {

        if (Redir_Inp) { // always UTF-8
            len = MIN(req->length, BUF_SIZE);
            ok = ReadFile(Std_Inp, req->data, len, &total, 0);
        }
        else {
            ok = ReadConsoleW(Std_Inp, Std_Buf, BUF_SIZE-1, &total, 0);
            if (ok) {
                total = WideCharToMultiByte(CP_UTF8, 0, Std_Buf, total, req->data, req->length, 0, 0);
                if (!total) ok = FALSE;
            }
        }

        if (!ok) {
            req->error = GetLastError();
            return DR_ERROR;
        }

        req->actual = total;
    }

    return DR_DONE;
}