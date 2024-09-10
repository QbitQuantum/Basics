void CWinSystemWin32DX::InitHooks(IDXGIOutput* pOutput)
{
  DXGI_OUTPUT_DESC outputDesc;
  if (!pOutput || FAILED(pOutput->GetDesc(&outputDesc)))
    return;

  DISPLAY_DEVICEW displayDevice;
  displayDevice.cb = sizeof(DISPLAY_DEVICEW);
  DWORD adapter = 0;
  bool deviceFound = false;

  // delete exiting hooks.
  UninitHooks();

  // enum devices to find matched
  while (EnumDisplayDevicesW(nullptr, adapter, &displayDevice, 0))
  {
    if (wcscmp(displayDevice.DeviceName, outputDesc.DeviceName) == 0)
    {
      deviceFound = true;
      break;
    }
    adapter++;
  }
  if (!deviceFound)
    return;

  CLog::Log(LOGDEBUG, __FUNCTION__": Hooking into UserModeDriver on device %S. ", displayDevice.DeviceKey);
  wchar_t* keyName =
#ifndef _M_X64
  // on x64 system and x32 build use UserModeDriverNameWow key
  CSysInfo::GetKernelBitness() == 64 ? keyName = L"UserModeDriverNameWow" :
#endif // !_WIN64
    L"UserModeDriverName";

  DWORD dwType = REG_MULTI_SZ;
  HKEY hKey = nullptr;
  wchar_t value[1024];
  DWORD valueLength = sizeof(value);
  LSTATUS lstat;

  // to void \Registry\Machine at the beginning, we use shifted pointer at 18
  if (ERROR_SUCCESS == (lstat = RegOpenKeyExW(HKEY_LOCAL_MACHINE, displayDevice.DeviceKey + 18, 0, KEY_READ, &hKey))
    && ERROR_SUCCESS == (lstat = RegQueryValueExW(hKey, keyName, nullptr, &dwType, (LPBYTE)&value, &valueLength)))
  {
    // 1. registry value has a list of drivers for each API with the following format: dx9\0dx10\0dx11\0dx12\0\0
    // 2. we split the value by \0
    std::vector<std::wstring> drivers;
    const wchar_t* pValue = value;
    while (*pValue)
    {
      drivers.push_back(std::wstring(pValue));
      pValue += drivers.back().size() + 1;
    }
    // no entries in the registry
    if (drivers.empty())
      return;
    // 3. we take only first three values (dx12 driver isn't needed if it exists ofc)
    if (drivers.size() > 3)
      drivers = std::vector<std::wstring>(drivers.begin(), drivers.begin() + 3);
    // 4. and then iterate with reverse order to start iterate with the best candidate for d3d11 driver
    for (auto it = drivers.rbegin(); it != drivers.rend(); ++it)
    {
      m_hDriverModule = LoadLibraryW(it->c_str());
      if (m_hDriverModule != nullptr)
      {
        s_fnOpenAdapter10_2 = reinterpret_cast<PFND3D10DDI_OPENADAPTER>(GetProcAddress(m_hDriverModule, "OpenAdapter10_2"));
        if (s_fnOpenAdapter10_2 != nullptr)
        {
          ULONG ACLEntries[1] = { 0 };
          m_hHook = new HOOK_TRACE_INFO();
          // install and activate hook into a driver
          if (SUCCEEDED(LhInstallHook(s_fnOpenAdapter10_2, HookOpenAdapter10_2, nullptr, m_hHook))
            && SUCCEEDED(LhSetInclusiveACL(ACLEntries, 1, m_hHook)))
          {
            CLog::Log(LOGDEBUG, __FUNCTION__": D3D11 hook installed and activated.");
            break;
          }
          else
          {
            CLog::Log(LOGDEBUG, __FUNCTION__": Unable ot install and activate D3D11 hook.");
            SAFE_DELETE(m_hHook);
            FreeLibrary(m_hDriverModule);
            m_hDriverModule = nullptr;
          }
        }
      }
    }
  }

  if (lstat != ERROR_SUCCESS)
    CLog::Log(LOGDEBUG, __FUNCTION__": error open registry key with error %ld.", lstat);

  if (hKey != nullptr)
    RegCloseKey(hKey);
}