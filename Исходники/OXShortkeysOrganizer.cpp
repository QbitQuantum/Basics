HACCEL COXShortkeysOrganizer::BuildAccelTable(CMultiDocTemplate* pDocTemplate)
{
	if(!IsAttached())
	{
		TRACE(_T("COXShortkeysOrganizer::BuildAccelTable: there is no attached frame window. You have to attach frame window before calling this function\n"));
		return NULL;
	}

	COXArrAccelerators* pArrAccels=FindAcceleratorTable(pDocTemplate);
	if(pArrAccels==NULL)
	{
		TRACE(_T("COXShortkeysOrganizer::BuildAccelTable: accelerator table for specified CMultiDocTemplate object doesn't exist\n"));
		return NULL;
	}

	ACCEL* pAccelTable=new ACCEL[pArrAccels->GetSize()];
	if(pAccelTable==NULL)
	{
		TRACE(_T("COXShortkeysOrganizer::BuildAccelTable: failed to allocate memory for new accelerator table\n"));
		return NULL;
	}
	for(int nIndex=0; nIndex<pArrAccels->GetSize(); nIndex++)
	{
		pAccelTable[nIndex].fVirt=pArrAccels->GetAt(nIndex).fVirt;
		pAccelTable[nIndex].key=pArrAccels->GetAt(nIndex).key;
		pAccelTable[nIndex].cmd=pArrAccels->GetAt(nIndex).cmd;
	}

    HACCEL hNewTable=::CreateAcceleratorTable(pAccelTable,PtrToInt(pArrAccels->GetSize()));
	m_arrCreatedAccel.Add(hNewTable);

	delete[] pAccelTable;

	return hNewTable;
}