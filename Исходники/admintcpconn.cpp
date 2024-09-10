void AdminTcpConnection::verCheck(){

  bool rtn = true;

  int32_t precheck = verCheckPreChecks();
  if(precheck != 1){
    rtn = false;
    if(precheck != -2){
      // if not non-block wait
      if(precheck == 0){
        Logger::getLogger()->info("Admin client disconnected in pre-check");
        close();
      }else{
        Logger::getLogger()->info("Error in pre-check, disconnecting");
        close();
      }
    }
  }
  if(!rtn)
    return;

  Frame *recvframe = new Frame(fv0_3);
  uint32_t hlen = recvframe->getHeaderLength();

  if(rheaderbuff == NULL){
    rbuffused = 0;
    rheaderbuff = new char[hlen];
  }

  if(rdatabuff == NULL && rbuffused < 4){
    int32_t len = underlyingRead(rheaderbuff+rbuffused, 4 - rbuffused);
    if(len == 0){
      Logger::getLogger()->info("Admin client disconnected");
      close();
      rtn = false;
    }else if(len > 0){
      rbuffused += len;
      if(rbuffused < 4){
        Logger::getLogger()->debug("ver check header not the length needed, delaying read");
        rtn = false;
      }
    }else{
      if(len != -2){
        Logger::getLogger()->warning("Socket error");
        close();
      }
      rtn = false;
    }
  }
  if(rtn && ((rdatabuff == NULL && rbuffused >= 4) || rdatabuff != NULL)){
    if(rheaderbuff[0] == 'T' && rheaderbuff[1] == 'P'){
      //assume we have TP procotol
      if(rheaderbuff[2] == '0'){
        if(rheaderbuff[3] <= '2'){
          Logger::getLogger()->warning("Admin client did not show correct version of protocol (version 2 or less)");
          sendDataAndClose("You are not running the right version of TP, please upgrade\n", 60);
          rtn = false;
        }else if(rheaderbuff[3] > '3'){
          //might be future version of protocol, just disconnect now
          Frame *f = new Frame(fv0_3);
          f->setSequence(0);
          f->createFailFrame(fec_ProtocolError, "TP Protocol, but I only support versions 2 and 3, sorry.");
          sendFrame(f);

          //stay connected just in case they try again with a lower version
          // have to empty the receive queue though.
          char* buff = new char[1024];
          int32_t len = underlyingRead(buff, 1024);
          Logger::getLogger()->debug("Read an extra %d bytes from the socket, into buffer of 1024", len);
          delete[] buff;
          rtn = false;
        }else{
          char ver[] = {'\0','\0','\0'};
          memcpy(ver, rheaderbuff+2 , 2);
          int nversion = atoi(ver);
          version = (ProtocolVersion)nversion;
        }
      }else if(rheaderbuff[2] >= 4 && rheaderbuff[2] < '0'){
        //tp04 and later
        version = (ProtocolVersion)rheaderbuff[2];
        if(version > fv0_4){
          Frame *f = new Frame(fv0_4);
          f->setSequence(0);
          f->createFailFrame(fec_ProtocolError, "TP Protocol, but I only support versions 4, sorry.");
          sendFrame(f);

          //stay connected just in case they try again with a lower version
          // have to empty the receive queue though.
          char* buff = new char[1024];
          int32_t len = underlyingRead(buff, 1024);
          Logger::getLogger()->debug("Read an extra %d bytes from the socket, into buffer of 1024", len);
          delete[] buff;
          rtn = false;
        }
      }else{
        //might be future version of protocol, just disconnect now
        Logger::getLogger()->warning("Unknown protocol version");

        //stay connected just in case they try again with a lower version
        // have to empty the receive queue though.
        char* buff = new char[1024];
        int32_t len = underlyingRead(buff, 1024);
        Logger::getLogger()->debug("Read an extra %d bytes from the socket, into buffer of 1024", len);
        delete[] buff;

        Frame *f = new Frame(fv0_3);
        f->setSequence(0);
        f->createFailFrame(fec_ProtocolError, "TP Protocol, but I only support versions 2 and 3, sorry.");
        sendFrame(f);

        delete[] rheaderbuff;
        rheaderbuff = NULL;
        rbuffused = 0;
        rtn = false;
      }

      if(rtn){
        Logger::getLogger()->info("Admin client has version %d of protocol", version);
        if(version != recvframe->getVersion()){
          delete recvframe;
          recvframe = new Frame(version);
        }
        if(readFrame(recvframe)){
          if(recvframe->getType() == ft02_Connect){
            std::string clientsoft = recvframe->unpackStdString();
            Logger::getLogger()->info("Admin client on connection %d is [%s]", sockfd, clientsoft.c_str());

            status = 2;

            Frame *okframe = createFrame(recvframe);
            okframe->setType(ft02_OK);

            okframe->packString("Protocol check ok, continue! Welcome to tpserver-cpp " VERSION);
            sendFrame(okframe);
          }else{
            Logger::getLogger()->warning("First frame wasn't Connect, was %d", recvframe->getType());
            Frame* fe = createFrame(recvframe);
            fe->createFailFrame(fec_ProtocolError, "First frame wasn't Connect, please try again");
            sendFrame(fe);
          }
        }else{
          Logger::getLogger()->debug("verCheck, did not get whole frame");
          rtn = false;
        }
      }
    }else{
      int32_t lastchance = verCheckLastChance();
      if(lastchance == 1){
        // last chance passed, try checking for frames again
        delete[] rheaderbuff;
        rheaderbuff = NULL;
      }else if(lastchance == -2){
        //waiting for more data
        rtn = false;
      }else{
        Logger::getLogger()->warning("Client did not talk any variant of TPprotocol");
        if(lastchance != 0){
          // send "I don't understand" message
          sendDataAndClose("You are not running the correct protocol\n", 41);
        }
        rtn = false;
      }
    }
  }else{
    rtn = false;
  }
}