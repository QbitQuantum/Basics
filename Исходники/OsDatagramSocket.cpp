int OsDatagramSocket::read(char* buffer, int bufferLength)
{
    int bytesRead;

    // If the remote end is not "connected" we cannot use recv
    if(mSimulatedConnect || !portIsValid(remoteHostPort) || remoteHostName.isNull())
    {
#ifdef GETFROMINFO /* [ */
        if (GETFROMINFO) {
          int fromPort;
          UtlString fromAddress;
          bytesRead = OsSocket::read(buffer, bufferLength,
             &fromAddress, &fromPort);
          fromAddress.remove(0);
        } else
#endif /* GETFROMINFO ] */
        {
           bytesRead = OsSocket::read(buffer, bufferLength,
              (struct in_addr*) NULL, NULL);
        }
    }
    else
    {
        bytesRead = OsSocket::read(buffer, bufferLength);
    }
    return(bytesRead);
}