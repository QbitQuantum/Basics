// This does the same as GetVolumePathNamesForVolumeNameW() on Windows XP and
// later. It is built into 32 bit versions of this library to make sure that
// the DLL can load correctly on Windows 2000 as well.
BOOL
WINAPI
ImScsiLegacyGetVolumePathNamesForVolumeName(
__in   LPCWSTR lpszVolumeName,
__out  LPWSTR  lpszVolumePathNames,
__in   DWORD   cchBufferLength,
__out  PDWORD  lpcchReturnLength)
{
    *lpcchReturnLength = 0;

    DWORD dw;
    dw;

    LPWSTR cur_ptr = lpszVolumePathNames;
    LPWSTR end_ptr = lpszVolumePathNames + cchBufferLength;

    WCHAR vol_target[MAX_PATH];

    wcsncpy(vol_target, lpszVolumeName + 4, 44);
    vol_target[44] = 0;

    if (!QueryDosDevice(vol_target, vol_target, _countof(vol_target)))
    {
        return FALSE;
    }

    WHeapMem<WCHAR> dosdevs(UNICODE_STRING_MAX_BYTES,
        HEAP_GENERATE_EXCEPTIONS);

    if (!QueryDosDevice(NULL, dosdevs, (DWORD)dosdevs.Count()))
    {
        return FALSE;
    }

    DWORD good = cchBufferLength >= 2;
    
    *lpcchReturnLength = 2;

    WCHAR dev_target[MAX_PATH];

    SIZE_T length;
    for (LPCWSTR ptr = dosdevs;
        (length = wcslen(ptr)) != 0;
        ptr += length + 1)
    {
        if (good)
        {
            *cur_ptr = 0;
        }

        if ((length != 2) ||
            (ptr[1] != L':') ||
            (!QueryDosDevice(ptr, dev_target, _countof(dev_target))) ||
            (_wcsicmp(dev_target, vol_target) != 0))
        {
            continue;
        }

        *lpcchReturnLength += 4;

        if ((cur_ptr + 4) >= end_ptr)
        {
            good = FALSE;
        }

        if (good)
        {
            swprintf(cur_ptr, L"%ws\\", ptr);
            cur_ptr += 4;
        }
    }

    WCHAR vol_name[50];

    HANDLE volume = FindFirstVolume(vol_name, _countof(vol_name));

    if (volume == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    DWORD error_mode = SetErrorMode(SEM_FAILCRITICALERRORS |
        SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);

    do
    {
        HANDLE vol_mnt = FindFirstVolumeMountPoint(vol_name, dosdevs,
            (DWORD)dosdevs.Count());

        if (vol_mnt == INVALID_HANDLE_VALUE)
        {
            continue;
        }

        do
        {
            WMem<WCHAR> mnt_path;
            
            mnt_path = ImDiskAllocPrintF(L"%1!ws!%2!ws!", vol_name, dosdevs);

            if (!mnt_path)
            {
                continue;
            }

            WCHAR mnt_vol_name[50];
            if (!GetVolumeNameForVolumeMountPoint(mnt_path, mnt_vol_name,
                _countof(mnt_vol_name)))
            {
                continue;
            }

            if (_wcsicmp(mnt_vol_name, lpszVolumeName) == 0)
            {
                if (ImScsiLegacyGetVolumePathNamesForVolumeName(vol_name,
                    vol_target, _countof(vol_target), &dw))
                {
                    mnt_path = ImDiskAllocPrintF(L"%1!ws!%2!ws!", vol_target,
                        dosdevs);

                }

                size_t len = wcslen(mnt_path) + 1;

                *lpcchReturnLength += (DWORD)len;

                if ((cur_ptr + len) >= end_ptr)
                {
                    good = FALSE;
                }

                if (good)
                {
                    wcscpy(cur_ptr, mnt_path);
                    cur_ptr += len;
                }
            }

        } while (FindNextVolumeMountPoint(vol_mnt, dosdevs,
            (DWORD)dosdevs.Count()));
        
        FindVolumeMountPointClose(vol_mnt);

    } while (FindNextVolume(volume, vol_name, _countof(vol_name)));

    FindVolumeClose(volume);

    SetErrorMode(error_mode);

    if (cur_ptr >= end_ptr)
    {
        good = FALSE;
    }

    if (good)
    {
        *cur_ptr = 0;
        ++*lpcchReturnLength;
    }
    else
    {
        SetLastError(ERROR_MORE_DATA);
    }

    return good;
}