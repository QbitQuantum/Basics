FLT_POSTOP_CALLBACK_STATUS
claimsmanPostOperation(
_Inout_ PFLT_CALLBACK_DATA Data,
_In_ PCFLT_RELATED_OBJECTS FltObjects,
_In_opt_ PVOID CompletionContext,
_In_ FLT_POST_OPERATION_FLAGS Flags
)
/*++

Routine Description:

This routine is the post-operation completion routine for this
miniFilter.

This is non-pageable because it may be called at DPC level.

Arguments:

Data - Pointer to the filter callbackData that is passed to us.

FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
opaque handles to this filter, instance, its associated volume and
file object.

CompletionContext - The completion context set in the pre-operation routine.

Flags - Denotes whether the completion is successful or is being drained.

Return Value:

The return value is the status of the operation.

--*/
{
	UNREFERENCED_PARAMETER(Data);
	UNREFERENCED_PARAMETER(CompletionContext);
	UNREFERENCED_PARAMETER(Flags);
	NTSTATUS status;
	PFLT_FILE_NAME_INFORMATION nameInfo = NULL;
	PUNICODE_STRING fileName = NULL;
	PTOKEN_USER pTokenUser = NULL;
	UNICODE_STRING sidString;
	
	LARGE_INTEGER Timeout;
	Timeout.QuadPart = (LONGLONG)1 * 10 * 1000 * 1000;
	
	// If there is no client registered, bail out immediately!
	// If the event is from kernel, bail out immediately!
	// If the event check for existence of file, bail out immediately!
	if (
		(ClaimsmanData.ClientPort == NULL) || 
		(Data->RequestorMode == KernelMode) ||
		(Data->IoStatus.Information == FILE_DOES_NOT_EXIST) ||
		(Data->IoStatus.Information == FILE_EXISTS)
		) {
		return FLT_POSTOP_FINISHED_PROCESSING;
	}

	//  We got a log record, if there is a file object, get its name.

	if (FltObjects->FileObject != NULL) {
		status = FltGetFileNameInformation(Data,
			FLT_FILE_NAME_NORMALIZED |
			FLT_FILE_NAME_QUERY_DEFAULT,
			&nameInfo);
	}
	else {
		//  Can't get a name when there's no file object
		status = STATUS_UNSUCCESSFUL;
	}

	if (NT_SUCCESS(status)) {
		FltParseFileNameInformation(nameInfo);
		fileName = &nameInfo->Name;
		// Produces way too much logging
		//PT_DBG_PRINT(PTDBG_TRACE_ROUTINES,
		//	("claimsman!claimsmanPostOperation: fileName=%wZ\n", fileName));
	}
	else
	{
		// No point continuing because we obviously did not get a filename anyways
		return FLT_POSTOP_FINISHED_PROCESSING;
	}

	//The only IRP you can trust for user information is IRP_MJ_CREATE. Things 
	//like write can be in arbitrary thread context, and even if the call works
	//you can get the wrong SID.

	status = SeQueryInformationToken(SeQuerySubjectContextToken(&(Data->Iopb->Parameters.Create.SecurityContext->AccessState->SubjectSecurityContext)), TokenUser, &pTokenUser);
	if (STATUS_SUCCESS == status && RtlValidSid(pTokenUser->User.Sid))
	{
		// Interesting extension?
		if (ClaimsmanCheckExtension(&nameInfo->Extension)) {
			CLAIMSMAN_MESSAGE msg;

			status = RtlConvertSidToUnicodeString(&sidString, pTokenUser->User.Sid, TRUE);

			if (NT_SUCCESS(status)) {
				PT_DBG_PRINT(PTDBG_TRACE_ROUTINES,
					("claimsman!claimsmanPostOperation: SID=%wZ\n", &sidString));
			}
			else {
				// No point continuing because we obviously did not get a valid SID
				FltReleaseFileNameInformation(nameInfo);
				ExFreePool(pTokenUser);
				return FLT_POSTOP_FINISHED_PROCESSING;
			}

			if (ClaimsmanCheckUserIgnore(&sidString)) {
				// Ignored user! Bail out!
				FltReleaseFileNameInformation(nameInfo);
				ExFreePool(pTokenUser);
				RtlFreeUnicodeString(&sidString);
				return FLT_POSTOP_FINISHED_PROCESSING;
			}

			LONGLONG size;
			LONGLONG modified;
			getSizeModified(FltObjects->Instance, fileName, &size, &modified);

			InitializeMessage(&msg, &sidString, fileName, FltObjects->FileObject->ReadAccess, FltObjects->FileObject->WriteAccess, FltObjects->FileObject->DeleteAccess, size, modified, Data->IoStatus.Status);

			// Ready, send the message!
			// But only if there's a client connected
			if (ClaimsmanData.ClientPort != NULL) {

				FltSendMessage(ClaimsmanData.Filter,
					&ClaimsmanData.ClientPort,
					&msg,
					sizeof(msg),
					NULL,
					0,
					&Timeout
					);
				PT_DBG_PRINT(PTDBG_TRACE_ROUTINES,
					("claimsman!claimsmanPostOperation: sent message=%d\n", status));
			}
			else {
				PT_DBG_PRINT(PTDBG_TRACE_ROUTINES,
					("claimsman!claimsmanPostOperation: no client connected!"));
			}
			RtlFreeUnicodeString(&sidString);
		}
	}

	FltReleaseFileNameInformation(nameInfo);
	if (pTokenUser != NULL) {
		ExFreePool(pTokenUser);
	}
	return FLT_POSTOP_FINISHED_PROCESSING;
}