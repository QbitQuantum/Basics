bool CResourceFile::TranslatePath(const CURL &url, std::string &translatedPath)
{
  translatedPath = url.Get();

  // only handle resource:// paths
  if (!url.IsProtocol("resource"))
    return false;

  // the share name represents an identifier that can be mapped to an addon ID
  std::string addonId = url.GetHostName();
  if (addonId.empty())
    return false;

  AddonPtr addon;
  if (!CAddonMgr::Get().GetAddon(addonId, addon, ADDON_UNKNOWN, true) || addon == NULL)
    return false;

  std::shared_ptr<CResource> resource = std::dynamic_pointer_cast<ADDON::CResource>(addon);
  if (resource == NULL)
    return false;

  std::string filePath = url.GetFileName();
  if (!resource->IsAllowed(filePath))
    return false;

  translatedPath = CUtil::ValidatePath(resource->GetFullPath(filePath));
  return true;
}