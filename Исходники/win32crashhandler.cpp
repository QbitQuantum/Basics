void installCrashHandler()
{
    SetUnhandledExceptionFilter(ExceptionHandler);
}