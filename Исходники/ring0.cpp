static bool OpenPhysicalMemory(void)
{
  // Grant me to access to physical memory
  EXPLICIT_ACCESS Access;
  PACL OldDacl = NULL, NewDacl = NULL;
  PVOID security;
  INIT_UNICODE_STRING(name, L"\\Device\\PhysicalMemory");
  OBJECT_ATTRIBUTES oa = {sizeof(oa), 0, &name, 0, 0, 0};  
  memset(&Access, 0, sizeof(EXPLICIT_ACCESS));
  NtOpenSection(&phyMemoryHandle, WRITE_DAC | READ_CONTROL, &oa);
  GetSecurityInfo(phyMemoryHandle, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, &OldDacl, NULL, &security);
  Access.grfAccessPermissions = SECTION_ALL_ACCESS; 
  Access.grfAccessMode = GRANT_ACCESS;
  Access.grfInheritance = NO_INHERITANCE;
  Access.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
  Access.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
  Access.Trustee.TrusteeType = TRUSTEE_IS_USER;
  Access.Trustee.ptstrName = "CURRENT_USER";
  // update ACL
  SetEntriesInAcl(1, &Access, OldDacl, &NewDacl);
  SetSecurityInfo(phyMemoryHandle, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, NewDacl, NULL);
  CloseHandle(phyMemoryHandle);
  // get handle to RAM
  if (NtOpenSection(&phyMemoryHandle,SECTION_MAP_READ|SECTION_MAP_WRITE,&oa)) die("NtOpenphyMemoryHandle failed");

  return true;
}