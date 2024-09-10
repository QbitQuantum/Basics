// Get current refresh rate on Win7
double W7GetRefreshRate(int monitorIdx)
{
  UINT32 uNumPathArrayElements = 0;
  UINT32 uNumModeInfoArrayElements = 0;
  DISPLAYCONFIG_PATH_INFO* pPathInfoArray = NULL;
  DISPLAYCONFIG_MODE_INFO* pModeInfoArray = NULL;
  DISPLAYCONFIG_TOPOLOGY_ID* pCurrentTopologyId = NULL;
  LONG result;
  double refreshRate = -1;
  DISPLAY_DEVICE displayDevice;
  displayDevice.cb = sizeof(DISPLAY_DEVICE);
  DEVMODE devMode;
  devMode.dmSize = sizeof(DEVMODE);
  DEVMODE *paDeviceMode;

  if(EnumDisplayDevices(NULL, monitorIdx, &displayDevice, 0))
  {
    EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode);
  }
  paDeviceMode = &devMode;

  // Get size of buffers for QueryDisplayConfig
  result = GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &uNumPathArrayElements, &uNumModeInfoArrayElements);
  if (result != 0)
  {
    return(refreshRate);
  }

  // allocate memory for QueryDisplayConfig buffers
  pPathInfoArray = (DISPLAYCONFIG_PATH_INFO*)calloc(uNumPathArrayElements, sizeof(DISPLAYCONFIG_PATH_INFO));
  if (pPathInfoArray == NULL)
  {
    return(refreshRate);
  }

  pModeInfoArray = (DISPLAYCONFIG_MODE_INFO*)calloc(uNumModeInfoArrayElements, sizeof(DISPLAYCONFIG_MODE_INFO));
  if (pModeInfoArray == NULL)
  {
    // freeing memory
    free(pPathInfoArray);
    return(refreshRate);
  }

  // get display configuration
  result = QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, 
                              &uNumPathArrayElements, pPathInfoArray, 
                              &uNumModeInfoArrayElements, pModeInfoArray,
                              pCurrentTopologyId);
  if (result == 0)
  {
    //// Get information from active target path and based on current dimension (support for multiple displays)
    for (UINT i = 0; i < uNumPathArrayElements; ++i)
    {
      UINT iModIdx = pPathInfoArray[i].sourceInfo.modeInfoIdx;
      if(pPathInfoArray[i].flags == DISPLAYCONFIG_PATH_ACTIVE && paDeviceMode[0].dmPosition.x == pModeInfoArray[iModIdx].sourceMode.position.x && paDeviceMode[0].dmPosition.y == pModeInfoArray[iModIdx].sourceMode.position.y)
      {
        if(paDeviceMode[0].dmPelsHeight == pModeInfoArray[iModIdx].sourceMode.height && paDeviceMode[0].dmPelsWidth == pModeInfoArray[iModIdx].sourceMode.width)
        {
          monitorIdx = i;
          DISPLAYCONFIG_PATH_TARGET_INFO target;
          target = pPathInfoArray[monitorIdx].targetInfo;
          LONG numerator = target.refreshRate.Numerator;
          LONG denominator = target.refreshRate.Denominator;
          refreshRate = (double)numerator/(double)denominator;
          break;
        }
      }
    }
  }
  // freeing memory
  free(pPathInfoArray);
  free(pModeInfoArray);

  return(refreshRate);
}