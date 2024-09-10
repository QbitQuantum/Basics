bool win32_exception::ShouldHook()
{
  if (!IsWindows8OrGreater())
    return true;

  bool result = true;

  auto module = ::LoadLibrary(L"kernel32.dll");
  if (module)
  {
    auto func = reinterpret_cast<GCPFN>(::GetProcAddress(module, "GetCurrentPackageFullName"));
    if (func)
    {
      UINT32 length = 0;
      auto r = func(&length, nullptr);
      result = r == APPMODEL_ERROR_NO_PACKAGE;
    }

    ::FreeLibrary(module);
  }

  return result;
}