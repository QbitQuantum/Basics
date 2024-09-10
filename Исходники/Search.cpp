        bool search::generate_pbo_list() {
            NTSTATUS status;
            PSYSTEM_HANDLE_INFORMATION handleInfo;
            ULONG handleInfoSize = 0x10000;
            ULONG pid;
            HANDLE processHandle;
            ULONG i;

            _NtQuerySystemInformation NtQuerySystemInformation =
                (_NtQuerySystemInformation)GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
            _NtDuplicateObject NtDuplicateObject =
                (_NtDuplicateObject)GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject");
            _NtQueryObject NtQueryObject =
                (_NtQueryObject)GetLibraryProcAddress("ntdll.dll", "NtQueryObject");

            if (!NtQuerySystemInformation || !NtDuplicateObject || !NtQueryObject)
                return false;

            pid = GetCurrentProcessId();
            processHandle = GetCurrentProcess();

            handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);

            while ((status = NtQuerySystemInformation(
                SystemHandleInformation,
                handleInfo,
                handleInfoSize,
                NULL
                )) == STATUS_INFO_LENGTH_MISMATCH)
                handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);

            /* NtQuerySystemInformation stopped giving us STATUS_INFO_LENGTH_MISMATCH. */
            if (!NT_SUCCESS(status))
            {
                LOG(ERROR) << "Error opening object for pbo search";
                free(handleInfo);
                return false;
            }

            for (i = 0; i < handleInfo->HandleCount; i++)
            {
                SYSTEM_HANDLE handle = handleInfo->Handles[i];
                HANDLE dupHandle = NULL;
                POBJECT_TYPE_INFORMATION objectTypeInfo;
                PVOID objectNameInfo;
                UNICODE_STRING objectName;
                ULONG returnLength;

                /* Check if this handle belongs to the PID the user specified. */
                if (handle.ProcessId != pid)
                    continue;

                /* Duplicate the handle so we can query it. */
                if (!NT_SUCCESS(NtDuplicateObject(
                    processHandle,
                    (HANDLE)handle.Handle,
                    GetCurrentProcess(),
                    &dupHandle,
                    0,
                    0,
                    0
                    )))
                {
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
                    CloseHandle(dupHandle);
                    continue;
                }

                /* Query the object name (unless it has an access of
                0x0012019f, on which NtQueryObject could hang. */
                if (handle.GrantedAccess == 0x0012019f)
                {

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
                    std::wstring tmp_type(objectTypeInfo->Name.Buffer);
                    std::wstring tmp_name(objectName.Buffer);
                    
                    std::string object_type(tmp_type.begin(), tmp_type.end());
                    std::string object_name(tmp_name.begin(), tmp_name.end());
                    if (object_type == "File" && object_name.find(".pbo") != object_name.npos) {
                        char buffer[MAX_PATH];
                        GetFinalPathNameByHandle(dupHandle, buffer, sizeof(buffer), VOLUME_NAME_DOS);

                        LOG(DEBUG) << "Pbo: " << buffer;
                        _active_pbo_list.push_back(std::string(buffer));
                    }
                }              

                free(objectTypeInfo);
                free(objectNameInfo);
                CloseHandle(dupHandle);
            }

            free(handleInfo);

            return true;
        }