/**********************************************************************
 * SmCreateUserProcess/5
 *
 * DESCRIPTION
 *
 * ARGUMENTS
 *	ImagePath: absolute path of the image to run;
 *	CommandLine: arguments and options for ImagePath;
 *	Flags: Wait flag: Set for boot time processes and unset for
 *			subsystems bootstrapping;
 *		1Mb reserve flag: Set for subsystems, unset for everything
*			else
 *	Timeout: optional: used if WaitForIt==TRUE;
 *	ProcessHandle: optional: a duplicated handle for
 		the child process (storage provided by the caller).
 *
 * RETURN VALUE
 * 	NTSTATUS:
 *
 */
NTSTATUS NTAPI
SmCreateUserProcess (LPWSTR ImagePath,
		     LPWSTR CommandLine,
		     ULONG Flags,
		     PLARGE_INTEGER Timeout OPTIONAL,
		     PRTL_USER_PROCESS_INFORMATION UserProcessInfo OPTIONAL)
{
	UNICODE_STRING			ImagePathString   = { 0, 0, NULL };
	UNICODE_STRING			CommandLineString = { 0, 0, NULL };
	UNICODE_STRING			SystemDirectory   = { 0, 0, NULL };
	PRTL_USER_PROCESS_PARAMETERS	ProcessParameters = NULL;
	RTL_USER_PROCESS_INFORMATION	ProcessInfo  = {0};
	PRTL_USER_PROCESS_INFORMATION	pProcessInfo = & ProcessInfo;
	NTSTATUS			Status = STATUS_SUCCESS;

	DPRINT("SM: %s called\n", __FUNCTION__);

	if (NULL != UserProcessInfo)
	{
		pProcessInfo = UserProcessInfo;
	}

	RtlInitUnicodeString (& ImagePathString, ImagePath);
	RtlInitUnicodeString (& CommandLineString, CommandLine);

	SystemDirectory.MaximumLength = (wcslen(SharedUserData->NtSystemRoot) * sizeof(WCHAR)) + sizeof(szSystemDirectory);
	SystemDirectory.Buffer = RtlAllocateHeap(RtlGetProcessHeap(),
						 0,
						 SystemDirectory.MaximumLength);
	if (SystemDirectory.Buffer == NULL)
	{
		Status = STATUS_NO_MEMORY;
		DPRINT1("SM: %s: Allocating system directory string failed (Status=0x%08lx)\n",
			__FUNCTION__, Status);
		return Status;
	}

	Status = RtlAppendUnicodeToString(& SystemDirectory,
					  SharedUserData->NtSystemRoot);
	if (!NT_SUCCESS(Status))
	{
		goto FailProcParams;
	}

	Status = RtlAppendUnicodeToString(& SystemDirectory,
					  szSystemDirectory);
	if (!NT_SUCCESS(Status))
	{
		goto FailProcParams;
	}


	Status = RtlCreateProcessParameters(& ProcessParameters,
					    & ImagePathString,
					    NULL,
					    & SystemDirectory,
					    & CommandLineString,
					    SmSystemEnvironment,
					    NULL,
					    NULL,
					    NULL,
					    NULL);

	RtlFreeHeap(RtlGetProcessHeap(),
		    0,
		    SystemDirectory.Buffer);

	if (!NT_SUCCESS(Status))
	{
FailProcParams:
		DPRINT1("SM: %s: Creating process parameters failed (Status=0x%08lx)\n",
			__FUNCTION__, Status);
		return Status;
	}

	/* Reserve lower 1Mb, if requested */
	if (Flags & SM_CREATE_FLAG_RESERVE_1MB)
		ProcessParameters->Flags |= RTL_USER_PROCESS_PARAMETERS_RESERVE_1MB;

	/* Create the user process */
	Status = RtlCreateUserProcess (& ImagePathString,
				       OBJ_CASE_INSENSITIVE,
				       ProcessParameters,
				       NULL,
				       NULL,
				       NULL,
				       FALSE,
				       NULL,
				       NULL,
				       pProcessInfo);

	RtlDestroyProcessParameters (ProcessParameters);

	if (!NT_SUCCESS(Status))
	{
		DPRINT1("SM: %s: Running \"%S\" failed (Status=0x%08lx)\n",
			__FUNCTION__, ImagePathString.Buffer, Status);
		return Status;
	}
	/*
	 * It the caller is *not* interested in the child info,
	 * resume it immediately.
	 */
	if (NULL == UserProcessInfo)
	{
		Status = NtResumeThread (ProcessInfo.ThreadHandle, NULL);
		if(!NT_SUCCESS(Status))
		{
			DPRINT1("SM: %s: NtResumeThread failed (Status=0x%08lx)\n",
				__FUNCTION__, Status);
		}
	}

	/* Wait for process termination */
	if (Flags & SM_CREATE_FLAG_WAIT)
	{
		Status = NtWaitForSingleObject (pProcessInfo->ProcessHandle,
						FALSE,
						Timeout);
		if (!NT_SUCCESS(Status))
		{
			DPRINT1("SM: %s: NtWaitForSingleObject failed with Status=0x%08lx\n",
				__FUNCTION__, Status);
		}
	}

    if (NULL == UserProcessInfo)
    {
        NtClose(pProcessInfo->ProcessHandle);
        NtClose(pProcessInfo->ThreadHandle);
    }
	return Status;
}