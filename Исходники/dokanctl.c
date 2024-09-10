int __cdecl wmain(int argc, PWCHAR argv[]) {
  size_t i;
  WCHAR fileName[MAX_PATH];
  WCHAR driverFullPath[MAX_PATH] = {0};
  PVOID wow64OldValue;
  BOOL isAdmin;

  isAdmin = IsUserAnAdmin();

  DokanUseStdErr(TRUE); // Set dokan library debug output

  Wow64DisableWow64FsRedirection(&wow64OldValue); // Disable system32 direct
  // setlocale(LC_ALL, "");

  GetModuleFileName(NULL, fileName, MAX_PATH);

  // search the last "\"
  for (i = wcslen(fileName) - 1; i > 0 && fileName[i] != L'\\'; --i) {
    ;
  }
  fileName[i] = L'\0';

  ExpandEnvironmentStringsW(DOKAN_DRIVER_FULL_PATH, driverFullPath, MAX_PATH);

  fwprintf(stdout, L"Driver path: '%s'\n", driverFullPath);

  WCHAR option = GetOption(argc, argv, 1);
  if (option == L'\0' || option == L'?') {
    return ShowUsage();
  }

  if (!isAdmin &&
      (option == L'i' || option == L'r' || option == L'd' || option == L'u')) {
    fprintf(stderr, "Admin rights required to process this operation\n");
    return EXIT_FAILURE;
  }

  switch (option) {
  // Admin rights required
  case L'i': {
    WCHAR type = towlower(argv[2][0]);
    if (type == L'd') {
      return InstallDriver(driverFullPath);
    } else if (type == L'n') {
      if (DokanNetworkProviderInstall())
        fprintf(stdout, "network provider install ok\n");
      else
        fprintf(stderr, "network provider install failed\n");
    } else {
      goto DEFAULT;
    }
  } break;

  case L'r': {
    WCHAR type = towlower(argv[2][0]);
    if (type == L'd') {
      return DeleteDokanService(DOKAN_DRIVER_SERVICE);
    } else if (type == L'n') {
      if (DokanNetworkProviderUninstall())
        fprintf(stdout, "network provider remove ok\n");
      else
        fprintf(stderr, "network provider remove failed\n");
    } else {
      goto DEFAULT;
    }
  } break;

  case L'd': {
    WCHAR type = towlower(argv[2][0]);
    if (L'0' > type || type > L'9')
      goto DEFAULT;

    ULONG mode = type - L'0';
    if (DokanSetDebugMode(mode)) {
      fprintf(stdout, "set debug mode ok\n");
    } else {
      fprintf(stderr, "set debug mode failed\n");
    }
  } break;

  case L'u': {
    if (argc < 3) {
      goto DEFAULT;
    }
    return Unmount(argv[2]);
  } break;

  // No admin rights required
  case L'l': {
    ULONG nbRead = 0;
    PDOKAN_CONTROL dokanControl =
        malloc(DOKAN_MAX_INSTANCES * sizeof(*dokanControl));
    if (dokanControl == NULL) {
      fprintf(stderr, "Failed to allocate dokanControl\n");
      return EXIT_FAILURE;
    }

    ZeroMemory(dokanControl, DOKAN_MAX_INSTANCES * sizeof(*dokanControl));
    if (DokanGetMountPointList(dokanControl, DOKAN_MAX_INSTANCES, FALSE,
                               &nbRead)) {
      fwprintf(stdout, L"  Mount points: %d\n", nbRead);
      for (unsigned int p = 0; p < nbRead; ++p) {
        fwprintf(stdout, L"  %u# MountPoint: %s - UNC: %s - DeviceName: %s\n",
                 p, dokanControl[p].MountPoint, dokanControl[p].UNCName,
                 dokanControl[p].DeviceName);
      }
    } else {
      fwprintf(stderr, L"  Cannot retrieve mount point list.\n");
    }
    free(dokanControl);
  } break;

  case L'v': {
    fprintf(stdout, "dokanctl : %s %s\n", __DATE__, __TIME__);
    fprintf(stdout, "Dokan version : %d\n", DokanVersion());
    fprintf(stdout, "Dokan driver version : 0x%lx\n", DokanDriverVersion());
  } break;

  DEFAULT:
  default:
    fprintf(stderr, "Unknown option - Use /? to show usage\n");
  }

  return EXIT_SUCCESS;
}