QTreeWidgetItem* BtBookmarkLoader::handleXmlElement(QDomElement& element, QTreeWidgetItem* parent)
{
	qDebug() << "BtBookmarkLoader::handleXmlElement";
	QTreeWidgetItem* newItem = 0;
	if (element.tagName() == "Folder") {
		qDebug() << "BtBookmarkLoader::handleXmlElement: found folder";
		BtBookmarkFolder* newFolder = new BtBookmarkFolder(parent, QString());
		if (element.hasAttribute("caption")) {
			newFolder->setText(0, element.attribute("caption"));
		}
		QDomNodeList childList = element.childNodes();
		for (unsigned int i = 0; i < childList.length(); i++) {
			qDebug() << "BtBookmarkLoader::handleXmlElement: go through child list of folder";
			QDomElement newElement = childList.at(i).toElement();
			QTreeWidgetItem* newChildItem = handleXmlElement(newElement, newFolder);
			newFolder->addChild(newChildItem);
		}
		newFolder->update();
		newItem = newFolder;
	}
	else if (element.tagName() == "Bookmark") {
		qDebug() << "BtBookmarkLoader::handleXmlElement: found bookmark";
		BtBookmarkItem* newBookmarkItem = new BtBookmarkItem(parent);
		if (element.hasAttribute("modulename")) {
			//we use the name in all cases, even if the module isn't installed anymore
			newBookmarkItem->m_moduleName = element.attribute("modulename");
		}
		if (element.hasAttribute("key")) {
			newBookmarkItem->m_key = element.attribute("key");
		}
		if (element.hasAttribute("description")) {
			newBookmarkItem->m_description = element.attribute("description");
		}
		newBookmarkItem->update();
		newItem = newBookmarkItem;
	}
	qDebug() << "BtBookmarkLoader::handleXmlElement: return new item";
	return newItem;
}