void send_paperdoll( Network::Client* client, Mobile::Character* chr )
{
  Network::PktHelper::PacketOut<Network::PktOut_88> msg;
  msg->Write<u32>( chr->serial_ext );

  if ( ( !settingsManager.ssopt.privacy_paperdoll ) || ( client->chr == chr ) )
  {
    std::string name = ( !chr->has_title_prefix() ? "" : chr->title_prefix() + " " ) + chr->name() +
                       ( !chr->has_title_suffix() ? "" : " " + chr->title_suffix() );
    if ( chr->has_title_race() )
      name += " (" + chr->title_race() + ")";
    msg->Write( name.c_str(), 60 );
  }
  else
    msg->Write( chr->name().c_str(), 60 );


  // MuadDib changed to reflect true status for 0x20 packet. 1/4/2007
  // Paperdoll Appears different type Status byte than other walk/update
  // packets. Using poison/hidden here will break peace/war button.
  u8 flag1 = chr->warmode() ? 1 : 0;
  if ( client->UOExpansionFlag & Network::AOS && client->chr->serial_ext == chr->serial_ext )
    flag1 |= CHAR_FLAG1_CANALTER;
  msg->Write<u8>( flag1 );

  msg.Send( client );
}