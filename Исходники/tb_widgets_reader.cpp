bool TBWidgetsReader::LoadFile(TBWidget *target, const char *filename)
{
	TBNode node;
	if (!node.ReadFile(filename))
		return false;
	LoadNodeTree(target, &node);
	return true;
}