char
GDBRemoteCommunication::GetAck ()
{
    StringExtractorGDBRemote packet;
    if (WaitForPacketWithTimeoutMicroSecondsNoLock (packet, GetPacketTimeoutInMicroSeconds ()) == 1)
        return packet.GetChar();
    return 0;
}