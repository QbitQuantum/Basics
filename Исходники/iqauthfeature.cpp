bool IqAuthFeature::xmppStanzaIn(IXmppStream *AXmppStream, Stanza &AStanza, int AOrder)
{
	if (AXmppStream==FXmppStream && AOrder==XSHO_XMPP_FEATURE)
	{
		if (AStanza.id() == "getIqAuth")
		{
			if (AStanza.type() == "result")
			{
				Stanza auth("iq");
				auth.setType("set").setTo(FXmppStream->streamJid().domain()).setId("setIqAuth");
				QDomElement query = auth.addElement("query",NS_JABBER_IQ_AUTH);
				query.appendChild(auth.createElement("username")).appendChild(auth.createTextNode(FXmppStream->streamJid().pNode()));
				query.appendChild(auth.createElement("resource")).appendChild(auth.createTextNode(FXmppStream->streamJid().resource()));

				QDomElement reqElem = AStanza.firstElement("query",NS_JABBER_IQ_AUTH);
				if (!reqElem.firstChildElement("digest").isNull())
				{
					QByteArray shaData = FXmppStream->streamId().toUtf8()+FXmppStream->password().toUtf8();
					QByteArray shaDigest = QCryptographicHash::hash(shaData,QCryptographicHash::Sha1).toHex();
					query.appendChild(auth.createElement("digest")).appendChild(auth.createTextNode(shaDigest.toLower().trimmed()));
					FXmppStream->sendStanza(auth);
					LOG_STRM_INFO(AXmppStream->streamJid(),"Username and encrypted password sent");
				}
				else if (!reqElem.firstChildElement("password").isNull())
				{
					if (FXmppStream->connection()->isEncrypted())
					{
						query.appendChild(auth.createElement("password")).appendChild(auth.createTextNode(FXmppStream->password()));
						FXmppStream->sendStanza(auth);
						LOG_STRM_INFO(AXmppStream->streamJid(),"Username and plain text password sent");
					}
					else
					{
						LOG_STRM_ERROR(AXmppStream->streamJid(),"Failed to send username and plain text password: Connection not encrypted");
						emit error(XmppError(IERR_XMPPSTREAM_NOT_SECURE));
					}
				}
			}
			else
			{
				XmppStanzaError err(AStanza);
				LOG_STRM_ERROR(AXmppStream->streamJid(),QString("Failed to receive authentication initialization: %1").arg(err.condition()));
				emit error(err);
			}
			return true;
		}
		else if (AStanza.id() == "setIqAuth")
		{
			FXmppStream->removeXmppStanzaHandler(XSHO_XMPP_FEATURE,this);
			if (AStanza.type() == "result")
			{
				LOG_STRM_INFO(AXmppStream->streamJid(),"Username and password accepted");
				deleteLater();
				emit finished(false);
			}
			else
			{
				XmppStanzaError err(AStanza);
				LOG_STRM_WARNING(AXmppStream->streamJid(),QString("Username and password rejected: %1").arg(err.condition()));
				emit error(XmppStanzaError(AStanza));
			}
			return true;
		}
	}
	return false;
}