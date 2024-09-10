void BOSSamp::BuildCclOBuf(LPDISPATCH commArea) 
{
	// TODO: Add your dispatch handler code here

	//
	// Map commArea onto a CICS OLE Buffer object
	//
	CclBuffer pBuffer = CclBuffer(commArea);
	//
	// Create a new CICS C++ Buffer object, and place the business objects
	// using the appropriate structure, for communicating with the server
	//
	CclBuf* buffer = new CclBuf();
	time_t doBT;
	doBT = doB.GetTime();
	char nu = '\0';
	buffer->assign(sizeof(doBT),&doB);
	buffer->insert(sizeof(yearsService),&yearsService);
	buffer->insert(sizeof(nu),&nu);
	buffer->insert(name.GetLength(),name);
	//
	// Create a safe array to hold the buffer data
	//
	SAFEARRAY * commData;
	SAFEARRAYBOUND sabound[1];
	void * pData;
	sabound[0].lLbound = 0;
	sabound[0].cElements = buffer->dataLength();
	commData = SafeArrayCreate ( VT_UI1, 1, sabound );
	//commData->pvData = (void *)buffer->dataArea();
	SafeArrayAccessData( commData, &pData );
	memcpy(pData,buffer->dataArea(),buffer->dataLength());
	SafeArrayUnlock(commData);
	//
	// Construct the VARIANT object and prime it with the safe array
	//
	VARIANT commVariant;
	VariantInit(&commVariant);
	commVariant.pparray = &commData;
	commVariant.vt = VT_BYREF|VT_ARRAY|VT_UI1;
	//
	// Set the data in the CICS OLE buffer object
	//
	pBuffer.SetData(commVariant);
	//
	// Detach and Release the 'mapped' CICS OLE buffer object
	//
	pBuffer.DetachDispatch();
	pBuffer.ReleaseDispatch();
}