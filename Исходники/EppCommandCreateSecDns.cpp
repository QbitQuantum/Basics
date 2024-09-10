EppCommandCreateSecDns* EppCommandCreateSecDns::fromXML( const DOMNode &root )
{
	EppCommandCreateSecDns * cmd  = new EppCommandCreateSecDns();
	if( cmd == null )
	{
		return null;
	}

	DOMNodeList* list  = root.getChildNodes();
	for( unsigned int i = 0; i < list->getLength(); i++ )
	{
		DOMNode* node = list->item(i);
		DOMString name = node->getLocalName();

		if( name.isNull() )
		{
			name = node->getNodeName();
		}
		if( name.isNull() )
		{
			continue;
		}
		if( name.substringData(0, 7).equals("secDNS:") )
		{
			name = name.substringData(7, name.length() - 7);
		}
		if( name.equals("dsData") )
		{
			EppSecDnsDsData * ds = EppSecDnsDsData::fromXML(*node);
			if( ds != null )
			{
				cmd->add(*ds);
				delete ds;
			}
		}
		else if( name.equals("maxSigLife") )
		{
			DOMString value = EppUtil::getText(*node);
			char *p = value.transcode();
			if( p != null )
			{
				cmd->maxSigLife = ::atoi(p);
				XercesString::Delete(p);
			}
		}
		else if( name.equals("keyData") )
		{
			// FIXME(zhang) not supported
			cmd->keyDataPresent = true;
			EppSecDnsKeyData *kd = EppSecDnsKeyData::fromXML(*node);
			if( kd != null )
			{
				cmd->add(*kd);
				delete kd;
			}
		}
	}
	return cmd;
}