void unix_send_one_node(void *msg, size_t length, int dest)
{
  sendto(sock, (char*) msg, length, 0, (struct sockaddr*) &addresses[dest],
      sizeof(addresses[dest]));
}