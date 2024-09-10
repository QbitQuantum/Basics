/* goodG2B() uses the GoodSource with the BadSink */
static void goodG2B()
{
    wchar_t * data;
    wchar_t * *dataPtr1 = &data;
    wchar_t * *dataPtr2 = &data;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    {
        wchar_t * data = *dataPtr1;
        /* FIX: Append a fixed string to data (not user / external input) */
        wcscat(data, L"*.*");
        *dataPtr1 = data;
    }
    {
        wchar_t * data = *dataPtr2;
        {
            wchar_t *args[] = {COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL};
            /* wexecv - specify the path where the command is located */
            /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
            EXECV(COMMAND_INT_PATH, args);
        }
    }
}