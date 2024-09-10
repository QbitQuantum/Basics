// This routine will pass the string pipe name and fetch the pipe handle.
PPIPE_CONTEXT Pipe_GetContextFromName(
    __in PDEVICE_CONTEXT DeviceContext,
    __in PUNICODE_STRING FileName)
{
	INT					nameLength, index;
	PPIPE_CONTEXT		pipeContext = NULL;
	PAGED_CODE();

	nameLength = (INT)(FileName->Length / sizeof(WCHAR));
	for (index = 0; index < sizeof(PipeNameToPipeID) / sizeof(PipeNameToPipeID[0]); index++)
	{
		INT checkLength = (INT)wcslen(PipeNameToPipeID[index].NameW);
		if (checkLength == nameLength &&
		        wmemcmp(FileName->Buffer, PipeNameToPipeID[index].NameW, nameLength) == 0)
		{
			pipeContext = GetPipeContextByID(DeviceContext, PipeNameToPipeID[index].PipeID);

			if (pipeContext == NULL || !pipeContext->IsValid || !pipeContext->Pipe || !pipeContext->Queue)
			{
				USBERR("pipe filename %s is valid but the pipe does not exist\n", PipeNameToPipeID[index].Name);
				return NULL;
			}

			return pipeContext; // a valid pipe was found.
		}
	}

	// The pipe name was not recognized.  Pipe names are case-sensitive and in the format:
	// 'PIPE_xx' where xx is the two digit hex endpoint address. i.e. PIPE_0A, PIPE_8A.
	USBERR("invalid pipe filename=%wZ\n", FileName->Buffer);
	return NULL;
}