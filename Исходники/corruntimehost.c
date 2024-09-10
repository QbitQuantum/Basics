HRESULT create_monodata(REFIID riid, LPVOID *ppObj )
{
    static const WCHAR wszAssembly[] = {'A','s','s','e','m','b','l','y',0};
    static const WCHAR wszCodebase[] = {'C','o','d','e','B','a','s','e',0};
    static const WCHAR wszClass[] = {'C','l','a','s','s',0};
    static const WCHAR wszFileSlash[] = {'f','i','l','e',':','/','/','/',0};
    static const WCHAR wszCLSIDSlash[] = {'C','L','S','I','D','\\',0};
    static const WCHAR wszInprocServer32[] = {'\\','I','n','p','r','o','c','S','e','r','v','e','r','3','2',0};
    static const WCHAR wszDLL[] = {'.','d','l','l',0};
    WCHAR path[CHARS_IN_GUID + ARRAYSIZE(wszCLSIDSlash) + ARRAYSIZE(wszInprocServer32) - 1];
    MonoDomain *domain;
    MonoAssembly *assembly;
    ICLRRuntimeInfo *info = NULL;
    RuntimeHost *host;
    HRESULT hr;
    HKEY key, subkey;
    LONG res;
    int offset = 0;
    DWORD numKeys, keyLength;
    WCHAR codebase[MAX_PATH + 8];
    WCHAR classname[350], subkeyName[256];
    WCHAR filename[MAX_PATH];

    DWORD dwBufLen = 350;

    lstrcpyW(path, wszCLSIDSlash);
    StringFromGUID2(riid, path + lstrlenW(wszCLSIDSlash), CHARS_IN_GUID);
    lstrcatW(path, wszInprocServer32);

    TRACE("Registry key: %s\n", debugstr_w(path));

    res = RegOpenKeyExW(HKEY_CLASSES_ROOT, path, 0, KEY_READ, &key);
    if (res == ERROR_FILE_NOT_FOUND)
        return CLASS_E_CLASSNOTAVAILABLE;

    res = RegGetValueW( key, NULL, wszClass, RRF_RT_REG_SZ, NULL, classname, &dwBufLen);
    if(res != ERROR_SUCCESS)
    {
        WARN("Class value cannot be found.\n");
        hr = CLASS_E_CLASSNOTAVAILABLE;
        goto cleanup;
    }

    TRACE("classname (%s)\n", debugstr_w(classname));

    dwBufLen = MAX_PATH + 8;
    res = RegGetValueW( key, NULL, wszCodebase, RRF_RT_REG_SZ, NULL, codebase, &dwBufLen);
    if(res == ERROR_SUCCESS)
    {
        /* Strip file:/// */
        if(strncmpW(codebase, wszFileSlash, strlenW(wszFileSlash)) == 0)
            offset = strlenW(wszFileSlash);

        strcpyW(filename, codebase + offset);
    }
    else
    {
        WCHAR assemblyname[MAX_PATH + 8];

        hr = CLASS_E_CLASSNOTAVAILABLE;
        WARN("CodeBase value cannot be found, trying Assembly.\n");
        /* get the last subkey of InprocServer32 */
        res = RegQueryInfoKeyW(key, 0, 0, 0, &numKeys, 0, 0, 0, 0, 0, 0, 0);
        if (res != ERROR_SUCCESS || numKeys == 0)
            goto cleanup;
        numKeys--;
        keyLength = sizeof(subkeyName) / sizeof(WCHAR);
        res = RegEnumKeyExW(key, numKeys, subkeyName, &keyLength, 0, 0, 0, 0);
        if (res != ERROR_SUCCESS)
            goto cleanup;
        res = RegOpenKeyExW(key, subkeyName, 0, KEY_READ, &subkey);
        if (res != ERROR_SUCCESS)
            goto cleanup;
        dwBufLen = MAX_PATH + 8;
        res = RegGetValueW(subkey, NULL, wszAssembly, RRF_RT_REG_SZ, NULL, assemblyname, &dwBufLen);
        RegCloseKey(subkey);
        if (res != ERROR_SUCCESS)
            goto cleanup;

        hr = get_file_from_strongname(assemblyname, filename, MAX_PATH);
        if (!SUCCEEDED(hr))
        {
            /*
             * The registry doesn't have a CodeBase entry and it's not in the GAC.
             *
             * Use the Assembly Key to retrieve the filename.
             *    Assembly : REG_SZ : AssemblyName, Version=X.X.X.X, Culture=neutral, PublicKeyToken=null
             */
            WCHAR *ns;

            WARN("Attempt to load from the application directory.\n");
            GetModuleFileNameW(NULL, filename, MAX_PATH);
            ns = strrchrW(filename, '\\');
            *(ns+1) = '\0';

            ns = strchrW(assemblyname, ',');
            *(ns) = '\0';
            strcatW(filename, assemblyname);
            *(ns) = '.';
            strcatW(filename, wszDLL);
        }
    }

    TRACE("filename (%s)\n", debugstr_w(filename));

    *ppObj = NULL;


    hr = get_runtime_info(filename, NULL, NULL, 0, 0, FALSE, &info);
    if (SUCCEEDED(hr))
    {
        hr = ICLRRuntimeInfo_GetRuntimeHost(info, &host);

        if (SUCCEEDED(hr))
            hr = RuntimeHost_GetDefaultDomain(host, &domain);

        if (SUCCEEDED(hr))
        {
            MonoImage *image;
            MonoClass *klass;
            MonoObject *result;
            IUnknown *unk = NULL;
            char *filenameA, *ns;
            char *classA;

            hr = CLASS_E_CLASSNOTAVAILABLE;

            mono_thread_attach(domain);

            filenameA = WtoA(filename);
            assembly = mono_domain_assembly_open(domain, filenameA);
            HeapFree(GetProcessHeap(), 0, filenameA);
            if (!assembly)
            {
                ERR("Cannot open assembly %s\n", filenameA);
                goto cleanup;
            }

            image = mono_assembly_get_image(assembly);
            if (!image)
            {
                ERR("Couldn't get assembly image\n");
                goto cleanup;
            }

            classA = WtoA(classname);
            ns = strrchr(classA, '.');
            *ns = '\0';

            klass = mono_class_from_name(image, classA, ns+1);
            HeapFree(GetProcessHeap(), 0, classA);
            if (!klass)
            {
                ERR("Couldn't get class from image\n");
                goto cleanup;
            }

            /*
             * Use the default constructor for the .NET class.
             */
            result = mono_object_new(domain, klass);
            mono_runtime_object_init(result);

            hr = RuntimeHost_GetIUnknownForObject(host, result, &unk);
            if (SUCCEEDED(hr))
            {
                hr = IUnknown_QueryInterface(unk, &IID_IUnknown, ppObj);

                IUnknown_Release(unk);
            }
            else
                hr = CLASS_E_CLASSNOTAVAILABLE;
        }
        else
            hr = CLASS_E_CLASSNOTAVAILABLE;
    }
    else
        hr = CLASS_E_CLASSNOTAVAILABLE;

cleanup:
    if(info)
        ICLRRuntimeInfo_Release(info);

    RegCloseKey(key);

    return hr;
}