int __cdecl main(int argc, char *argv[])
{
    BOOL bRc = FALSE;

    if (0 != PAL_Initialize(argc,argv))
    {
        return FAIL;
    }

    bRc = AreFileApisANSI();


    if (bRc == FALSE)
    {
        Fail("AreFileApisANSI: ERROR: Function returned FALSE whereas only TRUE "
            "is acceptable.\n");
    }

    PAL_Terminate();  
    return PASS;
}