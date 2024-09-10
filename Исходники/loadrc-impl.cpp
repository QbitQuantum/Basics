bool GetEnvVar(_In_z_ wchar_t *var, MyString &res)
{
    wchar_t *buffer;
    size_t size;
    _wdupenv_s(&buffer, &size, var);
    if (!size || !buffer)
        return false;
    res = buffer;
    free(buffer); // Don't forget to free the buffer!
    return true;
}