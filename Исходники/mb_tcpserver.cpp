void* TcpServer::MethodForThread(void* arg) {
  arg = arg;
  while (1) {
    WaitMessage(1000);
  }
  return NULL;
}