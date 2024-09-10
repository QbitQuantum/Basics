EppResponseDataCreateLaunchRegistration* EppResponseDataCreateLaunchRegistration::fromXML( const DOMNode& root )
{
	EppResponseDataCreateLaunchRegistration *cmd  = new EppResponseDataCreateLaunchRegistration();
	if( cmd == null )
	{
		return null;
	}
	DOMNodeList* list  = root.getChildNodes();
	for( unsigned int i = 0; i < list->getLength(); i++ )
	{
		DOMNode* node  = list->item(i);
		DOMString name = node->getLocalName();

		if( name.isNull() )
		{
			name = node->getNodeName();
		}
		if( name.isNull() )
		{
			continue;
		}
		if( (name.length() > 7) && name.substringData(0, 7).equals("launch:") )
		{
			name = name.substringData(7, name.length() - 7);
		}
		if( name.equals("phase") )
		{
			EppLaunchPhase *_pptr = EppLaunchPhase::fromXML(*node);
			if( null != _pptr )
			{
				cmd->_phase = *_pptr;
				delete _pptr;
			}
			_pptr = null;
		}
		else if( name.equals("applicationID") )
		{
			cmd->_appId = EppUtil::getText(*node);
		}
	}
	return cmd;
}