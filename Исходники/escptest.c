int ESCP_NormalCase()
{
    int NumErrors = 0;            // error count - to be returned
    int rc;                       // return code


    if (Verbose)
    {
        printf("\n----  W version  ----\n\n");
    }

    //  Variation 1  -  installed
    CodePageCtr = 0;
    rc = EnumSystemCodePagesW( MyFuncCP,
                               CP_INSTALLED );
    CheckReturnValidEnum( rc,
                          TRUE,
                          CodePageCtr,
                          NUM_INSTALLED_CPS,
                          "Flag installed",
                          &NumErrors );

    //  Variation 2  -  Supported
    CodePageCtr = 0;
    rc = EnumSystemCodePagesW( MyFuncCP,
                               CP_SUPPORTED );
    CheckReturnValidEnum( rc,
                          TRUE,
                          CodePageCtr,
                          NUM_SUPPORTED_CPS,
                          "Flag supported",
                          &NumErrors );


    //
    //  Return total number of errors found.
    //
    return (NumErrors);
}