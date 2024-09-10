bool CreateBinaryFromList (CCodeChain &CC, const CString &sClass, ICCItem *pList, void *pvDest)

//	CreateBinaryFromList
//
//	Initializes binary structure from a list

	{
	int iStart = 0;

	//	Check the class, if provided

	if (!sClass.IsBlank())
		{
		if (pList->GetCount() < 1)
			return false;

		if (!strEquals(pList->GetElement(0)->GetStringValue(), sClass))
			return false;

		iStart++;
		}

	//	Load the binary data

	DWORD *pDest = (DWORD *)pvDest;
	for (int i = iStart; i < pList->GetCount(); i++)
		*pDest++ = (DWORD)pList->GetElement(i)->GetIntegerValue();

	return true;
	}