DWORD CChangeGroup::GetChangeHash()
{
	DWORD dwHash = 0;
	int iSize =  (x64_int_cast)theChanges.size();

	for (int i = 0; i<iSize; i++)
	{
		if (theChanges[i]->GetNumber()>0)
		{
			dwHash = _rotl(dwHash,1) ^ theChanges[i]->GetHash();
		}
	}
	return dwHash;
}