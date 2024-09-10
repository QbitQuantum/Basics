static void *
find_gl_symbol (void *handle,
                __eglMustCastToProperFunctionPointerType (*getProcAddress) (const char *procname),
                const char *symbol_name)
{
    void *symbol = dlsym (handle, symbol_name);
    if (symbol == NULL)
        symbol = getProcAddress (symbol_name);
    return symbol;
}