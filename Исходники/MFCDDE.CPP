CDDEConnection *CDDEClient::MakeConnection(const CString& /* host */, const CString& server_name, const CString& topic)
{
    HSZ serviceName = DdeCreateStringHandle(DDEIdInst, (const char *)server_name, CP_WINANSI);
    HSZ topic_atom = DdeCreateStringHandle(DDEIdInst, (const char *)topic, CP_WINANSI);

    HCONV hConv = DdeConnect(DDEIdInst, serviceName, topic_atom, (PCONVCONTEXT)NULL);
    BOOL rt = DdeFreeStringHandle(DDEIdInst, serviceName);
    rt = DdeFreeStringHandle(DDEIdInst, topic_atom);
    if (hConv == NULL)
        return NULL;
    else
    {
        CDDEConnection *connection = OnMakeConnection();
        if (connection)
        {
            connection->hConv = hConv;
            connection->topic_name = topic;
            connection->client = this;
            connections.AddTail(connection);
//	  bDisconnected = true;
            return connection;
        }
        else return NULL;
    }
}