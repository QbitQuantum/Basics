void CoordXmlTest::readHumanReadableStream()
{
	namespace literal = XmlStreamLiteral;
	
	QFETCH(int, num_coords);
	MapCoordVector coords(num_coords, proto_coord);
	
	buffer.buffer().truncate(0);
	QBuffer header;
	{
		QXmlStreamWriter xml(&header);
		
		header.open(QBuffer::ReadWrite);
		xml.setAutoFormatting(false);
		xml.writeStartDocument();
		xml.writeStartElement("root");
		xml.writeCharacters(""); // flush root start element
		
		buffer.open(QBuffer::ReadWrite);
		xml.setDevice(&buffer);
		xml.writeStartElement("coords");
		// Using the more efficient string implementation.
		writeHumanReadableString_implementation(coords, xml);
		xml.writeEndElement();
		
		xml.setDevice(NULL);
		
		buffer.close();
		header.close();
	}
	
	header.open(QBuffer::ReadOnly);
	buffer.open(QBuffer::ReadOnly);
	QXmlStreamReader xml;
	xml.addData(header.buffer());
	xml.readNextStartElement();
	QCOMPARE(xml.name().toString(), QString("root"));
	
	bool failed = false;
	QBENCHMARK
	{
		// benchmark iteration overhead
		coords.clear();
		xml.addData(buffer.data());
		
		xml.readNextStartElement();
		if (xml.name() != "coords")
		{
			failed = true;
			break;
		}
		
		for( xml.readNext();
		     xml.tokenType() != QXmlStreamReader::EndElement;
		     xml.readNext() )
		{
			if (xml.error())
			{
				qDebug() << xml.errorString();
				failed = true;
				break;
			}
			
			const QXmlStreamReader::TokenType token = xml.tokenType();
			if (token == QXmlStreamReader::EndDocument)
			{
				failed = true;
				break;
			}
			
			if (token == QXmlStreamReader::Characters && !xml.isWhitespace())
			{
				QStringRef text = xml.text();
				QString data = QString::fromRawData(text.constData(), text.length());
				QTextStream stream(&data, QIODevice::ReadOnly);
				stream.setIntegerBase(10);
				while (!stream.atEnd())
				{
					qint32 x, y;
					int flags = 0;
					char separator;
					stream >> x >> y >> separator;
					if (separator != ';')
					{
						stream >> flags >> separator;
					}
					coords.push_back(MapCoord::fromNative(x, y, flags));
				}
				if (stream.status() == QTextStream::ReadCorruptData)
				{
					failed = true;
					break;
				}
			}
			// otherwise: ignore element
		}