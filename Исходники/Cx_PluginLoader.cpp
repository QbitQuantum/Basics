void Cx_PluginLoader::MakeFullPath(wchar_t* fullpath, HMODULE instance,
                                   const wchar_t* path)
{
    if (!path || 0 == path[0] || PathIsRelativeW(path))
    {
        GetModuleFileNameW(instance, fullpath, MAX_PATH);
        PathRemoveFileSpecW(fullpath);
        PathAppendW(fullpath, path);
    }
    else
    {
        wcscpy_s(fullpath, MAX_PATH, path);
    }
    ReplaceSlashes(fullpath);
    PathAddBackslashW(fullpath);
}