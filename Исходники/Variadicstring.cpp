const char *va(const char *fmt, ...)
{
    va_list VarArgs;
    int32_t StringLength = 0;
    char DestinationBuffer[BUFFER_SIZE / LARGEBUFFER_SIZE]{};

    // Create a temporary string from the arguments.
    va_start(VarArgs, fmt);
    StringLength = _vsnprintf_s(DestinationBuffer, BUFFER_SIZE / LARGEBUFFER_SIZE, _TRUNCATE, fmt, VarArgs);
    va_end(VarArgs);

    // Send the string to permanent storage.
    if (StringLength > BUFFER_SIZE / SMALLBUFFER_SIZE)
        return va_large(DestinationBuffer);
    else
        return va_small(DestinationBuffer);
}