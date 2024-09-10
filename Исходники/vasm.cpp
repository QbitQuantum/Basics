//////////
//
// VVM Assembler command line syntax is simple:
//
//////
int main(int argc, s8* argv[])
{
    bool	llNull;
    s32		lnI, lnLength;


    // Tell the world who we are
    printf("Visual FreePro Assembler OBED 0.70\n");
    printf("Copyright (c) 2012-2014 Rick C. Hodgin - Released under PBL 1.0 - /? for help\n");
    printf("---\n");
    printf("---\n");


    // Repeat for every command line parameter
    for (lnI = 1; lnI < argc; lnI++)
    {
        llNull		= true;
        lnLength	= strlen(argv[lnI]);
        if (lnLength >= 2 && (_memicmp(argv[lnI], "/?", 2) == 0 || _memicmp(argv[lnI], "-h", 2) == 0 || _memicmp(argv[lnI], "/h", 2) == 0))
        {
            // They want help
            iShowHelp();

        } else if (lnLength > 3 && _memicmp(argv[lnI], "-r:", 3) == 0) {
            // They are specifying an override for the default language
            iProcessCommandLineLanguageOption(argv[lnI]);

        } else if (lnLength >= 2 && _memicmp(argv[lnI], "/q", 2) == 0) {
            // They want quiet mode
            glQuiet = true;

        } else if (lnLength >= 2 && _memicmp(argv[lnI], "/i", 2) == 0) {
            // They want to ignore warnings
            glIgnoreWarnings = true;

        } else {
            // We will soon try to open the indicated file, but not yet
            llNull = false;
        }

        // Set first byte null if we are done processing this entry
        if (llNull)
            argv[lnI][0] = 0;
    }
    // When we get here, we've done a first pass on the command line parameters


    // Try to load the OSS.DLL and MC.DLL files now that we have the language
    iLoadDlls();


    // Now, try to open and assemble the remaining files
    for (lnI = 1; lnI < argc; lnI++)
    {
        if (argv[lnI][0] != 0)
        {
            // Try to assemble this file
            iAssembleFile(argv[lnI]);
        }
    }


    // All done
    printf("---\n");
    printf(mc_loadResourceAsciiText(IDS_FILES_PROCESSED), gnFilesProcessed, gnErrors, gnWarnings);
    return gnErrors;
}