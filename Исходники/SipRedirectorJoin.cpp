RedirectPlugin::LookUpStatus
SipRedirectorJoin::lookUp(
   const SipMessage& message,
   const UtlString& requestString,
   const Url& requestUri,
   const UtlString& method,
   ContactList& contactList,
   RedirectPlugin::RequestSeqNo requestSeqNo,
   int redirectorNo,
   SipRedirectorPrivateStorage*& privateStorage,
   ErrorDescriptor& errorDescriptor)
{
   UtlString userId;
   UtlString incomingCallId;

   requestUri.getUserId(userId);
   message.getCallIdField(&incomingCallId);

   if (!mCallJoinCode.isNull() &&
       userId.length() > mCallJoinCode.length() &&
       userId.index(mCallJoinCode.data()) == 0 &&
       userId.compareTo(mExcludedUser1) != 0 &&
       userId.compareTo(mExcludedUser2) != 0)
   {
      return lookUpDialog(requestString,
                          incomingCallId,
                          contactList,
                          requestSeqNo,
                          redirectorNo,
                          privateStorage,
                          // The suffix of the request URI after the
                          // directed call pick-up code.
                          userId.data() + mCallJoinCode.length(),
                          // Only examine confirmed dialogs.
                          stateConfirmed);
   }
   else
   {
      // We do not recognize the user, so we do nothing.
      return RedirectPlugin::SUCCESS;
   }
}