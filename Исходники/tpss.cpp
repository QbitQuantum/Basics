static const char* tpss_extract_mod_name_with_ext(const char* full)
{
    const char *slash = NULL;
    char *module_name = NULL;

    if (full)
    {
        slash = strrchr(full, '\\');

        module_name = _strlwr(_strdup(++slash));
    }

    return module_name;
}