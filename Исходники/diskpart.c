VOID
PrintResourceString(INT resID, ...)
{
    WCHAR szMsg[3072];
    va_list arg_ptr;

    va_start(arg_ptr, resID);
    LoadStringW(GetModuleHandle(NULL), resID, szMsg, 3072);
    vwprintf(szMsg, arg_ptr);
    va_end(arg_ptr);
}