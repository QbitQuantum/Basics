/*
* supGetObjectTypesInfo
*
* Purpose:
*
* Returns buffer with system types information.
*
* Returned buffer must be freed with HeapFree after usage.
* Function will return error after 100 attempts.
*
*/
PVOID supGetObjectTypesInfo(
	VOID
	)
{
	INT			c = 0;
	PVOID		Buffer = NULL;
	ULONG		Size = 0x1000;
	NTSTATUS	status;
	ULONG       memIO;

	do {
		Buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (SIZE_T)Size);
		if (Buffer != NULL) {
			status = NtQueryObject(NULL, ObjectTypesInformation, Buffer, Size, &memIO);
		}
		else {
			return NULL;
		}
		if (NT_SUCCESS(status)) {
			break;
		}
		else {
			Size = memIO;
			HeapFree(GetProcessHeap(), 0, Buffer);
			Buffer = NULL;
		}
		c++;
		if (c > 100) {
			status = STATUS_SECRET_TOO_LONG;
			break;
		}
	} while (status != STATUS_SUCCESS);

	if (NT_SUCCESS(status)) {
		return Buffer;
	}

	if (Buffer) {
		HeapFree(GetProcessHeap(), 0, Buffer);
	}
	return NULL;
}