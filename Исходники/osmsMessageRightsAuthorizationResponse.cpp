char* osmsMessageRightsAuthorizationResponse::encode()
{
	XMLDocument* pDoc = new XMLDocument();
	if (pDoc == NULL)
		return NULL;

	if (!pDoc->decode(xmlTemplate(), getName()))
	{
		delete pDoc;
		return NULL;
	}

	pDoc->setInteger("MessageType", getMessageType());
	pDoc->setString("TransactionId", getTransactionId());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}