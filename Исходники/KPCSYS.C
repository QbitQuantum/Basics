BOOL CEXPORT KpcExecute(LPSTR program, ...)
{
    va_list ap;
    int i = 0;
    LPSTR st;
    va_start(ap, program);

    for (st = program; st; st = va_arg(ap, LPSTR)) {
        strcpy(return_buffer + i, st);
        i += strlen(st);
        return_buffer[i++] = ' ';
    }
    return_buffer[i - 1] = '\0';
    GlobalCompact(0L);

    if (WinExec(return_buffer, SW_SHOWNORMAL) < 32)
        return KpcError(hInstThisDll, IDE_COULDNOTSTART, return_buffer, "");

    KppWaitForInputCB();
    return TRUE;
}