/*!
  Unload the listen threads manager.
 */
int ListenThreads::terminate ()
{
  char buffer[256];

  list <SocketInformation*> sockets;

  list <SocketInformation*>::iterator it;
  list <SocketInformation*>::iterator end;

  if (fastRebooting)
    return 0;
  else if (committingFastReboot)
    {
      it = frPortsToRemove.begin ();
      end = frPortsToRemove.end ();
    }
  else
    {
      for (HashMap<u_short, SocketInformation*>::Iterator i = usedPorts.begin ();
           i != usedPorts.end (); i++)
      sockets.push_front (*i);
      it = sockets.begin ();
      end = sockets.end ();
      shutdown ();
    }

  while (it != end)
    {
      for (int t = 0; t < 2; t++)
        {
          Socket* serverSocket;
          int err;

          if (t == 0)
            serverSocket = (*it)->ipv4;
          else
            serverSocket = (*it)->ipv6;

          if (!serverSocket)
            continue;

          serverSocket->shutdown (SHUT_RDWR);
          for (;;)
            {
              try
                {
                  err = serverSocket->recv (buffer, 256, 0);
                }
              catch (...)
                {
                  break;
                }
            }

          serverSocket->close ();
          delete serverSocket;
        }
      delete (*it);
      it++;
    }

  /* If it is not a fast reboot then clear everything.  */
  if (!(fastRebooting || committingFastReboot))
    usedPorts.clear ();

  return 0;
}