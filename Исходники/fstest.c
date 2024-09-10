int FS_Ansi()
{
    int NumErrors = 0;            // error count - to be returned
    int rc;                       // return code
    BYTE pFoldDestA[BUFSIZE];     // ptr to buffer


    //
    //  FoldStringA.
    //

    //  Variation 1  -  cbSrc = -1
    rc = FoldStringA( MAP_PRECOMPOSED,
                      "AbCd",
                      -1,
                      pFoldDestA,
                      BUFSIZE );
    CheckReturnValidA( rc,
                       -1,
                       pFoldDestA,
                       "AbCd",
                       NULL,
                       "A version cbSrc (-1)",
                       &NumErrors );

    //  Variation 2  -  cbSrc = value
    rc = FoldStringA( MAP_PRECOMPOSED,
                      "AbCd",
                      4,
                      pFoldDestA,
                      BUFSIZE );
    CheckReturnValidA( rc,
                       4,
                       pFoldDestA,
                       "AbCd",
                       NULL,
                       "A version cbSrc (value)",
                       &NumErrors );

    //  Variation 3  -  cbSrc = -1, no DestStr
    rc = FoldStringA( MAP_PRECOMPOSED,
                      "AbCd",
                      -1,
                      NULL,
                      0 );
    CheckReturnValidA( rc,
                       -1,
                       NULL,
                       "AbCd",
                       NULL,
                       "A version cbSrc (-1), no DestStr",
                       &NumErrors );

    //  Variation 4  -  cbSrc = value, no DestStr
    rc = FoldStringA( MAP_PRECOMPOSED,
                      "AbCd",
                      4,
                      NULL,
                      0 );
    CheckReturnValidA( rc,
                       4,
                       NULL,
                       "AbCd",
                       NULL,
                       "A version cbSrc (value), no DestStr",
                       &NumErrors );


    //
    //  Return total number of errors found.
    //
    return (NumErrors);
}