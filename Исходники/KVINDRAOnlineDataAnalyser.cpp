void KVINDRAOnlineDataAnalyser::ecouteSockets(void* arg)
{
   // static method, lance dans un thread
   // listen to the sockets

   TThread::Printf("<KVINDRAOnlineDataAnalyser::ecouteSockets> : beginning thread");
   KVINDRAOnlineDataAnalyser* ANA = (KVINDRAOnlineDataAnalyser*)arg;
   TServerSocket* fServer = new TServerSocket(ANA->port, kTRUE);

   if (!fServer->IsValid()) TThread::Printf("<KVINDRAOnlineDataAnalyser::ecouteSockets> : Port %d not valid", ANA->port);
   TMonitor* fMonitor = new TMonitor;
   fMonitor->Add(fServer);

   while (1) {

      TSocket* ss = fMonitor->Select();
      if (ss <= (TSocket*)0) continue;

      if (ss->IsA() == TServerSocket::Class()) {
         // new connection ?
         TSocket* s0 = fServer->Accept();
         if (s0) {
            TThread::Printf("<KVINDRAOnlineDataAnalyser::ecouteSockets> : Client found at %s",
                            s0->GetInetAddress().GetHostName());
            fMonitor->Add(s0);
         }
         continue;
      }
      if (ss->IsA() != TSocket::Class()) continue;

      TMessage* mess;
      if (ss->Recv(mess) <= 0) {
         // socket has been closed (?)
         TThread::Printf("<KVINDRAOnlineDataAnalyser::ecouteSockets> : connection from %s has been closed", ss->GetInetAddress().GetHostName());
         fMonitor->Remove(ss);
         delete ss;
         continue;
      }

      if (mess->What() == kMESS_STRING) {

         // deal with commands
         char str[256];
         mess->ReadString(str, 256);
         TThread::Printf("<KVINDRAOnlineDataAnalyser::ecouteSockets> : Received: %s", str);
         TString command(str);
         //command.ToUpper();
         ANA->HandleCommands(command, ss);

      }/* else if (mess->What() == kMESS_OBJECT) {
         TThread::Printf("<KVINDRAOnlineDataAnalyser::ecouteSockets> : Received UN P***IN d'OBJET!!!");
      } else {
         TThread::Printf("<KVINDRAOnlineDataAnalyser::ecouteSockets> : *** Unexpected message ***");
      }*/

      delete mess;
   }
}