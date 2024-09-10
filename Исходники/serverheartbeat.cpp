 void monitorTimeouts(HBClients& clients, HBMap& lastHeartbeats, SocketRouter& router, uint msTimeout)
 {
   for (auto addr : clients)
   {
     auto msElapsed = std::chrono::duration_cast < std::chrono::milliseconds > (hrc::now() - lastHeartbeats[addr]).count();
     if (msElapsed > msTimeout)
     {
       stateline::comms::Message gb( { addr }, stateline::comms::GOODBYE);
       VLOG(1) << "Heartbeat system sending GOODBYE on behalf of " << addr;
       router.send(SocketID::HEARTBEAT, Message( { addr }, stateline::comms::GOODBYE));
       clients.erase(clients.find(addr));
       lastHeartbeats.erase(addr);
     }
   }
 }