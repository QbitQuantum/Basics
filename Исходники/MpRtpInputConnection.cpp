OsStatus MpRtpInputConnection::enableSsrcDiscard(const UtlString& namedResource,
                                                 OsMsgQ& fgQ,
                                                 UtlBoolean enable, RtpSRC ssrc)
{
   MpIntResourceMsg msg(enable?(MpResourceMsg::MpResourceMsgType)MPRM_ENABLE_SSRC_DISCARD
                              :(MpResourceMsg::MpResourceMsgType)MPRM_DISABLE_SSRC_DISCARD,
                        namedResource, ssrc);
   return fgQ.send(msg, sOperationQueueTimeout);
}