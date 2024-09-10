ChEXPORT ChFILE* openTestFile(const ChCHAR1* in_fileName)
{
#if defined(__APPLE__) 
    static ChCHAR1 testFilesPath[1024] = {0};
    
    if (testFilesPath[0] == 0)
    {
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef mainURL ChUNUSED = CFBundleCopyBundleURL(mainBundle);
        
        // This will fail if 1024 bytes isn't enough
        ChASSERT(CFURLGetFileSystemRepresentation(mainURL, true, (UInt8*)&testFilesPath, 1024));
        
        // NOTE: We include the path seperator at the end so that we don't need
        // to add it on later.
        strcat(testFilesPath, "/testfiles/");
    }
    
    ChCHAR1 thePath[2048];
    
    strcpy(thePath, testFilesPath);
    strcat(thePath, in_fileName);
    
    return Chfopen(thePath, "rb");
    
#elif defined (WIN32) || defined (_WIN32)
    static ChCHAR1 testFilesPath[1024] = {0};
    ChCHAR1 thePath[2048];
    
    
    if (testFilesPath[0] == 0)
    {
        char* pFileSep = NULL;
        DWORD hres = GetModuleFileNameA( NULL, testFilesPath, 1024 );

        ChASSERT(SUCCEEDED(hres));
        // NOTE: We include the path seperator at the end so that we don't need
        // to add it on later.
        pFileSep = strrchr( testFilesPath, '\\' );
        ChASSERT( pFileSep );
        *pFileSep = '\0';
        strcat(testFilesPath, "\\..\\..\\UnitTests\\TestFiles\\");
    }
    
    strcpy(thePath, testFilesPath);
    strcat(thePath, in_fileName);
    
    return Chfopen(thePath, "rb");
#else
    // A platform specific openTestFile implementation is required

    static ChCHAR1 testFilesPath[1024] = {0};
    
    if (testFilesPath[0] == 0)
    {

	// TODO: This is incorrect.  Need to get path of executable.
	strcpy(testFilesPath, ".");
        // NOTE: We include the path seperator at the end so that we don't need
        // to add it on later.
        strcat(testFilesPath, "/testfiles/");
    }
    
    ChCHAR1 thePath[2048];
    
    strcpy(thePath, testFilesPath);
    strcat(thePath, in_fileName);
    
    return Chfopen(thePath, "rb");
#endif
}