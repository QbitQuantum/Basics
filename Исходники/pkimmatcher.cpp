// special characters are not properly converted by QChar::upper()
// of course still misses a lot.
QChar convertToUpper(const QChar& letter)
{
    const short offset = 32; //offset between upper and lower case letter
    if ( letter >= QChar(0x00e0) && letter <= QChar(0x00fe)) // special chars range
	return QChar(letter.unicode() - offset);
    else if ( letter == QChar(0x00ff) )
	return QChar(0x0179);
    return letter.toUpper();
}