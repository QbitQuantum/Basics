void TransportBridge::recv_json(rapidjson::Document* document) {
  char recvbuf[BRIDGE_RECV_BUFSIZE];
  int iResult;
  int pos = 0;
  int len;

  // First info should be the number of bytes in the string followed by newline.
  while (1) {
    iResult = recv(bridge_socket, recvbuf + pos, 1, 0);
    if (iResult == 0) {
      // Connection closed.
      bridge_error("Remote bridge closed trying to read length.\n");
    }
    else if (iResult != 1) {
      // Some other error
      bridge_error("recv failed reading length with error: %d\n", WSAGetLastError());
    }
    // Read one byte. If it's newline, we should have now received a full length string.
    if (recvbuf[pos] == '\n') {
      break;
    }
    // Error if it isn't a digit.
    if (!isdigit(recvbuf[pos])) {
      bridge_error("recv got a non-digit in the length field.\n");
    }
    if (pos >= BRIDGE_RECV_BUFSIZE-1) {
      bridge_error("recv got a very long length field.\n");
    }
    pos++;
  }
  // If we get here, we should have a legal length in recvbuf.
  len = -1;
  if (sscanf_s(recvbuf, "%d", &len) != 1 || len < 1) {
    bridge_error("Got illegal length string \"%s\"\n", recvbuf);
  }
  if (len >= BRIDGE_RECV_BUFSIZE-1) {
    bridge_error("length too long (max %d, got %d)\n", BRIDGE_RECV_BUFSIZE, len);
  }
  // Now read until we get len bytes.
  int nread = 0;
  while (nread < len) {
    iResult = recv(bridge_socket, recvbuf + nread, len - nread, 0);
    if (iResult == 0) {
      bridge_error("Remote bridge closed.\n");
    }
    else if (iResult < 0) {
      bridge_error("recv failed with error: %d\n", WSAGetLastError());
    }
    nread += iResult;
  }
  recvbuf[nread] = 0; // null terminate.
  document->SetArray(); // This should clear any existing allocation. Not sure if needed.

  FILE * recvbuf_file;
  recvbuf_file = fopen("C:/Users/Vivek Raghuram/Desktop/recvbuf.txt", "a");
  fprintf(recvbuf_file, recvbuf);
  fprintf(recvbuf_file, ".\n");
  fclose(recvbuf_file);

  document->Parse(recvbuf); // Parse the json into the document.
}  // TransportBridge::recv_json()