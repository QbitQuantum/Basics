/*!
 *  \fn DWORD PMD::cleanup()
 *  \ingroup win32backend
 *  \private
 *  \brief Cleans up the allocated memory before exiting a function.
 */
VOID PMD::cleanup() {

	if (hClientHandle != NULL) {
		printf ("\thClientHandle not null\n");
        WlanCloseHandle(
			hClientHandle, 
			NULL            // reserved
		);
    }
	if (pInterfaceList != NULL) {
		printf ("\tpInterfaceList not null \n");
		WlanFreeMemory(pInterfaceList);
	}
	
	if (pCurrentConnInfo != NULL)
	{
		printf ("\tpCurrentConnInfo not null\n");
		WlanFreeMemory(pCurrentConnInfo);
	}/*
	*/
}