intptr_t monapi_name_clear_cache(const char* name)
{
    nameCache.remove(name);
    return M_OK;
}