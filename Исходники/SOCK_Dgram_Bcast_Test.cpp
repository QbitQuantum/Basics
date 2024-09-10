/*\brief Receive single datagram
  \note The function employes dgram_port and dgram_recv_timeout variables
  \retval -1 if not received,
  \retval 0  received a datagrams
*/
int run_receiver ()
{
  ACE_DEBUG
    ((LM_INFO,
      ACE_TEXT ("Receiving datagrams from port %d with timeout %d ms\n"),
      dgram_port, dgram_recv_timeout.msec ()));

  ACE_SOCK_Dgram socket;
  ACE_INET_Addr  remote ;
  static char    dgram_buffer[BUFSIZ];

  if (socket.open (ACE_INET_Addr (dgram_port)) != -1)
    if (socket.recv (dgram_buffer, sizeof (dgram_buffer),
                     remote, 0, &dgram_recv_timeout) > 0)
      {
        ACE_DEBUG ((LM_INFO, ACE_TEXT ("%C received\n"), dgram_buffer));
        return 0;
      }
    else
      {
        ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("%p\n"),
                           ACE_TEXT ("Cannot receive datagrams")), -1);
      }
  else
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%p: %d\n"),
                         ACE_TEXT ("Cannot open broadcast socket on port"), dgram_port), -1);
    }
}