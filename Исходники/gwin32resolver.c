static DWORD WINAPI
lookup_service_in_thread (LPVOID data)
{
  GWin32ResolverRequest *req = data;

  req->u.service.retval =
    DnsQuery_A (req->u.service.rrname, DNS_TYPE_SRV, DNS_QUERY_STANDARD,
                NULL, &req->u.service.results, NULL);
  SetEvent (req->event);
  return 0;
}