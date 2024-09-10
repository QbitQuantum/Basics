/**
 * Execute an MCI command string.
 *
 * @return              @c true, if successful.
 */
static int sendMCICmd(char* returnInfo, int returnLength,
                      const char *format, ...)
{
    char                buf[300];
    va_list             args;
    MCIERROR            error;

    va_start(args, format);
    dd_vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    if((error = mciSendStringA(buf, returnInfo, returnLength, NULL)))
    {
        mciGetErrorStringA(error, buf, 300);
        Con_Message("DM_WinCD: %s", buf);

        return false;
    }

    return true;
}