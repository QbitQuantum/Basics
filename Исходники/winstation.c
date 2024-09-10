BOOL
WriteToLogPrintfV(
    IN PLOG_FILE LogFile,
    IN LPCWSTR Format,
    IN va_list args)
{
    StringCbVPrintfW(LogFile->pBuffer,
                     LogFile->cbBufferSize,
                     Format, args);

    return WriteToLog(LogFile,
                      LogFile->pBuffer,
                      wcslen(LogFile->pBuffer) * sizeof(WCHAR));
}