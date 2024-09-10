std::string VCardSerializer::serializePayload(boost::shared_ptr<VCard> vcard)  const {
	XMLElement queryElement("vCard", "vcard-temp");
	if (!vcard->getVersion().empty()) {
		boost::shared_ptr<XMLElement> versionElement(new XMLElement("VERSION"));
		versionElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(vcard->getVersion())));
		queryElement.addNode(versionElement);
	}
	if (!vcard->getFullName().empty()) {
		boost::shared_ptr<XMLElement> fullNameElement(new XMLElement("FN"));
		fullNameElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(vcard->getFullName())));
		queryElement.addNode(fullNameElement);
	}
	if (!vcard->getGivenName().empty() || !vcard->getFamilyName().empty() || !vcard->getMiddleName().empty() || !vcard->getPrefix().empty() || !vcard->getSuffix().empty()) {
		boost::shared_ptr<XMLElement> nameElement(new XMLElement("N"));
		if (!vcard->getFamilyName().empty()) {
			boost::shared_ptr<XMLElement> familyNameElement(new XMLElement("FAMILY"));
			familyNameElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(vcard->getFamilyName())));
			nameElement->addNode(familyNameElement);
		}
		if (!vcard->getGivenName().empty()) {
			boost::shared_ptr<XMLElement> givenNameElement(new XMLElement("GIVEN"));
			givenNameElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(vcard->getGivenName())));
			nameElement->addNode(givenNameElement);
		}
		if (!vcard->getMiddleName().empty()) {
			boost::shared_ptr<XMLElement> middleNameElement(new XMLElement("MIDDLE"));
			middleNameElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(vcard->getMiddleName())));
			nameElement->addNode(middleNameElement);
		}
		if (!vcard->getPrefix().empty()) {
			boost::shared_ptr<XMLElement> prefixElement(new XMLElement("PREFIX"));
			prefixElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(vcard->getPrefix())));
			nameElement->addNode(prefixElement);
		}
		if (!vcard->getSuffix().empty()) {
			boost::shared_ptr<XMLElement> suffixElement(new XMLElement("SUFFIX"));
			suffixElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(vcard->getSuffix())));
			nameElement->addNode(suffixElement);
		}
		queryElement.addNode(nameElement);
	}
	foreach(const VCard::EMailAddress& emailAddress, vcard->getEMailAddresses()) {
		boost::shared_ptr<XMLElement> emailElement(new XMLElement("EMAIL"));
		boost::shared_ptr<XMLElement> userIDElement(new XMLElement("USERID"));
		userIDElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(emailAddress.address)));
		emailElement->addNode(userIDElement);
		if (emailAddress.isHome) {
			emailElement->addNode(boost::shared_ptr<XMLElement>(new XMLElement("HOME")));
		}
		if (emailAddress.isWork) {
			emailElement->addNode(boost::shared_ptr<XMLElement>(new XMLElement("WORK")));
		}
		if (emailAddress.isInternet) {
			emailElement->addNode(boost::shared_ptr<XMLElement>(new XMLElement("INTERNET")));
		}
		if (emailAddress.isPreferred) {
			emailElement->addNode(boost::shared_ptr<XMLElement>(new XMLElement("PREF")));
		}
		if (emailAddress.isX400) {
			emailElement->addNode(boost::shared_ptr<XMLElement>(new XMLElement("X400")));
		}
		queryElement.addNode(emailElement);
	}
	if (!vcard->getNickname().empty()) {
		boost::shared_ptr<XMLElement> nickElement(new XMLElement("NICKNAME"));
		nickElement->addNode(boost::shared_ptr<XMLTextNode>(new XMLTextNode(vcard->getNickname())));
		queryElement.addNode(nickElement);
	}
	if (!vcard->getPhoto().isEmpty() || !vcard->getPhotoType().empty()) {
		XMLElement::ref photoElement(new XMLElement("PHOTO"));
		if (!vcard->getPhotoType().empty()) {
			XMLElement::ref typeElement(new XMLElement("TYPE"));
			typeElement->addNode(XMLTextNode::ref(new XMLTextNode(vcard->getPhotoType())));
			photoElement->addNode(typeElement);
		}
		if (!vcard->getPhoto().isEmpty()) {
			XMLElement::ref binvalElement(new XMLElement("BINVAL"));
			binvalElement->addNode(XMLTextNode::ref(new XMLTextNode(Base64::encode(vcard->getPhoto()))));
			photoElement->addNode(binvalElement);
		}
		queryElement.addNode(photoElement);
	}
	if (!vcard->getUnknownContent().empty()) {
		queryElement.addNode(boost::shared_ptr<XMLRawTextNode>(new XMLRawTextNode(vcard->getUnknownContent())));
	}
	return queryElement.serialize();
}