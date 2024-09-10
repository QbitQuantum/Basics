EppContact * EppContact::fromXML( const DOM_Node& root )
{
	EppContact * contact = new EppContact();
	DOM_NodeList list = root.getChildNodes();
	for( unsigned int i = 0; i < list.getLength(); i++ )
	{
		DOM_Node node = list.item(i);
		DOMString name = node.getLocalName();
		if( name == null )
		{
			name = node.getNodeName();
		}
		if( name == null )
		{
			continue;
		}
		if( name.substringData(0, 8).equals("contact:") )
		{
			name = name.substringData(8, name.length() - 8);
		}
		if( name.equals("id") )
		{
			contact->id = EppUtil::getText(node);
		}
		else if( name.equals("ascii") )
		{
			contact->ascii = EppContactData::fromXML(node);
		}
		else if( name.equals("i15d") )
		{
			contact->i15d = EppContactData::fromXML(node);
		}
		else if( name.equals("voice") )
		{
			contact->voice = EppE164::fromXML(node);
		}
		else if( name.equals("fax") )
		{
			contact->fax = EppE164::fromXML(node);
		}
		else if( name.equals("email") )
		{
			contact->email = EppUtil::getText(node);
		}
		else
		{
			contact->fromXMLCommon(node, name);
		}
	}

	return contact;
}