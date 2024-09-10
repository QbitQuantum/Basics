PVOID GetKernelModuleInfo(CHAR	* target_name, PVOID* base, LONG* size) {
	PVOID buffer = NULL;
	ULONG buf_size = 0x5000;
	NTSTATUS result;
	do {
		buffer = ExAllocatePool(PagedPool, buf_size);
		if (buffer == NULL) {
			return NULL;
		}
		ULONG need;
		result = NtQuerySystemInformation(SystemModuleInformation, buffer, buf_size, &need);
		if (result == STATUS_INFO_LENGTH_MISMATCH) {
			ExFreePool(buffer);
			buf_size *= 2;
		}
		else if (!NT_SUCCESS(result)) {
			ExFreePool(buffer);
			return NULL;
		}
	} while (result == STATUS_INFO_LENGTH_MISMATCH);

	PSYSTEM_MODULE_INFORMATION system_module_info = (PSYSTEM_MODULE_INFORMATION)buffer;
	int module_count = system_module_info->Count;
	for(int i=0; i<module_count; i++){
		CHAR* name = system_module_info->Module[i].ImageName + system_module_info->Module[i].PathLength;
		//DbgPrint("kernel module: %s,%p \n", name, system_module_info->Module[i].Base);
		if (_stricmp(name, target_name) == 0) {
			*base = system_module_info->Module[i].Base;
			*size = system_module_info->Module[i].Size;

		}
	}
	return NULL;

}