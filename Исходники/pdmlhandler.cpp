bool PdmlHandler::startElement(const QString & /* namespaceURI */,
	const QString & /* localName */,
	const QString &qName,
	const QXmlAttributes &attributes)
{
    qDebug("%s (%s)", __FUNCTION__, qName.toAscii().constData());
    if (qName == "pdml") 
	{
		packetCount = 0;
	}
	else if (qName == "packet") 
	{
		currentItem = _model->item(packetCount, 0);
    }
	else if ((qName == "proto") || (qName == "field"))
	{
		QStandardItem *item;

		if (attributes.value("hide") == "yes")
		{
			skip = true;
		}
		else 
		{
			QString		val;
			val = attributes.value("showname");
			if (val.isEmpty())
				val = attributes.value("show");
			if (!val.isEmpty())
			{
				item = new QStandardItem(val);
				item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				currentItem->appendRow(item);
				currentItem = item;
				//qDebug("ITEM(%p) --> %s", item, attributes.value("showname").toAscii().constData());
			}
			else
				skip = true;
		}
	}
    return true;
}