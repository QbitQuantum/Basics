/**
 * Sent it to all connected sockets
 */
void sendPayloadToSockets(Nrf24Payload payload)
{
  char buf[MAX_SOCKET_BYTES];
  bzero(buf, MAX_SOCKET_BYTES);
  sprintf (buf, ":,%c,%c,%d,%d,%d,%d,%d,%d\n",
    payload.getDeviceId(),
    payload.getType(),
    payload.getId(),
    payload.getVcc(),
    payload.getA(),
    payload.getB(),
    payload.getC(),
    payload.getD());

  for (int i = 0; i < FD_SETSIZE; ++i) {
    if (FD_ISSET (i, &active_fd_set) && i != master_socket) {
      int n = write(i, buf, MAX_SOCKET_BYTES);
      if (n < 0) {
        perror("sendPayloadToSockets ERROR writing to socket");
      }
    }
  }
}