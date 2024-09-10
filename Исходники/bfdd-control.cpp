  /**
   *
   *
   * @param message
   * @param message_size
   * @param port
   * @param outPrefix [in] - If not null, then every response line will be
   *                  prefixed with this string.
   *
   * @return bool
   */
  static bool SendData(const char *message, size_t message_size, const SockAddr &connectAddr, const char *outPrefix = NULL)
  {
    size_t totalLength;

    vector<char> buffer(max(MaxReplyLineSize,  MaxCommandSize));
    Socket sendSocket;
    FileHandle fileHandle;
    uint32_t magic;

    if (!sendSocket.OpenTCP(connectAddr.Type()))
    {
      fprintf(stderr, "Error creating %s socket: %s\n",
              Addr::TypeToString(connectAddr.Type()),
              SystemErrorToString(sendSocket.GetLastError()));
      return false;
    }


    if (!sendSocket.Connect(connectAddr))
    {
      fprintf(stderr, "Error connecting to beacon on %s: %s\n",
              connectAddr.ToString(),
              SystemErrorToString(sendSocket.GetLastError()));
      return false;
    }

    // Assemble the message
    magic = htonl(MagicMessageNumber);
    memcpy(&buffer.front(), &magic, sizeof(uint32_t));
    totalLength = message_size + sizeof(uint32_t);
    if (totalLength > MaxCommandSize)
    {
      fputs("Command too long. Not Sent.\n", stderr);
      return false;
    }

    memcpy(&buffer[sizeof(uint32_t)], message, message_size);

    // Send our message.
    if (!sendSocket.Send(&buffer.front(), totalLength))
    {
      fprintf(stderr, "Error sending command to beacon: %s\n", SystemErrorToString(sendSocket.GetLastError()));
      return false;
    }

    // Use stdio for simpler reading of the socket.
    fileHandle = fdopen(sendSocket, "r");
    if (!fileHandle.IsValid())
    {
      perror("Error opening socket file: ");
      return false;
    }

    // Read until done
    while (fgets(&buffer.front(), buffer.size(), fileHandle))
    {
      if (outPrefix)
        fputs(outPrefix, stdout);

      fputs(&buffer.front(), stdout);
    }

    if (ferror(fileHandle))
    {
      perror("\nConnection failed. Partial completion may have occurred: \n");
      return true;
    }

    return true;
  }