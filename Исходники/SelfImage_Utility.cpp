std::vector<wchar_t*> __fastcall GetNTDirectoryObjectContents(WideString Directory)
{
  std::vector<wchar_t*> Entries;
  std::string Entry;
  UNICODE_STRING usDir;
  OBJECT_ATTRIBUTES oa;
  HANDLE hDeviceDir;
  NTSTATUS nStatus;
  OBJDIR_INFORMATION *DirInfo;
  DWORD index;
  AnsiString Error;
  wchar_t *Temp;

  if (!HaveNTCalls)
    return Entries;

  RtlInitUnicodeString(&usDir, Directory);
  oa.Length = sizeof(OBJECT_ATTRIBUTES);
  oa.ObjectName = &usDir;
  oa.Attributes = OBJ_CASE_INSENSITIVE;
  oa.SecurityDescriptor = NULL;
  oa.SecurityQualityOfService = NULL;
  oa.RootDirectory = 0;

  // Fail when trying to open a floppy
  if (wmemcmp (L"\\Device\\Floppy", Directory, 14) == 0 ){
     return Entries;
  }

  nStatus = NtOpenDirectoryObject(&hDeviceDir, STANDARD_RIGHTS_READ | DIRECTORY_QUERY, &oa);
  if (!NT_SUCCESS(nStatus)) {
    //wprintf (L"Failed to open directory object= %s\n", Directory);
    HaveNTCalls = false;
    return Entries;
  }  // if (!NT_SUCCESS(nStatus))
  DirInfo = (OBJDIR_INFORMATION *)malloc(2048);
  index = 0;

  while (NT_SUCCESS(NtQueryDirectoryObject(hDeviceDir, DirInfo, 1024, true, false, &index, NULL))){
        Temp = new wchar_t[255];
        swprintf (Temp, L"%s\\%s", Directory, DirInfo->ObjectName.Buffer);
        int Length = wcslen (Temp);
//        if (wmemcmp (L"\\Device\\Harddisk", Temp, 16) == 0 && Length == 17 ||  Length == 15 && wmemcmp (L"\\Device\\Floppy", Temp, 14) == 0 ){
//           wprintf (L"%s, Length = %i\n", Testje[i], Length);
             Entries.push_back( Temp );
//        }


  }
  CloseHandle(hDeviceDir);
  free(DirInfo);
//  if (Entries.size())
    return Entries;
//  else {  // if (!Entries->Count)
//    delete Entries;
//    return NULL;
//  }  // if (!Entries->Count)
}   // TStringList * __fastcall GetNTDirectoryObjectContents(WideString Directory)