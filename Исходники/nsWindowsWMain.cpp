int wmain(int argc, WCHAR **argv)
{
#if !defined(XRE_DONT_SUPPORT_XPSP2)
  WindowsCrtPatch::Init();
#endif

#if defined(_MSC_VER) && _MSC_VER < 1900 && defined(_M_X64)
  // Disable CRT use of FMA3 on non-AVX2 CPUs and on Win7RTM due to bug 1160148
  int cpuid0[4] = {0};
  int cpuid7[4] = {0};
  __cpuid(cpuid0, 0); // Get the maximum supported CPUID function
  __cpuid(cpuid7, 7); // AVX2 is function 7, subfunction 0, EBX, bit 5
  if (cpuid0[0] < 7 || !(cpuid7[1] & 0x20) || !mozilla::IsWin7SP1OrLater()) {
    _set_FMA3_enable(0);
  }
#endif

#ifndef XRE_DONT_PROTECT_DLL_LOAD
  mozilla::SanitizeEnvironmentVariables();
  SetDllDirectoryW(L"");
#endif

  char **argvConverted = new char*[argc + 1];
  if (!argvConverted)
    return 127;

  for (int i = 0; i < argc; ++i) {
    argvConverted[i] = AllocConvertUTF16toUTF8(argv[i]);
    if (!argvConverted[i]) {
      return 127;
    }
  }
  argvConverted[argc] = nullptr;

  // need to save argvConverted copy for later deletion.
  char **deleteUs = new char*[argc+1];
  if (!deleteUs) {
    FreeAllocStrings(argc, argvConverted);
    return 127;
  }
  for (int i = 0; i < argc; i++)
    deleteUs[i] = argvConverted[i];
#ifndef XRE_WANT_ENVIRON
  int result = main(argc, argvConverted);
#else
  // Force creation of the multibyte _environ variable.
  getenv("PATH");
  int result = main(argc, argvConverted, _environ);
#endif

  delete[] argvConverted;
  FreeAllocStrings(argc, deleteUs);

  return result;
}