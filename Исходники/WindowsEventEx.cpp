void WindowsEventEx::setAccessToAll(HANDLE objHandle)
{
  DWORD errorCode = SetSecurityInfo(objHandle, SE_KERNEL_OBJECT,
                                    DACL_SECURITY_INFORMATION, // Modify DACL
                                    0,
                                    0,
                                    0, // Pointer to DACL (0 = access to all)
                                    0);
  if (errorCode != ERROR_SUCCESS &&
      errorCode != ERROR_NO_SECURITY_ON_OBJECT) {
    StringStorage errMess;
    errMess.format(_T("Cannot SetSecurityInfo with error = %d"), (int)errorCode);
    throw Exception(errMess.getString());
  }
}