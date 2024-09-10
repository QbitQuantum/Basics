int send_unicast (const ACE_INET_Addr &to)
{
  const char *message = "this is the message!\n";
  ACE_INET_Addr my_addr (ACE_static_cast (u_short, 10101));
  ACE_SOCK_Dgram udp (my_addr);
  ssize_t sent = udp.send (message,
                           ACE_OS_String::strlen (message) + 1,
                           to);
  udp.close ();
  if (sent == -1)
    ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("%p\n"),
                       ACE_TEXT ("send")), -1);
  return 0;
}