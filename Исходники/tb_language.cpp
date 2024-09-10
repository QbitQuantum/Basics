bool TBLanguage::Load(const char *filename)
{
	// Read the file into a node tree (even though it's only a flat list)
	TBNode node;
	if (!node.ReadFile(filename))
		return false;

	// Go through all nodes and add to the strings hash table
	TBNode *n = node.GetFirstChild();
	while (n)
	{
		const char *str = n->GetValue().GetString();
		TBStr *new_str = new TBStr(str);
		if (!new_str || !strings.Add(TBID(n->GetName()), new_str))
		{
			delete new_str;
			return false;
		}
		n = n->GetNext();
	}
	return true;
}