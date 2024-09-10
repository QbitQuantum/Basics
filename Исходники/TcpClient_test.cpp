 void sendDataByClient()
 {
     static int64_t i = 0;
     if (clientConnection)
     {
         Timestamp now = Timestamp::now();
         char str[] = "hello world";
         cout << "client send data : " << str << " at " << now.toString() <<"\n";
         clientConnection->send(str, sizeof(str));
     }
 }