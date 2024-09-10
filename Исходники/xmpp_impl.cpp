	//查找啊.
	BOOST_FOREACH(boost::shared_ptr<gloox::MUCRoom> room, m_rooms)
	{
		if ( room->name() == xmpproom ){
			room->send(message);
		}
	}	