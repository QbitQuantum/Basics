  void handleConnect(Socket::ptr socket) {
      char buf[10];
      while(1) { 
          //receive will switch the contex to epoll fiber
             size_t len = socket->receive(buf, sizeof(buf));
             if(len == 0) {
                printf("receive 0, closed by remote\n");
                break;
             }
             socket->send(buf, len);
       }
       socket->shutdown();
 }