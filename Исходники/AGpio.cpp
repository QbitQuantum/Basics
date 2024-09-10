 AGPIO::AGPIO(const char*fdPath,int ioID)
 {
     openStatus = 0;
     fdGpio = 0;
     if(fdOpen(fdPath) < 0)
     {
         LOG2("androidUAV:Error occur\n");
     }
     setIoID(ioID);
 }