WAI_NOINLINE
WAI_FUNCSPEC
int WAI_PREFIX(getModulePath)(char* out, int capacity, int* dirname_length)
{
  HMODULE module;
  int length = -1;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4054)
#endif
  if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)
  #if defined(_MSC_VER)
  _ReturnAddress()
  #else
  __builtin_extract_return_addr(__builtin_return_address(0))
  #endif
  , &module))
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
  {
    length = WAI_PREFIX(getModulePath_)(module, out, capacity, dirname_length);
  }

  return length;
}