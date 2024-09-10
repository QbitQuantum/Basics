void AudioStreamingServer::SendResponseHeader(const std::shared_ptr<ISocket>& clientSocket, const HttpResponse& response) const {
    std::string header = response.GenerateHeader();
    clientSocket->Send(header.c_str(), header.length());
}