    void shut_down()
    {
      ACE_SOCK_Stream stream;
      ACE_SOCK_Connector connect;

      if (connect.connect (stream, addr_) == -1)
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("(%t) %p Error while connecting\n"),
                    ACE_TEXT ("connect")));

      const ACE_TCHAR *sbuf = ACE_TEXT ("\011shutdown");

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("shutdown stream handle = %x\n"),
                  stream.get_handle ()));

      if (stream.send_n (sbuf, (ACE_OS::strlen (sbuf) + 1) * sizeof (ACE_TCHAR)) == -1)
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("(%t) %p\n"),
                    ACE_TEXT ("send_n")));

      stream.close ();
    }