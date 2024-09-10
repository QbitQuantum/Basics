/*********************************************************************************
 * Open the file
 */
VFileHandle * __stdcall VOpenFile (const char * FileName, VHANDLE hVFS)
{
	CVFS_Manager * pVFS = (CVFS_Manager *)hVFS;

	if(pVFS) 
	{ 
		return pVFS->OpenFile (FileName); 
	}

	return NULL;
}