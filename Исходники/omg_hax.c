void generate_session_key(unsigned char* oldSap, unsigned char* messageIn, unsigned char* sessionKey)
{
   unsigned char decryptedMessage[128];
   unsigned char newSap[320];
   unsigned char Q[210];
   int i;
   int round;
   unsigned char md5[16];
   unsigned char otherHash[16];

   decryptMessage(messageIn, decryptedMessage);
   // Now that we have the decrypted message, we can combine it with our initial sap to form the 5 blocks needed to generate the 5 words which, when added together, give
   // the session key.
   memcpy(&newSap[0x000], static_source_1, 0x11);
   memcpy(&newSap[0x011], decryptedMessage, 0x80);
   memcpy(&newSap[0x091], &oldSap[0x80], 0x80);
   memcpy(&newSap[0x111], static_source_2, 0x2f);
   memcpy(sessionKey, initial_session_key, 16);

   for (round = 0; round < 5; round++)
   {
      unsigned char* base = &newSap[round * 64];
      print_block("Input block: ", &base[0]);
      print_block("Input block: ", &base[0x10]);
      print_block("Input block: ", &base[0x20]);
      print_block("Input block: ", &base[0x30]);
      modified_md5(base, sessionKey, md5);
      printf("MD5 OK\n");
      sap_hash(base, sessionKey);
      printf("OtherHash OK\n");
      
      printf("MD5       = ");
      for (i = 0; i < 4; i++)
         printf("%08x ", ((uint32_t*)md5)[i]);
      printf("\nOtherHash = ");
      for (i = 0; i < 4; i++)
        printf("%08x ", ((uint32_t*)sessionKey)[i]);
      printf("\n");

      uint32_t* sessionKeyWords = (uint32_t*)sessionKey;
      uint32_t* md5Words = (uint32_t*)md5;
      for (i = 0; i < 4; i++)
      {
         sessionKeyWords[i] = (sessionKeyWords[i] + md5Words[i]) & 0xffffffff;
      }      
      printf("Current key: ");
      for (i = 0; i < 16; i++)
         printf("%02x", sessionKey[i]);
      printf("\n");
   }
   for (i = 0; i < 16; i+=4)
   {
      swap_bytes(&sessionKey[i], &sessionKey[i+3]);
      swap_bytes(&sessionKey[i+1], &sessionKey[i+2]);
   }
      
   // Finally the whole thing is XORd with 121:
   for (i = 0; i < 16; i++)
     sessionKey[i] ^= 121;
   print_block("Session key computed as: ", sessionKey);
}