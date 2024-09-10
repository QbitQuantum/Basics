TcpConnection TcpListener::accept() {
  assert(dispatcher != nullptr);
  assert(context == nullptr);
  if (dispatcher->interrupted()) {
    throw InterruptedException();
  }

  std::string message;
  SOCKET connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (connection == INVALID_SOCKET) {
    message = "socket failed, " + errorMessage(WSAGetLastError());
  } else {
    uint8_t addresses[sizeof sockaddr_in * 2 + 32];
    DWORD received;
    TcpListenerContext context2;
    context2.hEvent = NULL;
    if (acceptEx(listener, connection, addresses, 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &received, &context2) == TRUE) {
      message = "AcceptEx returned immediately, which is not supported.";
    } else {
      int lastError = WSAGetLastError();
      if (lastError != WSA_IO_PENDING) {
        message = "AcceptEx failed, " + errorMessage(lastError);
      } else {
        context2.context = dispatcher->getCurrentContext();
        context2.interrupted = false;
        context = &context2;
        dispatcher->getCurrentContext()->interruptProcedure = [&]() {
          assert(dispatcher != nullptr);
          assert(context != nullptr);
          TcpListenerContext* context2 = static_cast<TcpListenerContext*>(context);
          if (!context2->interrupted) {
            if (CancelIoEx(reinterpret_cast<HANDLE>(listener), context2) != TRUE) {
              DWORD lastError = GetLastError();
              if (lastError != ERROR_NOT_FOUND) {
                throw std::runtime_error("TcpListener::stop, CancelIoEx failed, " + lastErrorMessage());
              }

              context2->context->interrupted = true;
            }

            context2->interrupted = true;
          }
        };

        dispatcher->dispatch();
        dispatcher->getCurrentContext()->interruptProcedure = nullptr;
        assert(context2.context == dispatcher->getCurrentContext());
        assert(dispatcher != nullptr);
        assert(context == &context2);
        context = nullptr;
        DWORD transferred;
        DWORD flags;
        if (WSAGetOverlappedResult(listener, &context2, &transferred, FALSE, &flags) != TRUE) {
          lastError = WSAGetLastError();
          if (lastError != ERROR_OPERATION_ABORTED) {
            message = "AcceptEx failed, " + errorMessage(lastError);
          } else {
            assert(context2.interrupted);
            if (closesocket(connection) != 0) {
              throw std::runtime_error("TcpListener::accept, closesocket failed, " + errorMessage(WSAGetLastError()));
            } else {
              throw InterruptedException();
            }
          }
        } else {
          assert(transferred == 0);
          assert(flags == 0);
          if (setsockopt(connection, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<char*>(&listener), sizeof listener) != 0) {
            message = "setsockopt failed, " + errorMessage(WSAGetLastError());
          } else {
            if (CreateIoCompletionPort(reinterpret_cast<HANDLE>(connection), dispatcher->getCompletionPort(), 0, 0) != dispatcher->getCompletionPort()) {
              message = "CreateIoCompletionPort failed, " + lastErrorMessage();
            } else {
              return TcpConnection(*dispatcher, connection);
            }
          }
        }
      }
    }

    int result = closesocket(connection);
    assert(result == 0);
  }

  throw std::runtime_error("TcpListener::accept, " + message);
}