NTSTATUS NTAPI NtCloseHook(IN HANDLE Handle)
{
	char info[16];

	if (NtQueryObject(Handle, (OBJECT_INFORMATION_CLASS)4, &info, sizeof(OBJECT_HANDLE_ATTRIBUTE_INFORMATION), nullptr) >= 0)
	{
		return origClose(Handle);
	}
	
	return STATUS_INVALID_HANDLE;
}