/*
 * @implemented
 */
BOOL
WINAPI
GetVolumeInformationA(IN LPCSTR lpRootPathName,
                      IN LPSTR lpVolumeNameBuffer,
                      IN DWORD nVolumeNameSize,
                      OUT LPDWORD lpVolumeSerialNumber OPTIONAL,
                      OUT LPDWORD lpMaximumComponentLength OPTIONAL,
                      OUT LPDWORD lpFileSystemFlags OPTIONAL,
                      OUT LPSTR lpFileSystemNameBuffer OPTIONAL,
                      IN DWORD nFileSystemNameSize)
{
  UNICODE_STRING FileSystemNameU;
  UNICODE_STRING VolumeNameU = { 0, 0, NULL };
  ANSI_STRING VolumeName;
  ANSI_STRING FileSystemName;
  PWCHAR RootPathNameW;
  BOOL Result;

  if (!(RootPathNameW = FilenameA2W(lpRootPathName, FALSE)))
     return FALSE;

  if (lpVolumeNameBuffer)
    {
      VolumeNameU.MaximumLength = (USHORT)nVolumeNameSize * sizeof(WCHAR);
      VolumeNameU.Buffer = RtlAllocateHeap (RtlGetProcessHeap (),
	                                    0,
	                                    VolumeNameU.MaximumLength);
      if (VolumeNameU.Buffer == NULL)
      {
          goto FailNoMem;
      }
    }

  if (lpFileSystemNameBuffer)
    {
      FileSystemNameU.Length = 0;
      FileSystemNameU.MaximumLength = (USHORT)nFileSystemNameSize * sizeof(WCHAR);
      FileSystemNameU.Buffer = RtlAllocateHeap (RtlGetProcessHeap (),
	                                        0,
	                                        FileSystemNameU.MaximumLength);
      if (FileSystemNameU.Buffer == NULL)
      {
          if (VolumeNameU.Buffer != NULL)
          {
              RtlFreeHeap(RtlGetProcessHeap(),
                          0,
                          VolumeNameU.Buffer);
          }

FailNoMem:
          SetLastError(ERROR_NOT_ENOUGH_MEMORY);
          return FALSE;
      }
    }

  Result = GetVolumeInformationW (RootPathNameW,
	                          lpVolumeNameBuffer ? VolumeNameU.Buffer : NULL,
	                          nVolumeNameSize,
	                          lpVolumeSerialNumber,
	                          lpMaximumComponentLength,
	                          lpFileSystemFlags,
				  lpFileSystemNameBuffer ? FileSystemNameU.Buffer : NULL,
	                          nFileSystemNameSize);

  if (Result)
    {
      if (lpVolumeNameBuffer)
        {
          VolumeNameU.Length = wcslen(VolumeNameU.Buffer) * sizeof(WCHAR);
	  VolumeName.Length = 0;
	  VolumeName.MaximumLength = (USHORT)nVolumeNameSize;
	  VolumeName.Buffer = lpVolumeNameBuffer;
	}

      if (lpFileSystemNameBuffer)
	{
	  FileSystemNameU.Length = wcslen(FileSystemNameU.Buffer) * sizeof(WCHAR);
	  FileSystemName.Length = 0;
	  FileSystemName.MaximumLength = (USHORT)nFileSystemNameSize;
	  FileSystemName.Buffer = lpFileSystemNameBuffer;
	}

      /* convert unicode strings to ansi (or oem) */
      if (bIsFileApiAnsi)
        {
	  if (lpVolumeNameBuffer)
	    {
	      RtlUnicodeStringToAnsiString (&VolumeName,
			                    &VolumeNameU,
			                    FALSE);
	    }
	  if (lpFileSystemNameBuffer)
	    {
	      RtlUnicodeStringToAnsiString (&FileSystemName,
			                    &FileSystemNameU,
			                    FALSE);
	    }
	}
      else
        {
	  if (lpVolumeNameBuffer)
	    {
	      RtlUnicodeStringToOemString (&VolumeName,
			                   &VolumeNameU,
			                   FALSE);
	    }
          if (lpFileSystemNameBuffer)
	    {
	      RtlUnicodeStringToOemString (&FileSystemName,
			                   &FileSystemNameU,
			                   FALSE);
	    }
	}
    }

  if (lpVolumeNameBuffer)
    {
      RtlFreeHeap (RtlGetProcessHeap (),
	           0,
	           VolumeNameU.Buffer);
    }
  if (lpFileSystemNameBuffer)
    {
      RtlFreeHeap (RtlGetProcessHeap (),
	           0,
	           FileSystemNameU.Buffer);
    }

  return Result;
}