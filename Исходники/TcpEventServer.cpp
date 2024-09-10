bool TcpEventServer::SendHeartBeatMsg(int iSecond, const std::string& strHeartBeatMsg) {
    MsgNode* HeartBeatTimer = new MsgNode;
    HeartBeatTimer->SetTimer(iSecond, 0);
    HeartBeatTimer->SetObjectPoint(this);
    HeartBeatTimer->SetMsg(strHeartBeatMsg);
    AddTimerEvent(heartBeatTimeCb, HeartBeatTimer, false);
}