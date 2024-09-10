int cParsedNBT::FindTagByPath(int a_Tag, const AString & a_Path) const
{
	if (a_Tag < 0)
	{
		return -1;
	}
	size_t Begin = 0;
	size_t Length = a_Path.length();
	int Tag = a_Tag;
	for (size_t i = 0; i < Length; i++)
	{
		if (a_Path[i] != '\\')
		{
			continue;
		}
		Tag = FindChildByName(Tag, a_Path.c_str() + Begin, i - Begin - 1);
		if (Tag < 0)
		{
			return -1;
		}
		Begin = i + 1;
	}  // for i - a_Path[]
	
	if (Begin < Length)
	{
		Tag = FindChildByName(Tag, a_Path.c_str() + Begin, Length - Begin);
	}
	return Tag;
}