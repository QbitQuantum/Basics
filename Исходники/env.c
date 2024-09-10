/*
 * @implemented
 */
DWORD
WINAPI
ExpandEnvironmentStringsA (
	LPCSTR	lpSrc,
	LPSTR	lpDst,
	DWORD	nSize
	)
{
	ANSI_STRING Source;
	ANSI_STRING Destination;
	UNICODE_STRING SourceU;
	UNICODE_STRING DestinationU;
	NTSTATUS Status;
	ULONG Length = 0;

	RtlInitAnsiString (&Source,
	                   (LPSTR)lpSrc);
	Status = RtlAnsiStringToUnicodeString (&SourceU,
	                                       &Source,
	                                       TRUE);
        if (!NT_SUCCESS(Status))
        {
            SetLastErrorByStatus (Status);
            return 0;
        }

    /* make sure we don't overflow the maximum ANSI_STRING size */
    if (nSize > 0x7fff)
        nSize = 0x7fff;

	Destination.Length = 0;
	Destination.MaximumLength = (USHORT)nSize;
	Destination.Buffer = lpDst;

	DestinationU.Length = 0;
	DestinationU.MaximumLength = (USHORT)nSize * sizeof(WCHAR);
	DestinationU.Buffer = RtlAllocateHeap (RtlGetProcessHeap (),
	                                       0,
	                                       DestinationU.MaximumLength);
        if (DestinationU.Buffer == NULL)
        {
            RtlFreeUnicodeString(&SourceU);
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return 0;
        }

	Status = RtlExpandEnvironmentStrings_U (NULL,
	                                        &SourceU,
	                                        &DestinationU,
	                                        &Length);

	RtlFreeUnicodeString (&SourceU);

	if (!NT_SUCCESS(Status))
	{
		SetLastErrorByStatus (Status);
		if (Status != STATUS_BUFFER_TOO_SMALL)
		{
			RtlFreeHeap (RtlGetProcessHeap (),
			             0,
			             DestinationU.Buffer);
			return 0;
		}
	}

	RtlUnicodeStringToAnsiString (&Destination,
	                              &DestinationU,
	                              FALSE);

	RtlFreeHeap (RtlGetProcessHeap (),
	             0,
	             DestinationU.Buffer);

	return (Length / sizeof(WCHAR));
}