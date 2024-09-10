EppMarkMark* EppMarkMark::fromXML( const DOMNode& root, const char* ns)
{
	EppMarkMark *_ret    = new EppMarkMark(ns);
	DOMNodeList* list    = root.getChildNodes();

	int nsLen      = strlen(ns);

	if( list == 0 )
	{
		delete _ret;
		return NULL;
	}

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
		if( name.substringData(0, nsLen + 1).equals((_ret->getNameSpace() + ":").c_str()) )
		{
			name = name.substringData(nsLen + 1, name.length() - ( nsLen + 1 ));
		}
		if( name.equals("trademark") )
		{
			EppTrademarkData *_tmd = EppTrademarkData::fromXML(*node, ns);
			if( NULL != _tmd )
			{
				_ret->_marks.addElement(_tmd);
			}
		}
		else if ( name.equals("court") )
		{
			EppCourtData *_cd = EppCourtData::fromXML(*node, ns);
			if( NULL != _cd )
			{
				_ret->_marks.addElement(_cd);
			}
		}
		else if ( name.equals("treatyOrStatute") )
		{
			EppTreatyOrStatuteData *_tsd = EppTreatyOrStatuteData::fromXML(*node, ns);
			if( NULL != _tsd )
			{
				_ret->_marks.addElement(_tsd );
			}
		}

	}
	return _ret;
}