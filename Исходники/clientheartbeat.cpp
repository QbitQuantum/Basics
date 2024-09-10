 void sendHeartbeat(hrc::time_point& lastSendTime, SocketRouter& router, uint msFrequency)
 {
   auto currentTime = hrc::now();
   auto timeSinceLastHb = std::chrono::duration_cast < std::chrono::milliseconds > (currentTime - lastSendTime);
   if (timeSinceLastHb >= std::chrono::milliseconds(msFrequency))
   {
     VLOG(4) << "Sending heartbeat...";
     router.send(SocketID::HEARTBEAT, Message(stateline::comms::HEARTBEAT));
     lastSendTime = hrc::now();
   }
 }