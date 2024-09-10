BOOL SetUpFiles()
{
    int i = 0;
    BOOL result = TRUE;
    for (i = 0; i < numFileTests - 1 ; i++ )
    {
        gfaTestsFile[i].hFile = CreateFile(gfaTestsFile[i].name,
                        desiredAccessFile,
                        shareModeFile,
                        lpAttrFile,
                        dwCreationDispFile,
                        dwFlagsAttribFile,
                        hTemplateFile);

        if( gfaTestsFile[i].hFile == NULL )
        {
            Fail("Error while creating files for iteration %d\n", i);
        }

        if(!SetFileAttributesA (gfaTestsFile[i].name, gfaTestsFile[i].expectedAttribs))
        {
            result = FALSE;
            Trace("ERROR:%d: Error setting attributes [%s][%d]\n", GetLastError(), gfaTestsFile[i].name, gfaTestsFile[i].expectedAttribs); 
        } 
    }

    return result;
}