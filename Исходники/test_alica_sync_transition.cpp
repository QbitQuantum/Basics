 virtual void TearDown()
 {
     ae->shutdown();
     ae2->shutdown();
     sc->shutdown();
     delete cc;
     delete bc;
     delete uc;
     delete crc;
     delete ae->getCommunicator();
     delete ae2->getCommunicator();
     delete ae;
     delete ae2;
 }