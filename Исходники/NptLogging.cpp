/*----------------------------------------------------------------------
|   NPT_LogUdpHandler::Log
+---------------------------------------------------------------------*/
void
NPT_LogUdpHandler::Log(const NPT_LogRecord& record)
{
    // format the record
    NPT_String msg;
    NPT_LogTcpHandler::FormatRecord(record, msg);
    
    // send it in a datagram
    NPT_DataBuffer buffer(msg.GetChars(), msg.GetLength()+1, false);
    m_Socket.Send(buffer, &m_Target);
}