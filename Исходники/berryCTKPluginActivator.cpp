QString org_blueberry_core_runtime_Activator::getPluginId(void *symbol)
{
  if (symbol == NULL) return QString();

  if (ctk::DebugSymInitialize())
  {
    std::vector<char> moduleBuffer(sizeof(IMAGEHLP_MODULE64));
    PIMAGEHLP_MODULE64 pModuleInfo = (PIMAGEHLP_MODULE64)&moduleBuffer.front();
    pModuleInfo->SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
    if (SymGetModuleInfo64(GetCurrentProcess(), (DWORD64)symbol, pModuleInfo))
    {
      QString pluginId = pModuleInfo->ModuleName;
      return pluginId.replace('_', '.');
    }
  }
  return QString();
}