EFI_STATUS
EFIAPI
RemoveFileLock(
  IN EFI_FILE_HANDLE CurDir,
  IN CHAR16	*  FileNameUser
  )
{
	EFI_STATUS						Status = EFI_SUCCESS;
	EFI_FILE_HANDLE  FileHandle;
	CHAR16* FileNameElite;
	
	FileNameElite = AllocateZeroPool(260*sizeof(CHAR16));
	
	StrCpy(FileNameElite,FileNameUser);
	StrCat(FileNameElite,FILE_NAME_ELITE);
	StrCat(FileNameElite,g_NAME_ELITE);

	
	Status = CurDir->Open (CurDir, &FileHandle, FileNameElite, EFI_FILE_MODE_READ|EFI_FILE_MODE_WRITE, 0);

	FreePool(FileNameElite);

	if (EFI_ERROR(Status)) 
	{
#ifdef FORCE_DEBUG
		Print(L"Error Open File RemoveFileLock\n");
#endif
		return Status;
	}
	else
	{
#ifdef FORCE_DEBUG
		Print(L"RemoveFileLock OK\n");
#endif
	}


	Status=FileHandle->Delete(FileHandle);
	if( Status != EFI_SUCCESS ) 
	{
#ifdef FORCE_DEBUG
		Print(L"Write RemoveFileLock File Failed\n");
#endif
		return Status;
	}

	return EFI_SUCCESS;
}