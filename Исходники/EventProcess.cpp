bool EventProcess::InitTimingWheelTimer() {
    MsgNode* msgNode = new MsgNode;
    msgNode->SetTimer(10, 0);
    msgNode->SetObjectPoint(this);
    tcpEventServer_.AddTimerEvent(TimingWheelOnTime, msgNode, false);
}