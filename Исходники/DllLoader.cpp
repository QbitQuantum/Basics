// This function is even more a hack
// It will remove the dll from the Debug manager
// but vs.net does not unload the symbols (don't know why)
// The dll can be loaded again after unloading.
// This function leaks memory.
void DllLoader::UnloadSymbols()
{
#ifdef ENABLE_SYMBOL_UNLOADING
  ANSI_STRING name;
  OBJECT_ATTRIBUTES attributes;
  RtlInitAnsiString(&name, GetName());
  InitializeObjectAttributes(&attributes, &name, OBJ_CASE_INSENSITIVE, NULL);

  // Try to unload the symbols from vs.net debugger
  DbgUnLoadImageSymbols(&name, (ULONG)hModule, 0xFFFFFFFF);

  LPVOID pBaseAddress=GetXbdmBaseAddress();

  if (pBaseAddress)
  {
    CoffLoader dllxbdm;
    if (dllxbdm.ParseHeaders(pBaseAddress))
    {
      int offset=GetDmiOffset(dllxbdm.WindowsHeader->CheckSum);

      if (offset==0)
      {
        CLog::Log(LOGDEBUG,"DllLoader: Unable to unload symbols for %s. No offset for xbdm.dll with checksum 0x%08X found", GetName(), dllxbdm.WindowsHeader->CheckSum);
        return;
      }

      try
      {
        std::wstring strNameW;
        g_charsetConverter.utf8ToW(GetName(), strNameW);

        // Get the address of the global struct g_dmi
        // It is located inside the xbdm.dll and
        // get the LoadedModuleList member (here the entry var)
        // of the structure.
        LPBYTE g_dmi=((LPBYTE)pBaseAddress)+offset;
        LIST_ENTRY* entry=(LIST_ENTRY*)(g_dmi+4);

        //  Search for the dll we are unloading...
        while (entry)
        {
          std::wstring baseName=(wchar_t*)((LDR_DATA_TABLE_ENTRY*)entry)->BaseDllName.Buffer;
          if (baseName == strNameW)
          {
            // ...and remove it from the LoadedModuleList and free its memory.
            LIST_ENTRY* back=entry->Blink;
            LIST_ENTRY* front=entry->Flink;
            back->Flink=front;
            front->Blink=back;
            DmFreePool(entry);
            break;
          }

          entry=entry->Flink;
        }
      }
      catch(...)
      {
        CLog::Log(LOGDEBUG,"DllLoader: Unloading symbols for %s failed with an exception.", GetName());
      }
    }
  }
  else
    CLog::Log(LOGDEBUG,"DllLoader: Can't unload symbols for %s. xbdm.dll is needed and not loaded", GetName());
#endif
}