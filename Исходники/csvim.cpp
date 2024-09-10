void CsvIm::loadFile()
{
	QString text = "";
	QByteArray rawText;
	if (loadRawText(filename, rawText))
		text = toUnicode(rawText);
	QStringList lines = text.split("\n", QString::SkipEmptyParts);
	uint i;
	if (hasHeader)
	{
		colIndex = 0;
		parseLine(lines[0], true);
		header += "\n";
		colCount = colIndex;
		i = 1;
		++rowNumber;
	}
	else
		i = 0;
	for (int i2 = i; i2 < lines.size(); ++i2)
	{
		colIndex = 0;
		parseLine(lines[i2], false);
		data += "\n";
		++rowNumber;
		if (colCount < colIndex)
			colCount = colIndex;
	}
}