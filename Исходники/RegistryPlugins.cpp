static bool ReadPluginInfo(CPluginInfo &pluginInfo)
{
  {
    NDLL::CLibrary library;
    if (!library.LoadEx(pluginInfo.FilePath, LOAD_LIBRARY_AS_DATAFILE))
      return false;
  }
  NDLL::CLibrary library;
  if (!library.Load(pluginInfo.FilePath))
    return false;
  GetPluginPropertyFunc getPluginProperty = (GetPluginPropertyFunc)
    library.GetProcAddress("GetPluginProperty");
  if (getPluginProperty == NULL)
    return false;
  
  NCOM::CPropVariant propVariant;
  if (getPluginProperty(NPlugin::kName, &propVariant) != S_OK)
    return false;
  if (propVariant.vt != VT_BSTR)
    return false;
  pluginInfo.Name = propVariant.bstrVal;
  propVariant.Clear();
  
  if (getPluginProperty(NPlugin::kClassID, &propVariant) != S_OK)
    return false;
  if (propVariant.vt == VT_EMPTY)
    pluginInfo.ClassIDDefined = false;
  else if (propVariant.vt != VT_BSTR)
    return false;
  else
  {
    pluginInfo.ClassIDDefined = true;
    pluginInfo.ClassID = *(const GUID *)propVariant.bstrVal;
  }
  propVariant.Clear();
  
  if (getPluginProperty(NPlugin::kOptionsClassID, &propVariant) != S_OK)
    return false;
  if (propVariant.vt == VT_EMPTY)
    pluginInfo.OptionsClassIDDefined = false;
  else if (propVariant.vt != VT_BSTR)
    return false;
  else
  {
    pluginInfo.OptionsClassIDDefined = true;
    pluginInfo.OptionsClassID = *(const GUID *)propVariant.bstrVal;
  }
  propVariant.Clear();

  if (getPluginProperty(NPlugin::kType, &propVariant) != S_OK)
    return false;
  if (propVariant.vt == VT_EMPTY)
    pluginInfo.Type = kPluginTypeFF;
  else if (propVariant.vt == VT_UI4)
    pluginInfo.Type = (EPluginType)propVariant.ulVal;
  else
    return false;
  return true;
}