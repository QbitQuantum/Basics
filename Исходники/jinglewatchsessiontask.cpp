//NOTE: This task watch for pre-JEP session.
bool JingleWatchSessionTask::take(const QDomElement &element)
{
	if(element.tagName() != "iq")
		return false;
	
	QString sessionType, initiator;
	
	QDomElement first = element.firstChild().toElement();
	if( !first.isNull() && first.attribute("xmlns") == JINGLE_NS && first.tagName() == "session" ) 
	{
		kdDebug(JABBER_DEBUG_GLOBAL) << k_funcinfo << "Checking for incoming sesssion." << endl;
		initiator = first.attribute("initiator");
	
		// Only proceed initiate type Jingle XMPP call.
		if( first.attribute("type") != QString::fromUtf8("initiate") )
			return false;
		
		int nodeIndex;

		QDomNodeList nodeList = first.childNodes();
		// Do not check first child
		for(nodeIndex = 0; nodeIndex < nodeList.length(); nodeIndex++)
		{
			QDomElement nodeElement = nodeList.item(nodeIndex).toElement();
			if(nodeElement.tagName() == "description")
			{
				sessionType = nodeElement.attribute("xmlns");
			}
		}

		if( !initiator.isEmpty() && !sessionType.isEmpty() )
		{
			kdDebug(JABBER_DEBUG_GLOBAL) << k_funcinfo << "Emmiting incoming sesssion." << endl;
			emit watchSession(sessionType, initiator);
			return true;
		}
	}
	
	return false;
}