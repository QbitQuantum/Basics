ErrRet NotifyAssert(const char* condition, const char* fileName, int lineNumber, const char* formats, ...)
{
    char szBuffer[4096];

    va_list args;
    va_start(args, formats);
//		wvsprintf(szBuffer, formats, args);
    wvsprintfA(szBuffer, formats, args);
    va_end(args);

    std::string filenameStr = fileName;

    // pass the data on to the message box
    ErrRet result = DisplayError("Assert Failed!",
                                 condition,
                                 szBuffer,
                                 filenameStr.c_str(),
                                 lineNumber);
    return result;
}