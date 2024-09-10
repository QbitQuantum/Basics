void warningMessage(const char *subsystem, const char *warningFormat, ...) {
    va_list args;
    char buffer1[300], buffer2[300];

    va_start(args, warningFormat);
    vsprintf_s(buffer1, sizeof(buffer1), warningFormat, args);
    va_end(args);

    sprintf_s(buffer2, sizeof(buffer2), "%s: %s", subsystem, buffer1);
    warningMessage_internal(buffer2);
}