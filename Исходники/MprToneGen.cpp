// Sends an MPRM_STOP_TONE message to the named MprToneGen resource.
// When received, the resource stops generating a tone.
// Returns the result of attempting to queue the message to this resource.
OsStatus MprToneGen::stopTone(const UtlString& namedResource,
                              OsMsgQ& fgQ)
{
   MpResourceMsg msg(MpResourceMsg::MPRM_STOP_TONE, namedResource);
   return fgQ.send(msg, sOperationQueueTimeout);
}