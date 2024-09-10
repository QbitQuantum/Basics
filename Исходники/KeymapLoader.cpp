bool CKeymapLoader::FindMappedDevice(const CStdString& deviceId, CStdString& keymapName)
{
  CStdString deviceIdTemp = deviceId;
  std::map<CStdString, CStdString>::iterator deviceIdIt = deviceMappings.find(deviceIdTemp.ToUpper());
  if (deviceIdIt == deviceMappings.end())
    return false;

  keymapName = deviceIdIt->second;
  return true;
}