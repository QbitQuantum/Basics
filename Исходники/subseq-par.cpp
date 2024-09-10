  // Prijem a zpracovani prichozich zprav ve stavu, kdy proces nema praci
  void inactiveRecvLoop() {
    string recvMsg;
    
    while (true) {
                
      // Blokujici cekani dokud neprijde zprava 
      mpi::status status = com.probe();

      // Prisly data - hura do prace!
      if (status.tag() == DATA) {
        //cout << "inactive: recv data from " << status.source() << endl;
        com.recv(status.source(), status.tag(), data.startString);
        work();
      } 
                
      // Pozadany proces nema zadnou praci na rozdani
      // Posle se novy pozadavek o praci nahodnemu procesu
      else if (status.tag() == NO_WORK) {
        //cout << "inactive: recv no_work from " << status.source() << endl;
        com.recv(status.source(), status.tag());
        sendRequest();
      } 
      
      // Prisel pozadavek o praci, sam ale zadnou nemam
      else if (status.tag() == WORK_REQUEST) {
        //cout << "inactive: recv work_req from " << status.source() << endl;
        com.recv(status.source(), status.tag());
        //cout << "Sending NO_WORK to " << status.source() << endl;
        com.send(status.source(), NO_WORK);
      } 
      
      // Prisel token, zpracovani se lisi podle toho, zda jsem master nebo slave proces
      else if (status.tag() == TOKEN) {
        bool isWhiteToken;
        //cout << "inactive: recv token from " << status.source() << endl;
        com.recv(status.source(), status.tag(), isWhiteToken);
        if (handleToken(isWhiteToken)) {
          return;
        }
      } 

      // Prislo oznameni o nalezeni nejake podsekvence
      // Pokud je delsi nez moje nejlepsi nalezena, ulozim si ji
      else if (status.tag() == FOUND) {
        cout << "inactive: recv found from " << status.source() << endl;
        com.recv(status.source(), status.tag(), recvMsg);
        if (recvMsg.length() > myLongest.length()) {
          myLongest = recvMsg;
        }
      }
                
      // Nektery proces nasel nejlepsi vysledek, ulozim si ho a koncim cekani/praci
      else if (status.tag() == FOUND_BEST) {
        cout << "inactive: recv found best from " << status.source() << endl;
        com.recv(status.source(), status.tag(), myLongest);
        return;
      }
      
      // Info od master procesu, ze vypocet uspesne skoncil - je mozne se vypnout
      else if (status.tag() == END) {
        //cout << "inactive: recv end from " << status.source() << endl;
        return;
      }
      
      // Prisla zprava, kterou prave neumim zpracovat, vyzvednu a zahodim
      else {
        //cout << "inactive: recv from " << status.source() << endl;
        com.recv(status.source(), status.tag());
      }
    } 
  }