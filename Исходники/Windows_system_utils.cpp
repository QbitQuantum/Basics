void InitCrashHandler()
{
    SetUnhandledExceptionFilter(StackTraceCrashHandler);
}