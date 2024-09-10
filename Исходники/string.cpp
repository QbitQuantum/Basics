// append a string at the end of the current buffer.
void String::Concatenate(const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);

    std::string str_output;

    const bool bSuccess = String::vformat(fmt, &vl, str_output);

    va_end(vl);

    if (bSuccess) {
        const String strConcat(str_output);

        Concatenate(strConcat);
    }
}