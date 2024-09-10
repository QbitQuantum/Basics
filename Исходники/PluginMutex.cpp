CPluginMutex::CPluginMutex(const std::wstring& name, int errorSubidBase) 
  : m_isLocked(false), m_errorSubidBase(errorSubidBase), system_name(L"Global\\AdblockPlus" + name)
{
  if (m_errorSubidBase != PLUGIN_ERROR_MUTEX_DEBUG_FILE)
  {
    DEBUG_MUTEX(L"Mutex::Create name:" + name)
  }
  m_hMutex = CreateMutexW(NULL, FALSE, system_name.c_str());

  if (m_hMutex == NULL)
  {
    DWORD error = GetLastError();
    m_hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, system_name.c_str());
    if (m_hMutex == NULL)
    {
      system_name = L"Local\\AdblockPlus" + name;
      m_hMutex = CreateMutexW(NULL, FALSE, system_name.c_str());
      if (m_hMutex == NULL)
      {
        m_hMutex = OpenMutexW(NULL, FALSE, system_name.c_str());
        if (m_hMutex == NULL)
        {
          DWORD error = GetLastError();
          DEBUG_ERROR_LOG(::GetLastError(), PLUGIN_ERROR_MUTEX, PLUGIN_ERROR_MUTEX_CREATE + m_errorSubidBase, "Mutex::CreateMutex");
        }
      }
      else
      // TODO: Combine this block with identical one below.
      {
        switch (::WaitForSingleObject(m_hMutex, 3000))
        {
          // The thread got ownership of the mutex
        case WAIT_OBJECT_0: 
          m_isLocked = true;
          break;

        case WAIT_TIMEOUT:
          DEBUG_ERROR_LOG(::GetLastError(), PLUGIN_ERROR_MUTEX, PLUGIN_ERROR_MUTEX_WAIT_TIMEOUT + m_errorSubidBase, "Mutex::CreateMutex - Timeout");
          m_hMutex = NULL;
          break;

        case WAIT_FAILED:
          DEBUG_ERROR_LOG(::GetLastError(), PLUGIN_ERROR_MUTEX, PLUGIN_ERROR_MUTEX_WAIT + m_errorSubidBase, "Mutex::CreateMutex - Wait error");
          break;
        }
      }

    }
  }
  else
  // TODO: Combine this block with identical one above.
  {
    switch (::WaitForSingleObject(m_hMutex, 3000))
    {
      // The thread got ownership of the mutex
    case WAIT_OBJECT_0: 
      m_isLocked = true;
      break;

    case WAIT_TIMEOUT:
      DEBUG_ERROR_LOG(::GetLastError(), PLUGIN_ERROR_MUTEX, PLUGIN_ERROR_MUTEX_WAIT_TIMEOUT + m_errorSubidBase, "Mutex::CreateMutex - Timeout");
      m_hMutex = NULL;
      break;

    case WAIT_FAILED:
      DEBUG_ERROR_LOG(::GetLastError(), PLUGIN_ERROR_MUTEX, PLUGIN_ERROR_MUTEX_WAIT + m_errorSubidBase, "Mutex::CreateMutex - Wait error");
      break;
    }
  }
}