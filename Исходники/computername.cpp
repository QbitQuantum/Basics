bool isWordCharacter(char c)
{
	return isDigit(c)||isCapitalLetter(c)||isSmallLetter(c)||c=='-';
}