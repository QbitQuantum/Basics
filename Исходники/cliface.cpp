    void send_uo_skill( Client* client, Mobile::Character* me, const Mobile::Attribute* attr )
	{
	  ClientAttributeUpdaters& cau = client->Interface.attribute_updaters[attr->attrid];

	  PktHelper::PacketOut<PktOut_3A> msg;
	  msg->offset += 2;
	  if ( !Core::ssopt.core_sends_caps )
		msg->Write<u8>( static_cast<u8>( Core::PKTBI_3A_VALUES::SINGLE_SKILL ) );
	  else
		msg->Write<u8>( static_cast<u8>( Core::PKTBI_3A_VALUES::SINGLE_SKILL_CAP ) );
	  msg->WriteFlipped<u16>( static_cast<u16>( cau.pUOSkill->skillid ) );
      const Mobile::AttributeValue& av = me->attribute( attr->attrid );
	  msg->WriteFlipped<u16>( static_cast<u16>( av.effective_tenths() ) ); //value
	  msg->WriteFlipped<u16>( static_cast<u16>( av.base() ) ); //value_unmod base is always in tenths...
	  msg->Write<u8>( static_cast<u8>( av.lock() ) );
	  if ( Core::ssopt.core_sends_caps )
		msg->WriteFlipped<u16>( static_cast<u16>( av.cap() ) );
	  u16 len = msg->offset;
	  msg->offset = 1;
	  msg->WriteFlipped<u16>( len );
	  msg.Send( client, len );
	}