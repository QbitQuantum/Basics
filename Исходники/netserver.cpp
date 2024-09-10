DWORD
NetServer::Reader(int index)
{
   // init random seed for this thread:
   srand(timeGetTime());

   while (!server_shutdown) {
      sync.acquire();
      NetSock* s = conn[index];
      sync.release();

      if (s) {
         const int MAX_REQUEST = 4096;
         Text request;

         /***
          *** NOT SURE WHY, BUT THIS DOESN'T WORK FOR SHIT
          ***
          *** Setting the socket timeout to 2 seconds caused it
          *** to wait for two seconds, read nothing, and give up
          *** with a WSAETIMEDOUT error.  Meanwhile, the client
          *** immediately registered a failure (during the 2 sec
          *** delay) and aborted the request.
          ***

         s->set_timeout(2000);
         Text msg = s->recv();

         while (msg.length() > 0 && request.length() < MAX_REQUEST) {
            request += msg;
            msg = s->recv();
         }

          ***/

         request = s->recv();

         if (request.length() > 0 && !s->is_closed()) {
            Text response = ProcessRequest(request, clients[index]);
            err = s->send(response);
            if (err < 0) {
               err = NetLayer::GetLastError();
            }
         }

         sync.acquire();
         delete conn[index];
         conn[index] = 0;
         sync.release();
      }
      else {
         Sleep(5);
      }
   }

   return 0;
}