 void OnMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time_)
 {
     LOG_DEBUG << conn->name();
     size_t len = buf->readableBytes();
     while (len >= kCells + 2)
     {
         const char* crlf = buf->findCRLF();
         if (crlf)
         {
             kimgbo::string request(buf->peek(), crlf);
             buf->retrieveUntil(crlf + 2);
             len = buf->readableBytes();
             if (!processRequest(conn, request))
             {
                 conn->send("Bad Request!\r\n");
                 conn->shutdown();
                 break;
             }
         }
         else if (len > 100) // id + ":" + kCells + "\r\n"
         {
             conn->send("Id too long!\r\n");
             conn->shutdown();
             break;
         }
         else
         {
             break;
         }
     }
 }