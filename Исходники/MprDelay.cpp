UtlBoolean MprDelay::stopPlay(const UtlString& namedResource, 
                              OsMsgQ& fgQ)
{
   MpResourceMsg msg((MpResourceMsg::MpResourceMsgType)MPRM_DELAY_STOP_PLAY, namedResource);
   return fgQ.send(msg);
}