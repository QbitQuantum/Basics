void test3(void)
{
 HANDLE hKey;
 OBJECT_ATTRIBUTES ObjectAttributes;
 UNICODE_STRING KeyName;
 NTSTATUS Status;
 char Buffer[10];
 DWORD Result;
  dprintf("NtCreateKey non volatile: \n");
  dprintf("  \\Registry\\Machine\\Software\\test3reactos: ");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\Software\\test3reactos");
  InitializeObjectAttributes(&ObjectAttributes, &KeyName, OBJ_CASE_INSENSITIVE
				, NULL, NULL);
  Status = NtCreateKey ( &hKey, KEY_ALL_ACCESS , &ObjectAttributes
		,0,NULL,REG_OPTION_NON_VOLATILE,NULL);
  dprintf("\t\tStatus=%x\n",Status);
  NtClose(hKey);

  dprintf("delete \\Registry\\Machine\\software\\test3reactos ?");
  ReadConsoleA(InputHandle, Buffer, 3, &Result, NULL) ;
  if (Buffer[0] != 'y' && Buffer[0] != 'Y') return;

  dprintf("delete \\Registry\\Machine\\software\\test3reactos ?");
  RtlRosInitUnicodeStringFromLiteral(&KeyName, L"\\Registry\\Machine\\Software\\test3reactos");
  InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
  dprintf("NtOpenKey : ");
  Status=NtOpenKey( &hKey, KEY_ALL_ACCESS, &ObjectAttributes);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  dprintf("NtDeleteKey : ");
  Status=NtDeleteKey(hKey);
  dprintf("\t\t\t\tStatus =%x\n",Status);
  NtClose(hKey);
}