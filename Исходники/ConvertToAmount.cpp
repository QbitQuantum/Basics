static
ParseResult ParseWholePart(QString::const_iterator begin, QString::const_iterator end)
{
	Amount a (0);
	QString::const_iterator iter;
	for (iter = begin; iter != end; iter++) {
		if (iter->isDigit()) {
			a *= Amount(10);					//scale up
			a = a + Amount(iter->digitValue()); //add
		} else if (*iter == QLocale().groupSeparator()) {
			//eat it
		} else if (*iter == QLocale().decimalPoint()) {
			iter++; //skip the decimal point
			return ParseResult(a, iter);
		} else {
			throw std::runtime_error("Invalid currency string");
		}
	}
	return ParseResult(a,iter);
}