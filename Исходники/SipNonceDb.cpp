UtlBoolean SipNonceDb::isNonceValid(const UtlString& nonce,
                                    const UtlString& callId,
                                    const UtlString& fromTag,
                                    const UtlString& realm,
                                    const long expiredTime)
{
   UtlBoolean valid = FALSE;

   if (nonce.length() == (MD5_SIZE + HEX_TIMESTAMP_LENGTH))
   {
      UtlString timestamp = nonce(MD5_SIZE, HEX_TIMESTAMP_LENGTH);
      UtlString rcvdSignature = nonce(0,MD5_SIZE);
      UtlString msgSignature(nonceSignature(callId, fromTag, realm, timestamp.data()));
      if (0 == rcvdSignature.compareTo(msgSignature))
      {
         // check for expiration
         char* end;
         long nonceCreated = strtol(timestamp.data(), &end, 16 /* hex */);
         long now = OsDateTime::getSecsSinceEpoch();

         if ( nonceCreated+expiredTime >= now )
         {
            valid = TRUE;
         }
         else
         {
            OsSysLog::add(FAC_SIP,PRI_INFO,
                          "SipNonceDB::isNonceValid expired nonce '%s': created %ld+%ld < %ld",
                          nonce.data(), nonceCreated, expiredTime, now
                          );
         }
      }
      else
      {
         OsSysLog::add(FAC_SIP,PRI_ERR,
                       "SipNonceDB::isNonceValid nonce signature check failed '%s'",
                       nonce.data()
                       );
         OsSysLog::add(FAC_SIP,PRI_DEBUG,
                       "SipNonceDB::isNonceValid rcvd signature '%s' calculated signature '%s'",
                       rcvdSignature.data(), msgSignature.data()
                       );
      }
   }
   else
   {
      OsSysLog::add(FAC_SIP,PRI_ERR,
                    "SipNonceDb::isNonceValid invalid nonce format '%s'"
                    " length %zu expected %d",
                    nonce.data(), nonce.length(), MD5_SIZE+HEX_TIMESTAMP_LENGTH);
   }

   return(valid);
}