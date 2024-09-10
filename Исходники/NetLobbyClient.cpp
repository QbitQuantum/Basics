void
NetLobbyClient::DoAuthUser(NetPeer* peer, Text msg)
{
    List<NetLobbyParam> params;
    ParseMsg(msg, params);

    int  level = NetAuth::NET_AUTH_STANDARD;
    Text salt;

    for (int i = 0; i < params.size(); i++) {
        NetLobbyParam* p = params[i];

        int num = 0;
        sscanf_s(p->value, "%d", &num);

        if (p->name == "level") {
            level = num;
        }

        else if (p->name == "salt") {
            salt = p->value;
        }
    }

    Text response = NetAuth::CreateAuthResponse(level, salt);
    if (response.length() > 0)
    SendData(NET_LOBBY_USER_AUTH, response);
}