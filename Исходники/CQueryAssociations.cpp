/**************************************************************************
 *  IQueryAssociations_GetString
 *
 * Get a file association string from the registry.
 *
 * PARAMS
 *  cfFlags  [I]   ASSOCF_ flags from "shlwapi.h"
 *  str      [I]   Type of string to get (ASSOCSTR enum from "shlwapi.h")
 *  pszExtra [I]   Extra information about the string location
 *  pszOut   [O]   Destination for the association string
 *  pcchOut  [I/O] Length of pszOut
 *
 * RETURNS
 *  Success: S_OK. pszOut contains the string, pcchOut contains its length.
 *  Failure: An HRESULT error code indicating the error.
 */
HRESULT STDMETHODCALLTYPE CQueryAssociations::GetString(
    ASSOCF flags,
    ASSOCSTR str,
    LPCWSTR pszExtra,
    LPWSTR pszOut,
    DWORD *pcchOut)
{
    const ASSOCF unimplemented_flags = ~ASSOCF_NOTRUNCATE;
    DWORD len = 0;
    HRESULT hr;
    WCHAR path[MAX_PATH];

    TRACE("(%p)->(0x%08x, %u, %s, %p, %p)\n", this, flags, str, debugstr_w(pszExtra), pszOut, pcchOut);
    if (flags & unimplemented_flags)
    {
        FIXME("%08x: unimplemented flags\n", flags & unimplemented_flags);
    }
    
    if (!pcchOut)
    {
        return E_UNEXPECTED;
    }
    
    if (!this->hkeySource && !this->hkeyProgID)
    {
        return HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION);
    }

    switch (str)
    {
        case ASSOCSTR_COMMAND:
        {
            WCHAR *command;
            hr = this->GetCommand(pszExtra, &command);
            if (SUCCEEDED(hr))
            {
                hr = this->ReturnString(flags, pszOut, pcchOut, command, strlenW(command) + 1);
                HeapFree(GetProcessHeap(), 0, command);
            }
            return hr;
        }
        case ASSOCSTR_EXECUTABLE:
        {
            hr = this->GetExecutable(pszExtra, path, MAX_PATH, &len);
            if (FAILED(hr))
            {
                return hr;
            }
            len++;
            return this->ReturnString(flags, pszOut, pcchOut, path, len);
        }
        case ASSOCSTR_FRIENDLYDOCNAME:
        {
            WCHAR *pszFileType;

            hr = this->GetValue(this->hkeySource, NULL, (void**)&pszFileType, NULL);
            if (FAILED(hr))
            {
                return hr;
            }
            DWORD size = 0;
            DWORD ret = RegGetValueW(HKEY_CLASSES_ROOT, pszFileType, NULL, RRF_RT_REG_SZ, NULL, NULL, &size);
            if (ret == ERROR_SUCCESS)
            {
                WCHAR *docName = static_cast<WCHAR *>(HeapAlloc(GetProcessHeap(), 0, size));
                if (docName)
                {
                    ret = RegGetValueW(HKEY_CLASSES_ROOT, pszFileType, NULL, RRF_RT_REG_SZ, NULL, docName, &size);
                    if (ret == ERROR_SUCCESS)
                    {
                        hr = this->ReturnString(flags, pszOut, pcchOut, docName, strlenW(docName) + 1);
                    }
                    else
                    {
                        hr = HRESULT_FROM_WIN32(ret);
                    }
                    HeapFree(GetProcessHeap(), 0, docName);
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                }
            }
            else
            {
                hr = HRESULT_FROM_WIN32(ret);
            }
            HeapFree(GetProcessHeap(), 0, pszFileType);
            return hr;
        }
        case ASSOCSTR_FRIENDLYAPPNAME:
        {
            PVOID verinfoW = NULL;
            DWORD size, retval = 0;
            UINT flen;
            WCHAR *bufW;
            static const WCHAR translationW[] = L"\\VarFileInfo\\Translation";
            static const WCHAR fileDescFmtW[] = L"\\StringFileInfo\\%04x%04x\\FileDescription";
            WCHAR fileDescW[41];

            hr = this->GetExecutable(pszExtra, path, MAX_PATH, &len);
            if (FAILED(hr))
            {
                return hr;
            }
            retval = GetFileVersionInfoSizeW(path, &size);
            if (!retval)
            {
                goto get_friendly_name_fail;
            }
            verinfoW = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, retval);
            if (!verinfoW)
            {
                return E_OUTOFMEMORY;
            }
            if (!GetFileVersionInfoW(path, 0, retval, verinfoW))
            {
                goto get_friendly_name_fail;
            }
            if (VerQueryValueW(verinfoW, translationW, (LPVOID *)&bufW, &flen))
            {
                UINT i;
                DWORD *langCodeDesc = (DWORD *)bufW;
                for (i = 0; i < flen / sizeof(DWORD); i++)
                {
                    sprintfW(fileDescW, fileDescFmtW, LOWORD(langCodeDesc[i]), HIWORD(langCodeDesc[i]));
                    if (VerQueryValueW(verinfoW, fileDescW, (LPVOID *)&bufW, &flen))
                    {
                        /* Does strlenW(bufW) == 0 mean we use the filename? */
                        len = strlenW(bufW) + 1;
                        TRACE("found FileDescription: %s\n", debugstr_w(bufW));
                        hr = this->ReturnString(flags, pszOut, pcchOut, bufW, len);
                        HeapFree(GetProcessHeap(), 0, verinfoW);
                        return hr;
                    }
                }
            }
        get_friendly_name_fail:
            PathRemoveExtensionW(path);
            PathStripPathW(path);
            TRACE("using filename: %s\n", debugstr_w(path));
            hr = this->ReturnString(flags, pszOut, pcchOut, path, strlenW(path) + 1);
            HeapFree(GetProcessHeap(), 0, verinfoW);
            return hr;
        }
        case ASSOCSTR_CONTENTTYPE:
        {
            static const WCHAR Content_TypeW[] = L"Content Type";

            DWORD size = 0;
            DWORD ret = RegGetValueW(this->hkeySource, NULL, Content_TypeW, RRF_RT_REG_SZ, NULL, NULL, &size);
            if (ret != ERROR_SUCCESS)
            {
                return HRESULT_FROM_WIN32(ret);
            }
            WCHAR *contentType = static_cast<WCHAR *>(HeapAlloc(GetProcessHeap(), 0, size));
            if (contentType != NULL)
            {
                ret = RegGetValueW(this->hkeySource, NULL, Content_TypeW, RRF_RT_REG_SZ, NULL, contentType, &size);
                if (ret == ERROR_SUCCESS)
                {
                    hr = this->ReturnString(flags, pszOut, pcchOut, contentType, strlenW(contentType) + 1);
                }
                else
                {
                    hr = HRESULT_FROM_WIN32(ret);
                }
                HeapFree(GetProcessHeap(), 0, contentType);
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }
            return hr;
        }
        case ASSOCSTR_DEFAULTICON:
        {
            static const WCHAR DefaultIconW[] = L"DefaultIcon";
            DWORD ret;
            DWORD size = 0;
            ret = RegGetValueW(this->hkeyProgID, DefaultIconW, NULL, RRF_RT_REG_SZ, NULL, NULL, &size);
            if (ret == ERROR_SUCCESS)
            {
                WCHAR *icon = static_cast<WCHAR *>(HeapAlloc(GetProcessHeap(), 0, size));
                if (icon)
                {
                    ret = RegGetValueW(this->hkeyProgID, DefaultIconW, NULL, RRF_RT_REG_SZ, NULL, icon, &size);
                    if (ret == ERROR_SUCCESS)
                    {
                        hr = this->ReturnString(flags, pszOut, pcchOut, icon, strlenW(icon) + 1);
                    }
                    else
                    {
                        hr = HRESULT_FROM_WIN32(ret);
                    }
                    HeapFree(GetProcessHeap(), 0, icon);
                }
                else
                {
                    hr = HRESULT_FROM_WIN32(ret);
                }
            }
            else
            {
                hr = HRESULT_FROM_WIN32(ret);
            }
            return hr;
        }
        case ASSOCSTR_SHELLEXTENSION:
        {
            static const WCHAR shellexW[] = L"ShellEx\\";
            WCHAR keypath[sizeof(shellexW) / sizeof(shellexW[0]) + 39], guid[39];
            CLSID clsid;
            HKEY hkey;

            hr = CLSIDFromString(pszExtra, &clsid);
            if (FAILED(hr))
            {            
                return hr;
            }
            strcpyW(keypath, shellexW);
            strcatW(keypath, pszExtra);
            LONG ret = RegOpenKeyExW(this->hkeySource, keypath, 0, KEY_READ, &hkey);
            if (ret)
            {
                return HRESULT_FROM_WIN32(ret);
            }
            DWORD size = sizeof(guid);
            ret = RegGetValueW(hkey, NULL, NULL, RRF_RT_REG_SZ, NULL, guid, &size);
            RegCloseKey(hkey);
            if (ret)
            {
                return HRESULT_FROM_WIN32(ret);
            }
            return this->ReturnString(flags, pszOut, pcchOut, guid, size / sizeof(WCHAR));
        }
        
        default:
        {
            FIXME("assocstr %d unimplemented!\n", str);
            return E_NOTIMPL;
        }
    }
}