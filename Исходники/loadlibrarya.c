int __cdecl main(int argc, char *argv[])
{
    HANDLE hFullLib;
    HANDLE hShortLib;
    HANDLE hRelLib;

    int    iRetVal  = FAIL;
    char   fullPath[_MAX_DIR];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char relTestDir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    
    BOOL bRc = FALSE;
    char   relLibPath[_MAX_DIR];


    /* Initialize the PAL. */
    if ((PAL_Initialize(argc, argv)) != 0)
    {
        return (FAIL);
    }

    /* Initalize the buffer.
     */
    memset(fullPath, 0, _MAX_DIR);

    /* Get the full path to the library (DLL).
     */
  
       if (NULL != _fullpath(fullPath,argv[0],_MAX_DIR)) {
	
	 _splitpath(fullPath,drive,dir,fname,ext);
	 _makepath(fullPath,drive,dir,LibraryName,"");
	 
	
	} else {
		Fail("ERROR: conversion from relative path \" %s \" to absolute path failed. _fullpath returned NULL\n",argv[0]);
	}

       /* Get relative path to the library
	*/
       _splitpath(argv[0], drive, relTestDir, fname, ext);
       _makepath(relLibPath,drive,relTestDir,LibraryName,"");


    /* Call Load library with the short name of
     * the dll.
     */
    hShortLib = LoadLibrary(LibraryName);
    if(hShortLib == NULL)
    {
        Fail("ERROR:%u:Short:Unable to load library %s\n", 
             GetLastError(), 
             LibraryName);
    }
    
    /* Test the loaded library.
     */
    if (!TestDll(hShortLib))
    {
        iRetVal = FAIL;
        goto cleanUpOne;
    }

    /* Call Load library with the full name of
     * the dll.
     */
    hFullLib = LoadLibrary(fullPath);
    if(hFullLib == NULL)
    {
        Trace("ERROR:%u:Full:Unable to load library %s\n", 
              GetLastError(), 
              fullPath);
        iRetVal = FAIL;
        goto cleanUpTwo;
    }

    /* Test the loaded library.
     */
    if (!TestDll(hFullLib))
    {
        iRetVal = FAIL;
        goto cleanUpTwo;
    }

    /*
    ** Call the load library with the relative path
    ** wrt to the directory ./testloadlibrary/.. 
    ** since we don't want to make any assumptions
    ** regarding the type of build
    */
    hRelLib = LoadLibrary(relLibPath);
    if(hRelLib == NULL)
    {
        Trace("ERROR:%u:Rel:Unable to load library at %s\n", 
              GetLastError(), relLibPath);
        iRetVal = FAIL;
        goto cleanUpTwo;
    }

    /* Test the loaded library.
     */
    if (!TestDll(hRelLib))
    {
        iRetVal = FAIL;
        goto cleanUpThree;
    }

   if( hRelLib != hFullLib )
   {
        Trace("Relative and Absolute Paths to libraries don't have same handle\n");
            iRetVal = FAIL;
            goto cleanUpThree;
   }

   if( hRelLib != hShortLib )
   {
        Trace("Relative and Short Paths to libraries don't have same handle\n");
            iRetVal = FAIL;
            goto cleanUpThree;
   }


   /* Test Succeeded.
     */
    iRetVal = PASS;

cleanUpThree:

    /* Call the FreeLibrary API. 
     */ 

    if (!FreeLibrary(hRelLib))
    {
        Trace("ERROR:%u: Unable to free library \"%s\"\n", 
              GetLastError(),
              relLibPath);
        iRetVal = FAIL;
    }

cleanUpTwo:

    /* Call the FreeLibrary API. 
     */ 
    if (!FreeLibrary(hFullLib))
    {
        Trace("ERROR:%u: Unable to free library \"%s\"\n", 
              GetLastError(),
              fullPath);
        iRetVal = FAIL;
    }

cleanUpOne:

    /* Call the FreeLibrary API. 
     */ 
    if (!FreeLibrary(hShortLib))
    {
        Trace("ERROR:%u: Unable to free library \"%s\"\n", 
              GetLastError(),
              LibraryName);
        iRetVal = FAIL;
    }


    /* Terminate the PAL.
     */
    PAL_Terminate();
    return iRetVal;

}