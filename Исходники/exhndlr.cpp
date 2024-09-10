void RemoveExceptionHandler(void)
{
    if (exchndlrv)
        RemoveVectoredExceptionHandler(exchndlrv);
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)exchndlr);
    exchndlr = NULL;
    exchndlrv = NULL;
}