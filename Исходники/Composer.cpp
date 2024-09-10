bool ewol::widget::Composer::loadFromString(const std::string& _composerXmlString) {
	exml::Document doc;
	if (doc.parse(_composerXmlString) == false) {
		EWOL_ERROR(" can not load file XML string...");
		return false;
	}
	exml::Element* root = (exml::Element*)doc.getNamed("composer");
	if (root == nullptr) {
		// Maybe a multiple node XML for internal config:
		root = doc.toElement();
		if (root == nullptr) {
			EWOL_ERROR("[" << getId() << "] {" << getObjectType() << "} (l ?) main node not find: \"composer\" ...");
			return false;
		}
		if (root->size() == 0) {
			EWOL_ERROR("[" << getId() << "] {" << getObjectType() << "} (l ?) no node in the Container XML element.");
			return false;
		}
	}
	// call upper class to parse his elements ...
	ewol::widget::Container::loadXML(root);
	requestUpdateSize();
	return true;
}