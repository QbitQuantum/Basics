static ACE_THR_FUNC_RETURN
cli_worker (void *arg)
{
  // Client thread function.
  ACE_INET_Addr addr (rendezvous);
  ACE_SOCK_Stream stream;
  ACE_SOCK_Connector connect;
  ACE_Time_Value delay (0, req_delay);
  size_t len = * reinterpret_cast<ACE_TCHAR *> (arg);

  for (size_t i = 0 ; i < cli_conn_no; i++)
    {
      if (connect.connect (stream, addr) < 0)
        {
          ACE_ERROR ((LM_ERROR,
                      "(%t) %p\n",
                      "connect"));
          continue;
        }

      for (size_t j = 0; j < cli_req_no; j++)
        {
          ACE_DEBUG ((LM_DEBUG,
                      "(%t) conn_worker handle 0x%x, req %d\n",
                      stream.get_handle (),
                      j+1));
          if (stream.send_n (arg,
                             (len + 1) * sizeof (ACE_TCHAR)) == -1)
            {
              ACE_ERROR ((LM_ERROR,
                          "(%t) %p\n",
                          "send_n"));
              continue;
            }
          ACE_OS::sleep (delay);
        }

      stream.close ();
    }

  return 0;
}