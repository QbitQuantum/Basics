static HRESULT WINAPI EnumWorkItems_Next(IEnumWorkItems *iface, ULONG count, LPWSTR **names, ULONG *fetched)
{
    static const WCHAR tasksW[] = { '\\','T','a','s','k','s','\\','*',0 };
    EnumWorkItemsImpl *This = impl_from_IEnumWorkItems(iface);
    WCHAR path[MAX_PATH];
    WIN32_FIND_DATAW data;
    ULONG enumerated, allocated, dummy;
    LPWSTR *list;
    HRESULT hr = S_FALSE;

    TRACE("(%p)->(%u %p %p)\n", This, count, names, fetched);

    if (!count || !names || (!fetched && count > 1)) return E_INVALIDARG;

    if (!fetched) fetched = &dummy;

    *names = NULL;
    *fetched = 0;
    enumerated = 0;
    list = NULL;

    if (This->handle == INVALID_HANDLE_VALUE)
    {
        GetWindowsDirectoryW(path, MAX_PATH);
        lstrcatW(path, tasksW);
        This->handle = FindFirstFileW(path, &data);
        if (This->handle == INVALID_HANDLE_VALUE)
            return S_FALSE;
    }
    else
    {
        if (!FindNextFileW(This->handle, &data))
            return S_FALSE;
    }

    allocated = 64;
    list = CoTaskMemAlloc(allocated * sizeof(list[0]));
    if (!list) return E_OUTOFMEMORY;

    do
    {
        if (is_file(&data))
        {
            if (enumerated >= allocated)
            {
                LPWSTR *new_list;
                allocated *= 2;
                new_list = CoTaskMemRealloc(list, allocated * sizeof(list[0]));
                if (!new_list)
                {
                    hr = E_OUTOFMEMORY;
                    break;
                }
                list = new_list;
            }

            list[enumerated] = CoTaskMemAlloc((lstrlenW(data.cFileName) + 1) * sizeof(WCHAR));
            if (!list[enumerated])
            {
                hr = E_OUTOFMEMORY;
                break;
            }

            lstrcpyW(list[enumerated], data.cFileName);
            enumerated++;

            if (enumerated >= count)
            {
                hr = S_OK;
                break;
            }
        }
    } while (FindNextFileW(This->handle, &data));

    if (FAILED(hr))
        free_list(list, enumerated);
    else
    {
        *fetched = enumerated;
        *names = list;
    }

    return hr;
}