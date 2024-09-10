// ----------------------------------------------------------------------------
// SnoopAutoDetectAdapter
// ----------------------------------------------------------------------------
int SnoopAutoDetectAdapter::detect(QString& host)
{
  IP ip;
  DWORD  bestIfIndex;
  ip = htonl(VNet::resolve(host));
  DWORD res = GetBestInterface(ip, &bestIfIndex);
  if (res != NO_ERROR)
  {
    LOG_FATAL("GetBestInterface return %d", res);
    return snoop::INVALID_ADAPTER_INDEX;
  }

  foreach (const SnoopInterface& intf, SnoopInterfaces::instance())
  {
    if (intf.adapterInfo != NULL && intf.adapterInfo->Index == bestIfIndex)
      return intf.index;
  }

  LOG_FATAL("can not find appropriate adapter for %s", qPrintable(host));
  return snoop::INVALID_ADAPTER_INDEX;;
}