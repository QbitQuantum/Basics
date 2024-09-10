static PyObject*
msierror(int status)
{
    int code;
    char buf[2000];
    char *res = buf;
    DWORD size = sizeof(buf);
    MSIHANDLE err = MsiGetLastErrorRecord();

    if (err == 0) {
        switch(status) {
        case ERROR_ACCESS_DENIED:
            PyErr_SetString(MSIError, "access denied");
            return NULL;
        case ERROR_FUNCTION_FAILED:
            PyErr_SetString(MSIError, "function failed");
            return NULL;
        case ERROR_INVALID_DATA:
            PyErr_SetString(MSIError, "invalid data");
            return NULL;
        case ERROR_INVALID_HANDLE:
            PyErr_SetString(MSIError, "invalid handle");
            return NULL;
        case ERROR_INVALID_STATE:
            PyErr_SetString(MSIError, "invalid state");
            return NULL;
        case ERROR_INVALID_PARAMETER:
            PyErr_SetString(MSIError, "invalid parameter");
            return NULL;
        case ERROR_OPEN_FAILED:
            PyErr_SetString(MSIError, "open failed");
            return NULL;
        case ERROR_CREATE_FAILED:
            PyErr_SetString(MSIError, "create failed");
            return NULL;
        default:
            PyErr_Format(MSIError, "unknown error %x", status);
            return NULL;
        }
    }

    code = MsiRecordGetInteger(err, 1); /* XXX code */
    if (MsiFormatRecord(0, err, res, &size) == ERROR_MORE_DATA) {
        res = malloc(size+1);
        if (res == NULL) {
            MsiCloseHandle(err);
            return PyErr_NoMemory();
        }
        MsiFormatRecord(0, err, res, &size);
        res[size]='\0';
    }
    MsiCloseHandle(err);
    PyErr_SetString(MSIError, res);
    if (res != buf)
        free(res);
    return NULL;
}