int XTree::addElement(int pid, int lsid, std::string tagName)
{
	_elementIndex++;

	int	topid = _elementIndex / _botCap;
	int	botid = _elementIndex % _botCap;
	if (botid == 0)
		_expand(topid);

	// Check if we've got the element name
	hash_map <std::string, int, HashString>::const_iterator
		hit = _tagNames.find(tagName);
	if (hit != _tagNames.end())
	{
		int	id = hit->second;
		_valueIndex[topid][botid] = id;
	}
	else
	{
		_tagIndex++;
		_value[0][_tagIndex] = tagName;
		_tagNames[tagName] = _tagIndex;
		_valueIndex[topid][botid] = _tagIndex;
	}

	if (pid == NULL_NODE)
		return _elementIndex;

	int	ptopid = pid / _botCap;
	int	pbotid = pid % _botCap;
	// parent-child relation or sibling-sibling ralation
	if (lsid == NULL_NODE)
		_firstChild[ptopid][pbotid] = _elementIndex;
	else
		_nextSibling[lsid/_botCap][lsid%_botCap] = _elementIndex;

	// update children count
	_childrenCount[ptopid][pbotid]++;

	return _elementIndex;
}