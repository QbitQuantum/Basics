void Debug::AssertMessage(const char* aFileName, int aLine, const char* aFunctionName, const char* aString)
{
    time_t t = time(0); // get current system time;
    struct tm timeinfo;
    localtime_s(&timeinfo, &t);
    myDebugFile << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << " error" << std::endl;
    myDebugFile << "	Error: " << aString << " in function " << aFunctionName << " line " << aLine << " in file " << aFileName << std::endl;
    myDebugFile.flush();


    StackWalker aStackWalker;
    aStackWalker.ShowCallstack();

    size_t* a(NULL);

    wchar_t tmpFileName[256];
    mbstowcs_s(a, tmpFileName, aFileName, 256);

    wchar_t tmpString[256];
    mbstowcs_s(a, tmpString, aString, 256);

    _wassert(tmpString, tmpFileName, aLine);
}