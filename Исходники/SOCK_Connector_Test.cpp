static u_int
host_is_up (ACE_TCHAR hostname[])
{
  ACE_SOCK_Connector con;
  ACE_SOCK_Stream sock;

  // The ACE_INET_Addr construction causes gethostbyname_r to be
  // called, so we need to copy the hostname.
  ACE_TCHAR test_host[MAXHOSTNAMELEN];
  ACE_OS::strcpy (test_host, hostname);

  ACE_INET_Addr another_host ((u_short) 7, test_host);
  ACE_Time_Value timeout_value (5);
  int const status = con.connect (sock,
                                  another_host,
                                  &timeout_value);
  sock.close ();
  return status == 0  ?  1  :  0;
}