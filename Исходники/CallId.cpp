void CallId::getNewCallId(const char* callIdPrefix,
                          UtlString& callId)
{
   // Lock to protect common variables.
   OsLock lock(sCallIdMutex);

   // Increment the call number.
   sCallNum += 1;
    
   // callID prefix shouldn't contain an @.
   if (strchr(callIdPrefix, '@') != NULL)
   {
      OsSysLog::add(FAC_SIP, PRI_ERR,
                    "CallId::getNewCallId callIdPrefix='%s' contains '@'",
                    callIdPrefix);
   }

   // Compute the next value.
   nextValue("");

   // Compose the new Call-Id.
   char buffer[256];
   sprintf(buffer, "%s-%.*s-%d",
           callIdPrefix, 
           CALL_ID_CHAIN_VALUE_REVEALED, sChainValue.data(),
           sCallNum);

   // Copy it to the destination.
   callId.remove(0);
   callId.append(buffer);
}