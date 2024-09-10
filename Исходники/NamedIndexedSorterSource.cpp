BOOL CNamesIndexedSorterSource::IsSmallerThan(CNamesIndexedSorterSource* pcOther)
{
	int		iResult;

	if (mpcCurrent->IsEmpty())
	{
		return FALSE;
	}
	else
	{
		if (pcOther == NULL)
		{
			return TRUE;
		}

		iResult = StrICmp(mpcCurrent->Name(), pcOther->mpcCurrent->Name());
		if (iResult < 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}