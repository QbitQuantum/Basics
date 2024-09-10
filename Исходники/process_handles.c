PyObject*
psutil_get_open_files(long pid, HANDLE processHandle)
{
    _NtQuerySystemInformation NtQuerySystemInformation =
        GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
    _NtDuplicateObject NtDuplicateObject =
        GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject");
    _NtQueryObject NtQueryObject =
        GetLibraryProcAddress("ntdll.dll", "NtQueryObject");

    NTSTATUS                    status;
    PSYSTEM_HANDLE_INFORMATION  handleInfo;
    ULONG                       handleInfoSize = 0x10000;

    ULONG                       i;
    ULONG                       fileNameLength;
    PyObject                    *filesList = Py_BuildValue("[]");
    PyObject                    *arg = NULL;
    PyObject                    *fileFromWchar = NULL;

    if (filesList == NULL)
        return NULL;

    handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);
    if (handleInfo == NULL) {
        Py_DECREF(filesList);
        PyErr_NoMemory();
        return NULL;
    }

    /* NtQuerySystemInformation won't give us the correct buffer size,
       so we guess by doubling the buffer size. */
    while ((status = NtQuerySystemInformation(
        SystemHandleInformation,
        handleInfo,
        handleInfoSize,
        NULL
        )) == STATUS_INFO_LENGTH_MISMATCH)
    {
        handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);
    }

    /* NtQuerySystemInformation stopped giving us STATUS_INFO_LENGTH_MISMATCH. */
    if (!NT_SUCCESS(status)) {
        //printf("NtQuerySystemInformation failed!\n");
        Py_DECREF(filesList);
        free(handleInfo);
        return NULL;
    }

    for (i = 0; i < handleInfo->HandleCount; i++)
    {
        SYSTEM_HANDLE            handle = handleInfo->Handles[i];
        HANDLE                   dupHandle = NULL;
        POBJECT_TYPE_INFORMATION objectTypeInfo = NULL;
        PVOID                    objectNameInfo;
        UNICODE_STRING           objectName;
        ULONG                    returnLength;
        fileFromWchar = NULL;
        arg = NULL;

        /* Check if this handle belongs to the PID the user specified. */
        if (handle.ProcessId != pid)
            continue;

        /* Skip handles with the following access codes as the next call
           to NtDuplicateObject() or NtQueryObject() might hang forever. */
        if((handle.GrantedAccess == 0x0012019f)
        || (handle.GrantedAccess == 0x001a019f)
        || (handle.GrantedAccess == 0x00120189)
        || (handle.GrantedAccess == 0x00100000)) {
            continue;
        }

        /* Duplicate the handle so we can query it. */
        if (!NT_SUCCESS(NtDuplicateObject(
            processHandle,
            handle.Handle,
            GetCurrentProcess(),
            &dupHandle,
            0,
            0,
            0
            )))
        {
            //printf("[%#x] Error!\n", handle.Handle);
            continue;
        }

        /* Query the object type. */
        objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x1000);
        if (!NT_SUCCESS(NtQueryObject(
            dupHandle,
            ObjectTypeInformation,
            objectTypeInfo,
            0x1000,
            NULL
            )))
        {
            //printf("[%#x] Error!\n", handle.Handle);
            free(objectTypeInfo);
            CloseHandle(dupHandle);
            continue;
        }

        objectNameInfo = malloc(0x1000);
        if (!NT_SUCCESS(NtQueryObject(
            dupHandle,
            ObjectNameInformation,
            objectNameInfo,
            0x1000,
            &returnLength
            )))
        {
            /* Reallocate the buffer and try again. */
            objectNameInfo = realloc(objectNameInfo, returnLength);
            if (!NT_SUCCESS(NtQueryObject(
                dupHandle,
                ObjectNameInformation,
                objectNameInfo,
                returnLength,
                NULL
                )))
            {
                /* We have the type name, so just display that.*/
                /*
                printf(
                    "[%#x] %.*S: (could not get name)\n",
                    handle.Handle,
                    objectTypeInfo->Name.Length / 2,
                    objectTypeInfo->Name.Buffer
                    );
                */
                free(objectTypeInfo);
                free(objectNameInfo);
                CloseHandle(dupHandle);
                continue;

            }
        }

        /* Cast our buffer into an UNICODE_STRING. */
        objectName = *(PUNICODE_STRING)objectNameInfo;

        /* Print the information! */
        if (objectName.Length)
        {
            /* The object has a name.  Make sure it is a file otherwise
               ignore it */
            fileNameLength = objectName.Length / 2;
            if (wcscmp(objectTypeInfo->Name.Buffer, L"File") == 0) {
                //printf("%.*S\n", objectName.Length / 2, objectName.Buffer);
                fileFromWchar = PyUnicode_FromWideChar(objectName.Buffer,
                                                       fileNameLength);
                if (fileFromWchar == NULL)
                    goto error_py_fun;
                #if PY_MAJOR_VERSION >= 3
                    arg = Py_BuildValue("N", PyUnicode_AsUTF8String(fileFromWchar));
                #else
                    arg = Py_BuildValue("N", PyUnicode_FromObject(fileFromWchar));
                #endif
                if (!arg)
                    goto error_py_fun;
                Py_XDECREF(fileFromWchar);
                fileFromWchar = NULL;
                if (PyList_Append(filesList, arg))
                    goto error_py_fun;
                Py_XDECREF(arg);
            }
            /*
            printf(
                "[%#x] %.*S: %.*S\n",
                handle.Handle,
                objectTypeInfo->Name.Length / 2,
                objectTypeInfo->Name.Buffer,
                objectName.Length / 2,
                objectName.Buffer
                );
            */
        }
        else
        {
            /* Print something else. */
            /*
            printf(
                "[%#x] %.*S: (unnamed)\n",
                handle.Handle,
                objectTypeInfo->Name.Length / 2,
                objectTypeInfo->Name.Buffer
                );
            */
            ;;
        }
        free(objectTypeInfo);
        free(objectNameInfo);
        CloseHandle(dupHandle);
    }
    free(handleInfo);
    CloseHandle(processHandle);
    return filesList;

error_py_fun:
    Py_XDECREF(arg);
    Py_XDECREF(fileFromWchar);
    Py_DECREF(filesList);
    return NULL;
}