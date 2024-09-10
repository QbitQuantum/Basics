std::string StorageClient::startClient()
{

    Client* client = new Client(_ip, _port);
    client->Connect();

    std::string message = std::string("startClient");

    client->sendMessage(message);
    std::string messagea = client->readMessage();
    _sessionID = std::stoi(messagea);
    client->sendMessage("disconnect");
    delete client;
    return messagea;
}