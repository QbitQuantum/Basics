void KeepModuleAlive()
{
  // deliberately omitting GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT to bump refcount
  GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (const char *)&ownModuleHandle,
                     &ownModuleHandle);
}