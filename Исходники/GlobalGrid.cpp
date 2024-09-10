  void NtfyPacket(std::shared_ptr<GlobalGrid::VSocket> socket,unsigned char* packetData, size_t packetLength) {
    
    if(sessions.find(socket) == sessions.end()) {
      //We should have an AES key in our packet here encrypted with our public key.
      
      
      //Packet header -- thumbprint (16 bytes) (unverified data element), session key (variable length, encrypted)
      if(packetLength<=16) {
	return;
      }
      void* packet = RSA_Decrypt(privkey,packetData+16,packetLength-16);
      if(packet == 0) { //Decryption failure.
	return;
      }
      unsigned char* buffer;
      size_t sz;
      GlobalGrid::Buffer_Get(packet,&buffer,&sz);
      if(sz>=32) {
	//We have a new Session.
	Session route(socket,buffer,packetData);
	sessions.insert(route);
	//Respond with ACK, which verifies our identity
	//Send challenge to verify remote identity.
	
	char hexprint[33];
	ToHexString((unsigned char*)route.claimedThumbprint,16,hexprint);
	hexprint[32] = 0;
	
	void* remoteKey = DB_FindAuthority(hexprint);
	
	if(remoteKey) {
	  SendChallenge(remoteKey,route,socket);
	}else {
	  //We don't have a remote key. Request it.
	  unsigned char izard[16];
	  memset(izard,0,16);
	  izard[0] = 2;
	  aes_encrypt(route.key,izard);
	  socket->Send(izard,16);
	}
	GlobalGrid::GGObject_Free(packet);
      }else {
	GlobalGrid::GGObject_Free(packet);
      }
    }else {
      //Bind to existing Session.
      if(packetLength % 16 != 0) {
	//Invalid packet.
	return;
      }
      
      Session session = *sessions.find(socket);
      for(size_t i = 0;i<packetLength;i+=16) {
	aes_decrypt(session.key,packetData+i);
      }
      
      switch(*packetData) {
	case 0:
	  //Challenge request
	{
	  //Decrypt challenge
	  uint16_t len;
	  memcpy(&len,packetData+1,2);
	  void* challenge = RSA_Decrypt(privkey,packetData+1+2,len);
	  if(challenge == 0) {
	    return;
	  }
	  unsigned char* challenge_bytes;
	  size_t challenge_sz;
	  
	  GlobalGrid::Buffer_Get(challenge,&challenge_bytes,&challenge_sz);
	  if(challenge_sz != 16) {
	    GlobalGrid::GGObject_Free(challenge);
	    return;
	  }
	  
	  unsigned char response[32];
	  memset(response,0,32);
	  response[0] = 1;
	  memcpy(response+1,challenge_bytes,16);
	  aes_encrypt(session.key,response);
	  aes_encrypt(session.key,response+16);
	  socket->Send(response,32);
	  GlobalGrid::GGObject_Free(challenge);
	  
	  
	}
	  break;
	case 1:
	{
	  //Response to challenge (identity verification)
	  if(memcmp(session.challenge,packetData+1,16) == 0) {
	    session.verified = true;
	    printf("Identity verified.\n");
	  }
	}
	  break;
	case 2:
	{
	  //Request for public encryptionKey.
	  void* key = RSA_Export(privkey,false);
	  unsigned char* key_bytes;
	  size_t key_size;
	  GlobalGrid::Buffer_Get(key,&key_bytes,&key_size);
	  size_t aligned = key_size+1;
	  aligned+=16-(aligned % 16);
	  
	  unsigned char* packet = new unsigned char[aligned];
	  memcpy(packet+1,key_bytes,key_size);
	  packet[0] = 3;
	  
	  for(size_t i = 0;i<aligned;i+=16) {
	    aes_encrypt(session.key,packet+i);
	  }
	  
	  socket->Send(packet,aligned);
	  delete[] packet;
	  GlobalGrid::GGObject_Free(key);
	  
	}
	  break;
	case 3:
	{
	  //Received public encryption key
	  void* key = RSA_Key(packetData+1,packetLength-1);
	  char thumbprint[33];
	  RSA_thumbprint(key,thumbprint);
	  thumbprint[32] = 0;
	  void* obj = DB_FindAuthority(thumbprint);
	  if(obj == 0) {
	    void* keybin = RSA_Export(key,false);
	    unsigned char* cert;
	    size_t cert_len;
	    GlobalGrid::Buffer_Get(keybin,&cert,&cert_len);
	    DB_Insert_Certificate(thumbprint,cert,cert_len,false);
	    GlobalGrid::GGObject_Free(keybin);
	    if(session.verified == false) {
	      //TODO: Send verification request
	      SendChallenge(key,session,socket);
	    }
	  }else {
	    RSA_Free(obj);
	  }
	}
	  break;
	case 4:
	{
	  //Route packet
	  packetData++;
	  unsigned char ttl = *packetData;
	  packetData++;
	  
	  //Intended destination
	  GlobalGrid::Guid dest;
	  memcpy(dest.value,packetData,16);
	  packetData+=16;
	  GlobalGrid::Guid localThumbprint;
	  RSA_thumbprint(privkey,(unsigned char*)localThumbprint.value);
	  uint32_t packetSize;
	  memcpy(&packetSize,packetData,4);
	  packetData+=16;
	  if(dest == localGuid) {
	    printf("TODO: Packet destined for ourselves\n");
	    return;
	  }
	  SendPacket(packetData,packetSize,ttl,dest,session.claimedThumbprint);
	  
	}
	  break;
      }
    }
  }