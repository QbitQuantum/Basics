bool COMXCoreComponent::Deinitialize(bool free_component /* = false */)
{
  OMX_ERRORTYPE omx_err;

  m_exit = true;

  m_flush_input   = true;
  m_flush_output  = true;

  if(m_handle && m_DllOMXOpen)
  {
    FlushAll();

    FreeOutputBuffers();
    FreeInputBuffers();

    TransitionToStateLoaded();

    if(free_component)
    {
      CLog::Log(LOGDEBUG, "COMXCoreComponent::Deinitialize : %s handle 0x%08x dllopen : %d\n", 
          m_componentName.c_str(), m_handle, m_DllOMXOpen);
      omx_err = m_DllOMX->OMX_FreeHandle(m_handle);
      if (omx_err != OMX_ErrorNone)
      {
        CLog::Log(LOGERROR, "COMXCoreComponent::Deinitialize - failed to free handle for component %s omx_err(0x%08x)", 
            m_componentName.c_str(), omx_err);
      }  
      m_handle = NULL;

      m_input_port      = 0;
      m_output_port     = 0;
      m_componentName   = "";
      m_resource_error  = false;
    }
  }

  return true;
}