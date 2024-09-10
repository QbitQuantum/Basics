OsStatus MpRtpInputAudioConnection::startReceiveRtp(OsMsgQ& messageQueue,
                                                    const UtlString& resourceName,
                                                    const SdpCodecList& sdpCodecList,
                                                    OsSocket& rRtpSocket,
                                                    OsSocket& rRtcpSocket)
{
    OsStatus result = OS_INVALID_ARGUMENT;
    if(sdpCodecList.getCodecCount() > 0)
    {
        // Create a message to contain the startRecieveRtp data
        MprRtpStartReceiveMsg msg(resourceName,
                                  sdpCodecList,
                                  rRtpSocket,
                                  rRtcpSocket);

        // Send the message in the queue.
        result = messageQueue.send(msg);
    }
    return(result);
}