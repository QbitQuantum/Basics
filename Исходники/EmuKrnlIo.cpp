// ******************************************************************
// * 0x0045 - IoDeleteSymbolicLink()
// ******************************************************************
XBSYSAPI EXPORTNUM(69) xboxkrnl::NTSTATUS NTAPI xboxkrnl::IoDeleteSymbolicLink
(
	IN PSTRING SymbolicLinkName
)
{
	LOG_FUNC_ONE_ARG(SymbolicLinkName);

	EmuNtSymbolicLinkObject* symbolicLink = FindNtSymbolicLinkObjectByName(PSTRING_to_string(SymbolicLinkName));

	NTSTATUS ret = STATUS_OBJECT_NAME_NOT_FOUND;

	if (symbolicLink != NULL)
		// Destroy the object once all handles to it are closed too :
		ret = symbolicLink->NtClose();

	RETURN(ret);
}