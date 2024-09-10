ULONG WINAPI ControlCallback(
                             WMIDPREQUESTCODE RequestCode,
                             PVOID Context,
                             ULONG *Reserved,
                             PVOID Buffer
                             )
{
  ProbeManager* context = (ProbeManager*)Context;
  switch(RequestCode)
  {
  case WMI_ENABLE_EVENTS: 
    {
      context->mIsActive = true;
      TRACEHANDLE sessionHandle = GetTraceLoggerHandle(Buffer);
      //Note: We only accept one handle
      if ((HANDLE)sessionHandle == INVALID_HANDLE_VALUE) {
        ULONG result = GetLastError();
        LOG(("Probes: ControlCallback failed, %ul", result));
        return result;
      } else if (context->mIsActive && context->mSessionHandle
                && context->mSessionHandle != sessionHandle) {
        LOG(("Probes: Can only handle one context at a time, "
             "ignoring activation"));
        return ERROR_SUCCESS;
      } else {
        context->mSessionHandle = sessionHandle;
        LOG(("Probes: ControlCallback activated"));
        return ERROR_SUCCESS;
      }
    }

  case WMI_DISABLE_EVENTS:
    context->mIsActive      = false;
    context->mSessionHandle = 0;
    LOG(("Probes: ControlCallback deactivated"));
    return ERROR_SUCCESS;

  default:
    LOG(("Probes: ControlCallback does not know what to do with %d",
         RequestCode));
    return ERROR_INVALID_PARAMETER;
  }
}