BOOL CNamedIndexesOptimiser::AllocateSources(CNamedIndexesBlocks* pcBlocks, CIndexedFile* pcIndexedFile)
{
	CFileBasic*						pcFile;
	filePos							iSize;
	filePos							iNumBlocks;
	int								iChunks;
	filePos							iModulous;

	int								i;
	CNamesIndexedSorterSource*		pcSource;
	filePos							iPosition;

	pcFile = pcIndexedFile->GetPrimaryFile();

	iSize = pcFile->GetFileSize();
	iNumBlocks = iSize / pcBlocks->GetDataSize();
	iModulous = iSize % pcBlocks->GetDataSize();
	if (iModulous != 0)
	{
		return FALSE;
	}

	iChunks = (int)(iNumBlocks / pcBlocks->GetNumBlocks());
	iModulous = iNumBlocks % pcBlocks->GetNumBlocks();
	if (iModulous != 0)
	{
		return FALSE;
	}

	macSources.Allocate(&gcSystemAllocator, iChunks);

	for (i = 0; i < iChunks; i++)
	{
		iPosition = i * (pcBlocks->GetDataSize() * pcBlocks->GetNumBlocks());
		pcSource = macSources.Get(i);
		pcSource->Init(pcBlocks->GetDataSize(), iPosition);
	}

	return TRUE;
}