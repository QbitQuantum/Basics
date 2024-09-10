int sendExecuteAck(int sockfd, struct sockaddr_in sockaddr, Packet *packet){
   Packet *packet_reply;
   packet_reply = (Packet *)malloc(sizeof(Packet)); //Packet with Execute_Serv type Data

   packet_reply = genExecuteAck(packet); // msg to be sent back
   return Sendto(sockfd, packet_reply, sizeof(Packet), MSG_NOSIGNAL, sockaddr, sizeof(sockaddr));
}