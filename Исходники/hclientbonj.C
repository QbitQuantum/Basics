void ConnectToServer(const TInetAddress *hostb, Int_t port)
{
   // Called by the Bonjour resolver with the host and port to which
   // we can connect.

   // Connect only once...
   TBonjourResolver *resolver = (TBonjourResolver*) gTQSender;
   TInetAddress host = *hostb; 
   delete resolver;

   printf("ConnectToServer: host = %s, port = %d\n", host.GetHostName(), port);

   //--- Here starts original hclient.C code ---

   // Open connection to server
   TSocket *sock = new TSocket(host.GetHostName(), port);

   // Wait till we get the start message
   char str[32];
   sock->Recv(str, 32);

   // server tells us who we are
   int idx = !strcmp(str, "go 0") ? 0 : 1;

   Float_t messlen  = 0;
   Float_t cmesslen = 0;
   if (idx == 1)
      sock->SetCompressionLevel(1);

   TH1 *hpx;
   if (idx == 0) {
      // Create the histogram
      hpx = new TH1F("hpx","This is the px distribution",100,-4,4);
      hpx->SetFillColor(48);  // set nice fillcolor
   } else {
      hpx = new TH2F("hpxpy","py vs px",40,-4,4,40,-4,4);
   }

   TMessage::EnableSchemaEvolutionForAll(gEvo);
   TMessage mess(kMESS_OBJECT);
   //TMessage mess(kMESS_OBJECT | kMESS_ACK);

   // Fill histogram randomly
   gRandom->SetSeed();
   Float_t px, py;
   const int kUPDATE = 1000;
   for (int i = 0; i < 25000; i++) {
      gRandom->Rannor(px,py);
      if (idx == 0)
         hpx->Fill(px);
      else
         hpx->Fill(px,py);
      if (i && (i%kUPDATE) == 0) {
         mess.Reset();              // re-use TMessage object
         mess.WriteObject(hpx);     // write object in message buffer
         sock->Send(mess);          // send message
         messlen  += mess.Length();
         cmesslen += mess.CompLength();
      }
   }
   sock->Send("Finished");          // tell server we are finished

   if (cmesslen > 0)
      printf("Average compression ratio: %g\n", messlen/cmesslen);

   gBenchmark->Show("hclient");

   // Close the socket
   sock->Close();
}