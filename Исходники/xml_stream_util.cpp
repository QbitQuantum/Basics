void XmlElementReader::read(MapCoordVector& coords)
{
	namespace literal = XmlStreamLiteral;
	
	coords.clear();
	
	const auto num_coords = attribute<unsigned int>(literal::count);
	coords.reserve(std::min(num_coords, 500000u));
	
	try
	{
		for( xml.readNext(); xml.tokenType() != QXmlStreamReader::EndElement; xml.readNext() )
		{
			const QXmlStreamReader::TokenType token = xml.tokenType();
			if (xml.error() || token == QXmlStreamReader::EndDocument)
			{
				throw FileFormatException(ImportExport::tr("Could not parse the coordinates."));
			}
			else if (token == QXmlStreamReader::Characters && !xml.isWhitespace())
			{
				QStringRef text = xml.text();
				QString data = QString::fromRawData(text.constData(), text.length());
				
				QTextStream stream(&data, QIODevice::ReadOnly);
				stream.setIntegerBase(10);
				while (!stream.atEnd())
				{
					coords.emplace_back();
					stream >> coords.back();
				}
				
				if (stream.status() == QTextStream::ReadCorruptData)
				{
					throw FileFormatException(ImportExport::tr("Could not parse the coordinates."));
				}
			}
			else if (token == QXmlStreamReader::StartElement)
			{
				if (xml.name() == literal::coord)
				{
					coords.emplace_back(MapCoord::load(xml));
				}
				else
				{
					xml.skipCurrentElement();
				}
			}
			// otherwise: ignore element
		}