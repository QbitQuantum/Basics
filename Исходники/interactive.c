static DWORD
HandleFlushNeighborsMessage (flush_neighbors_message_t *msg)
{
  typedef NETIOAPI_API (*FlushIpNetTable2Fn) (ADDRESS_FAMILY, NET_IFINDEX);
  static FlushIpNetTable2Fn flush_fn = NULL;

  if (msg->family == AF_INET)
    return FlushIpNetTable (msg->iface.index);

  if (!flush_fn)
    {
      HMODULE iphlpapi = GetModuleHandle (TEXT("iphlpapi.dll"));
      if (iphlpapi == NULL)
        return GetLastError ();

      flush_fn = (FlushIpNetTable2Fn) GetProcAddress (iphlpapi, "FlushIpNetTable2");
      if (!flush_fn)
        {
          if (GetLastError () == ERROR_PROC_NOT_FOUND)
            return WSAEPFNOSUPPORT;
          else
            return GetLastError ();
        }
    }
  return flush_fn (msg->family, msg->iface.index);
}