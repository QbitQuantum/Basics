void XDebugComThread::DoSendCommand(const wxString& command, clSocketBase::Ptr_t client)
{
    // got message, process it
    if(!client) {
        return;
    }
    CL_DEBUGS(wxString() << "CodeLite >>> " << command);

    wxMemoryBuffer buff;
    buff.AppendData(command.mb_str(wxConvISO8859_1), command.length());
    buff.AppendByte(0);
    std::string cmd((const char*)buff.GetData(), buff.GetDataLen());
    client->Send(cmd);
}