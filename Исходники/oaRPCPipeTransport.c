static HANDLE PipeCreateServer(const char* pipename)
{
  BOOL                ret;
  const char*         sd            = "D:(A;OICI;GA;;;WD)";

  SECURITY_ATTRIBUTES sa;
  HANDLE              result        = INVALID_HANDLE_VALUE;

  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = FALSE;

  ret = ConvertStringSecurityDescriptorToSecurityDescriptorA(
    sd,
    SDDL_REVISION_1,
    &sa.lpSecurityDescriptor, 
    NULL);

  if(!ret)
    return INVALID_HANDLE_VALUE;

  result = CreateNamedPipeA(
    pipename,
    PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
    PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
    PIPE_UNLIMITED_INSTANCES,
    DEF_BUF_SIZE,
    DEF_BUF_SIZE,
    NMPWAIT_USE_DEFAULT_WAIT,
    &sa);

  if(sa.lpSecurityDescriptor)
    LocalFree(sa.lpSecurityDescriptor);

  return result;
}