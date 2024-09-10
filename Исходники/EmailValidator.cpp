QValidator::State EmailValidator::checkLocal(const QString & str, int & pos)const {
	pos = 0;
	const QString allowed = "_-.!#$%&'*"
		//"+-/=?^_`{|}~" //characters after + are valid but ignored
		;
	if(str.isEmpty()) {
		return set(tr("Empty name before @ character"));
	}
	int i = 0;
	pos = 0;
	if(str[0] == '.') {
		return set(tr("Dot (.) can't be at the start of email"));
	}
	pos = str.count() - 1;
	if(str[pos] == '.') {
		return set(tr("Dot (.) can't be at the end of you email name"));
	}
	for(pos = 0; pos < str.length(); ++pos) {
		QChar ch = str[pos];
		if(isAsciiAlpha(ch) || ch.isDigit() || allowed.contains(ch))
			continue;
		return set(tr("Invalid character ") + ch);
	}
	return set(QValidator::Acceptable);
}