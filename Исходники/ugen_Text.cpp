Text Text::replaceIgnoreCase(Text const& find, Text const& substitute) const throw()
{
	Text thisLower = this->toLower();
	Text findLower = find.toLower();
	const int size = this->size();
	const int findLength = find.length();
	int startIndex = 0;
	int findIndex;
	
	Text result;
	
	while((findIndex = thisLower.indexOf(findLower, startIndex)) >= 0)
	{
		result <<= this->range(startIndex, findIndex);
		result <<= substitute;
		startIndex = findIndex + findLength;
	}
	
	result <<= this->range(startIndex, size);
	
	return result;
}