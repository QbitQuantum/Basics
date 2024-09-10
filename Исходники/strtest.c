void TestMove( void )
{
    char            bufA[80] = "FoO baR gOoBeR bLaH";
    char            bufB[80];
    char            *bufPtr;
    char            *newBuf;
    int             status;

    bufPtr = strcpy( bufB, "FoO baR" );         /* copy string */
    VERIFY( bufPtr == bufB );

    bufPtr = strcat( bufB, " gOoBeR bLaH" );    /* append the rest */
    VERIFY( bufPtr == bufB );

    status = strcmp( bufA, bufB );              /* check result */
    VERIFY( status == 0 );

    bufPtr = strset( bufB, 0x00 );              /* zero out buffer */
    VERIFY( bufPtr == bufB );

    bufPtr = strncpy( bufB, "ABCDEFGHIJ", 2 );  /* copy two bytes */
    VERIFY( bufPtr == bufB );

    bufPtr = strncat( bufB, "CDEFGHIJ", 3 );    /* copy three more */
    VERIFY( bufPtr == bufB );

    status = strcmp( bufB, "ABCDE" );           /* ensure only five bytes */
    VERIFY( status == 0 );

    bufPtr = strnset( bufB, 0x00, 10 );         /* blank string */
    VERIFY( bufPtr == bufB );

    status = strcmp( bufB, "" );                /* verify empty */
    VERIFY( status == 0 );

    bufPtr = strcpy( bufB, "abcdefghij" );      /* copy string */
    VERIFY( bufPtr == bufB );

    bufPtr = strrev( bufB );                    /* reverse it */
    VERIFY( bufPtr == bufB );

    status = strcmp( bufB, "jihgfedcba" );      /* ensure reversed ok */
    VERIFY( status == 0 );

    newBuf = strdup( bufA );                    /* duplicate string */
    status = strcmp( bufA, newBuf );
    VERIFY( status == 0 );
}