// ================================================
// Main
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int main(int argc, char* argv[])
{
   CigiInSz = 0;
   
   ReadConfig();
   
   init_cigi_if();
   
   /* CIGI messaging */
   CigiOutgoingMsg &Omsg = *OmsgPtr;



   Omsg.BeginMsg();


   while(1)
   {
      cout << "================================\n";
      cout << "Frame: " << Omsg.GetFrameCnt() << endl;
      cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";

      /* process incoming CIGI message - this could be long */
      if( CigiInSz > 0 ) {
         try {
            ImsgPtr->ProcessIncomingMsg((unsigned char *)CInBuf,CigiInSz);
         }
         catch( CigiException &theException ){
            std::cout << "getNetMessages - Exception: " << theException.what() << std::endl;
         }
      }

      cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n";


      // load the IG Control
      Omsg << CSOF;



      // wait until start of frame time
      waitUntilBeginningOfFrame();


      // Do packaging here to 
      // Package msg
      try {
         Omsg.PackageMsg(&pCigiOutBuf,CigiOutSz);
      } catch( CigiException &theException ){
         std::cout << "getNetMessages - Exception: " << theException.what() << std::endl;
      }


      // Update Frame IDs
      Omsg.UpdateSOF(pCigiOutBuf);


      // send SOF message
      int sentBytes = network.send(pCigiOutBuf,CigiOutSz);


      // Check frame counter
		check_SOF.Unpack(pCigiOutBuf,false,NULL);
		cout << check_SOF.GetFrameCntr() << endl;


      Omsg.FreeMsg();   // Frees the buffer containing the message that was just sent


      // wait for Host message
      long HoldTime;
      bool RcvrProc = false;
      long CheckTime = (long)time(&HoldTime);
      while(!RcvrProc)
      {
         if((CigiInSz = network.recv( CInBuf, RECV_BUFFER_SIZE )) > 0)
            RcvrProc = true;
         else
         {
            long TstTime = (long)time(&HoldTime);
            if((TstTime - CheckTime) > 1)
            {
               cout << "Did not receive IG Control\n";
               RcvrProc = true;
               CigiInSz = 0;
            }
         }
      }

   }


   // shut down the network
   network.closeSocket();
   
   delete IGSn;
   
   return 0;
}