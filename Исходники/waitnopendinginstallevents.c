int __cdecl
main(ULONG argc, PCHAR argv[])
{
  DWORD ret;
  DWORD timeout = INFINITE;

  if (argc == 2)
  {
    timeout = atoi(argv[1]);
  }

  //printf("timeout = %d\n", timeout);

  ret = CMP_WaitNoPendingInstallEvents(timeout);

  //printf("ret = %d\n", ret);

  return ret;
}