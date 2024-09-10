EFI_STATUS EFIAPI
OvrExit(
	IN EFI_HANDLE				ImageHandle,
	IN EFI_STATUS				ExitStatus,
	IN UINTN					ExitDataSize,
	IN CHAR16					*ExitData
)
{
	EFI_STATUS					Status;
	
	Status = gOrgBS.Exit(ImageHandle, ExitStatus, ExitDataSize, ExitData);
	PRINT("->Exit(%p, %r, 0x%x, %s) = %r\n", ImageHandle, ExitStatus, ExitDataSize, ExitData, Status);
	return Status;
}