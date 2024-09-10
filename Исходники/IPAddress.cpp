bool IPAddress::IsLoopback() const
{
  if (family == IPFamily::IPv4)
  {
    return data.in4.s_addr == htonl(INADDR_LOOPBACK);
  }
  else
  if (IsMappedv4())
  {
    return ToUnmappedv4().IsLoopback();
  }
  else
  {
    return IN6_IS_ADDR_LOOPBACK(&data.in6);
  }
}