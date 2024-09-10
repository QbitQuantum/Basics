bool CTcpSocketService::GetPeerData(std::string& Ip, UINT& Port)
{
    bool Success = (GetPeerName(Ip, (int&)Port) != FALSE);

    if(!Success)
        DisplaySocketsError("CTcpSocketService::GetPeerName");
    return Success;
}