void send_skillmsg( Network::Client* client, const Mobile::Character* chr )
{
  Network::PktHelper::PacketOut<Network::PktOut_3A> msg;
  msg->offset += 2;
  if ( settingsManager.ssopt.core_sends_caps )
    msg->Write<u8>( PKTBI_3A_VALUES::FULL_LIST_CAP );
  else
    msg->Write<u8>( PKTBI_3A_VALUES::FULL_LIST );

  for ( unsigned short i = 0; i <= networkManager.uoclient_general.maxskills; ++i )
  {
    const UOSkill& uoskill = GetUOSkill( i );
    msg->WriteFlipped<u16>( static_cast<u16>( i + 1 ) );  // for some reason, we send this 1-based
    if ( uoskill.pAttr )
    {
      const Mobile::AttributeValue& av = chr->attribute( uoskill.pAttr->attrid );
      int value;
      value = av.effective_tenths();
      if ( value > 0xFFFF )
        value = 0xFFFF;
      msg->WriteFlipped<u16>( static_cast<u16>( value ) );

      value = av.base();
      if ( value > 0xFFFF )
        value = 0xFFFF;
      msg->WriteFlipped<u16>( static_cast<u16>( value ) );
      msg->Write<u8>( av.lock() );
      if ( settingsManager.ssopt.core_sends_caps )
        msg->WriteFlipped<u16>( av.cap() );
    }
    else
    {
      msg->offset += 4;  // u16 value/value_unmod
      msg->Write<u8>( PKTBI_3A_VALUES::LOCK_DOWN );
      if ( settingsManager.ssopt.core_sends_caps )
        msg->WriteFlipped<u16>( settingsManager.ssopt.default_attribute_cap );
    }
  }
  if ( !settingsManager.ssopt.core_sends_caps )
    msg->offset += 2;  // u16 nullterm
  u16 len = msg->offset;
  msg->offset = 1;
  msg->WriteFlipped<u16>( len );
  msg.Send( client, len );
}