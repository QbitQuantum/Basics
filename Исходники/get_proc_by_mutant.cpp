BOOL GetProcessIdByMutantName(LPCWSTR mutant_name, std::vector<ULONG> &pids)
{
	_NtQuerySystemInformation NtQuerySystemInformation = 
		(_NtQuerySystemInformation)GetLibraryProcAddress(TEXT("ntdll.dll"), "NtQuerySystemInformation");
	_NtDuplicateObject NtDuplicateObject =
		(_NtDuplicateObject)GetLibraryProcAddress(TEXT("ntdll.dll"), "NtDuplicateObject");
	_NtQueryObject NtQueryObject =
		(_NtQueryObject)GetLibraryProcAddress(TEXT("ntdll.dll"), "NtQueryObject");


	if (NtQuerySystemInformation == NULL || NtDuplicateObject == NULL || NtQueryObject == NULL) {
		return FALSE;
	}

	PSYSTEM_HANDLE_INFORMATION handle_info;
	ULONG handle_info_size = 0x10000;

	CHeapPtr<UCHAR> handle_info_buffer;
	handle_info_buffer.Allocate(handle_info_size);

	NTSTATUS ns;
	while ((ns = NtQuerySystemInformation(
		SystemHandleInformation,
		handle_info_buffer.m_pData,
		handle_info_size,
		NULL
		)) == STATUS_INFO_LENGTH_MISMATCH) {

			handle_info_buffer.Reallocate(handle_info_size *= 2);
	}

	if (!NT_SUCCESS(ns)) {
		return FALSE;
	}

	handle_info = (PSYSTEM_HANDLE_INFORMATION)handle_info_buffer.m_pData;

	ULONG process_id = 0;
	HANDLE cur_handle = NULL;
	for (ULONG i = 0; i < handle_info->HandleCount; i++) {

		SYSTEM_HANDLE handle = handle_info->Handles[i];
		ULONG info_size = 0x1000;

		if (handle.GrantedAccess == 0x0012019f) {
			continue;
		}

		if (process_id != handle.ProcessId) {
			process_id = handle.ProcessId;

			if (cur_handle != NULL) {
				CloseHandle(cur_handle);
				cur_handle = NULL;
			}

			if (cur_handle == NULL) {
				cur_handle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, process_id);
			}

			if (cur_handle == NULL) {
				continue;
			}

		}

		HANDLE dup_handle = NULL;
		if (!NT_SUCCESS(NtDuplicateObject(
			cur_handle,
			(HANDLE)handle.Handle,
			GetCurrentProcess(),
			&dup_handle,
			0,
			0,
			0
			))) {

				continue;
		}

		CHandle auto_handle(dup_handle);
		CHeapPtr<UCHAR> obj_type_buffer;
		obj_type_buffer.Allocate(info_size);
		POBJECT_TYPE_INFORMATION obj_type_info = (POBJECT_TYPE_INFORMATION)obj_type_buffer.m_pData;
		if (!NT_SUCCESS(NtQueryObject(
			dup_handle,
			ObjectTypeInformation,
			obj_type_info,
			info_size,
			NULL
			))) {
				continue;
		}

		if (memcmp(obj_type_info->Name.Buffer, L"Mutant", 12) != 0) {
			continue;
		}

		CHeapPtr<UCHAR> obj_name_buffer;
		obj_name_buffer.Allocate(info_size);
		PVOID obj_name_info = obj_name_buffer.m_pData;
		ULONG return_length;
		if (!NT_SUCCESS(NtQueryObject(
			dup_handle,
			ObjectNameInformation,
			obj_name_info,
			info_size,
			&return_length
			))) {
				continue;
		}

		UNICODE_STRING object_name = *(PUNICODE_STRING)obj_name_info;
		if (object_name.Length) {
			CStringW object_name(object_name.Buffer, object_name.Length / 2); 
			if (object_name == mutant_name) {
				pids.push_back(process_id);
			}
			//wprintf(L"%u %s\n", process_id, object_name.GetString());
		}

	}

	if (cur_handle != NULL) {
		CloseHandle(cur_handle);
		cur_handle = NULL;
	}

	return TRUE;
}