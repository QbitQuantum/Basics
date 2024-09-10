/*--------------------------------------------------------------------------*/
wchar_t *get_full_pathW(wchar_t * _wcFullPath, const wchar_t * _wcPath, size_t _SizeInBytes)
{
    wchar_t *wcResult = NULL;

#if defined(_MSC_VER)
    if (_wcPath)
    {
        wcResult = (wchar_t *) MALLOC(sizeof(wchar_t) * _SizeInBytes);
        if (wcResult)
        {
            _wfullpath(wcResult, _wcPath, _SizeInBytes);
            wcscpy(_wcFullPath, wcResult);
        }
    }
#else
    if (_wcPath)
    {
        char *_Path = wide_string_to_UTF8(_wcPath);

        if (_Path)
        {
            char *_FullPath = (char *)MALLOC(sizeof(char) * (_SizeInBytes));

            if (_FullPath)
            {
                char *rp = NULL;

                rp = realpath(_Path, _FullPath);
                if (!rp)
                {
                    strcpy(_FullPath, _Path);
                    normalizePath(_FullPath);
                }
                wcResult = to_wide_string(_FullPath);
                if (wcResult)
                {
                    wcscpy(_wcFullPath, wcResult);
                }
                FREE(_FullPath);
                _FullPath = NULL;
            }
            FREE(_Path);
            _Path = NULL;
        }
    }
#endif
    return wcResult;
}