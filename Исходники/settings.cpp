bool DataFile::GetEntry(BString key, BString &result)
////////////////////////////////////////////////////////////////////////
{
	if (key.Length() == 0)
		return false;
	
	unsigned char hashcode = GetHash(key);
	DataEntry *tempentry;

	for (int i=0; i<m_Entries.CountItems(); i++)
	{
		tempentry = (DataEntry *)m_Entries.ItemAt(i);
		if (tempentry)
		{
			if (tempentry->HashValue == hashcode && tempentry->Key == key)
			{
				result = tempentry->Value;
				return true;
			}
		}
	}	
	
	return false;
}