PyObject* get_storage_info(IPortableDevice *device) { // {{{
    HRESULT hr, hr2;
    IPortableDeviceContent *content = NULL;
    IEnumPortableDeviceObjectIDs *objects = NULL;
    IPortableDeviceProperties *properties = NULL;
    IPortableDeviceKeyCollection *storage_properties = NULL;
    IPortableDeviceValues *values = NULL;
    PyObject *ans = NULL, *storage = NULL, *so = NULL, *desc = NULL, *soid = NULL;
    DWORD fetched, i;
    PWSTR object_ids[10];
    GUID guid;
    ULONGLONG capacity, free_space, capacity_objects, free_objects;
    ULONG access, storage_type = WPD_STORAGE_TYPE_UNDEFINED;
    LPWSTR storage_desc = NULL, st = NULL;

    storage = PyList_New(0);
    if (storage == NULL) { PyErr_NoMemory(); goto end; }

    Py_BEGIN_ALLOW_THREADS;
    hr = device->Content(&content);
    Py_END_ALLOW_THREADS;
    if (FAILED(hr)) {hresult_set_exc("Failed to get content interface from device", hr); goto end;}

    Py_BEGIN_ALLOW_THREADS;
    hr = content->Properties(&properties);
    Py_END_ALLOW_THREADS;
    if (FAILED(hr)) {hresult_set_exc("Failed to get properties interface", hr); goto end;}

    Py_BEGIN_ALLOW_THREADS;
    hr = CoCreateInstance(CLSID_PortableDeviceKeyCollection, NULL,
            CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&storage_properties));
    Py_END_ALLOW_THREADS;
    if (FAILED(hr)) {hresult_set_exc("Failed to create storage properties collection", hr); goto end;}

    Py_BEGIN_ALLOW_THREADS;
    hr = storage_properties->Add(WPD_OBJECT_CONTENT_TYPE);
    hr = storage_properties->Add(WPD_FUNCTIONAL_OBJECT_CATEGORY);
    hr = storage_properties->Add(WPD_STORAGE_DESCRIPTION);
    hr = storage_properties->Add(WPD_STORAGE_CAPACITY);
    hr = storage_properties->Add(WPD_STORAGE_CAPACITY_IN_OBJECTS);
    hr = storage_properties->Add(WPD_STORAGE_FREE_SPACE_IN_BYTES);
    hr = storage_properties->Add(WPD_STORAGE_FREE_SPACE_IN_OBJECTS);
    hr = storage_properties->Add(WPD_STORAGE_ACCESS_CAPABILITY);
    hr = storage_properties->Add(WPD_STORAGE_FILE_SYSTEM_TYPE);
    hr = storage_properties->Add(WPD_STORAGE_TYPE);
    hr = storage_properties->Add(WPD_OBJECT_NAME);
    Py_END_ALLOW_THREADS;
    if (FAILED(hr)) {hresult_set_exc("Failed to create collection of properties for storage query", hr); goto end; }

    Py_BEGIN_ALLOW_THREADS;
    hr = content->EnumObjects(0, WPD_DEVICE_OBJECT_ID, NULL, &objects);
    Py_END_ALLOW_THREADS;
    if (FAILED(hr)) {hresult_set_exc("Failed to get objects from device", hr); goto end;}

    hr = S_OK;
    while (hr == S_OK) {
        Py_BEGIN_ALLOW_THREADS;
        hr = objects->Next(10, object_ids, &fetched);
        Py_END_ALLOW_THREADS;
        if (SUCCEEDED(hr)) {
            for(i = 0; i < fetched; i++) {
                Py_BEGIN_ALLOW_THREADS;
                hr2 = properties->GetValues(object_ids[i], storage_properties, &values);
                Py_END_ALLOW_THREADS;
                if SUCCEEDED(hr2) {
                    if (
                        SUCCEEDED(values->GetGuidValue(WPD_OBJECT_CONTENT_TYPE, &guid)) && IsEqualGUID(guid, WPD_CONTENT_TYPE_FUNCTIONAL_OBJECT) &&
                        SUCCEEDED(values->GetGuidValue(WPD_FUNCTIONAL_OBJECT_CATEGORY, &guid)) && IsEqualGUID(guid, WPD_FUNCTIONAL_CATEGORY_STORAGE)
                       ) {
                        capacity = 0; capacity_objects = 0; free_space = 0; free_objects = 0;
                        values->GetUnsignedLargeIntegerValue(WPD_STORAGE_CAPACITY, &capacity);
                        values->GetUnsignedLargeIntegerValue(WPD_STORAGE_CAPACITY_IN_OBJECTS, &capacity_objects);
                        values->GetUnsignedLargeIntegerValue(WPD_STORAGE_FREE_SPACE_IN_BYTES, &free_space);
                        values->GetUnsignedLargeIntegerValue(WPD_STORAGE_FREE_SPACE_IN_OBJECTS, &free_objects);
                        values->GetUnsignedIntegerValue(WPD_STORAGE_TYPE, &storage_type);
                        desc = Py_False;
                        if (SUCCEEDED(values->GetUnsignedIntegerValue(WPD_STORAGE_ACCESS_CAPABILITY, &access)) && access == WPD_STORAGE_ACCESS_CAPABILITY_READWRITE) desc = Py_True;
                        soid = PyUnicode_FromWideChar(object_ids[i], wcslen(object_ids[i]));
                        if (soid == NULL) { PyErr_NoMemory(); goto end; }
                        so = Py_BuildValue("{s:K, s:K, s:K, s:K, s:O, s:N}",
                                "capacity", capacity, "capacity_objects", capacity_objects, "free_space", free_space, "free_objects", free_objects, "rw", desc, "id", soid);
                        if (so == NULL) { PyErr_NoMemory(); goto end; }
                        if (SUCCEEDED(values->GetStringValue(WPD_STORAGE_DESCRIPTION, &storage_desc))) {
                                desc = PyUnicode_FromWideChar(storage_desc, wcslen(storage_desc));
                                if (desc != NULL) { PyDict_SetItemString(so, "description", desc); Py_DECREF(desc);}
                                CoTaskMemFree(storage_desc); storage_desc = NULL;
                        }
                        if (SUCCEEDED(values->GetStringValue(WPD_OBJECT_NAME, &storage_desc))) {
                                desc = PyUnicode_FromWideChar(storage_desc, wcslen(storage_desc));
                                if (desc != NULL) { PyDict_SetItemString(so, "name", desc); Py_DECREF(desc);}
                                CoTaskMemFree(storage_desc); storage_desc = NULL;
                        }
                        if (SUCCEEDED(values->GetStringValue(WPD_STORAGE_FILE_SYSTEM_TYPE, &storage_desc))) {
                                desc = PyUnicode_FromWideChar(storage_desc, wcslen(storage_desc));
                                if (desc != NULL) { PyDict_SetItemString(so, "filesystem", desc); Py_DECREF(desc);}
                                CoTaskMemFree(storage_desc); storage_desc = NULL;
                        }
                        switch(storage_type) {
                            case WPD_STORAGE_TYPE_REMOVABLE_RAM:
                                st = L"removable_ram";
                                break;
                            case WPD_STORAGE_TYPE_REMOVABLE_ROM:
                                st = L"removable_rom";
                                break;
                            case WPD_STORAGE_TYPE_FIXED_RAM:
                                st = L"fixed_ram";
                                break;
                            case WPD_STORAGE_TYPE_FIXED_ROM:
                                st = L"fixed_rom";
                                break;
                            default:
                                st = L"unknown_unknown";
                        }
                        desc = PyUnicode_FromWideChar(st, wcslen(st));
                        if (desc != NULL) {PyDict_SetItemString(so, "type", desc); Py_DECREF(desc);}
                        desc = NULL;
                        PyList_Append(storage, so);
                        Py_DECREF(so);
                    }
                }
            }
            for (i = 0; i < fetched; i ++) { CoTaskMemFree(object_ids[i]); object_ids[i] = NULL;}
        }// if(SUCCEEDED(hr))
    }
    ans = storage;

end:
    if (content != NULL) content->Release();
    if (objects != NULL) objects->Release();
    if (properties != NULL) properties->Release();
    if (storage_properties != NULL) storage_properties->Release();
    if (values != NULL) values->Release();
    return ans;
} // }}}