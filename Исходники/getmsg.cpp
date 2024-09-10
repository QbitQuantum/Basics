void send_prompt( Network::Client* client, u32 serial )
{
  Network::PktHelper::PacketOut<Network::PktOut_9A> msg;
  msg->WriteFlipped<u16>( sizeof msg->buffer );
  msg->Write<u32>( serial );
  msg->WriteFlipped<u32>( 0x15u );
  msg->offset += 5;  // u32 type u8 text[0]
  msg.Send( client );
}