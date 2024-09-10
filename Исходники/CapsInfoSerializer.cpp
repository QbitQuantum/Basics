std::string CapsInfoSerializer::serializePayload(boost::shared_ptr<CapsInfo> capsInfo)  const {
	XMLElement capsElement("c", "http://jabber.org/protocol/caps");
	capsElement.setAttribute("node", capsInfo->getNode());
	capsElement.setAttribute("hash", capsInfo->getHash());
	capsElement.setAttribute("ver", capsInfo->getVersion());
	return capsElement.serialize();
}