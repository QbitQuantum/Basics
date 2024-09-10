/*----------------------------------------------------------------------*
 *  •   prototypes                                                      *
 *—————————————————————————————————————————————————————————————————————-*/
static Boolean
Print_Standard_Labels (void )
{
    SInt32                  i = 0;
    Boolean                 rc = FALSE;
    char                    lLblType[4];
    char                    lLblNum[2];
    SInt32                  iLblType = 0;

    sscanf ( gStdLblBuffer, "%3c%1c%*76c", lLblType, lLblNum );
    TERMINATE(lLblType);
    TERMINATE(lLblNum);

    if ( isdigit( lLblNum[0] ) )
    { if ( lLblNum[0] < '1' || lLblNum[0] > '9' ) return ( FALSE ); } /* this should be transportable to EBCDIC machines */
    else
        return ( FALSE );

    if ( strcmp ( lLblType, "VOL" ) == 0 )      iLblType = 1;       /* VOL  */

    if ( ( strcmp ( lLblType, "HDR" ) == 0 ) ||
        ( strcmp ( lLblType, "EOF" ) == 0 ) ||
        ( strcmp ( lLblType, "EOV" ) == 0 ) )   iLblType = 2;       /* HDR | EOF | EOV  */

    if ( ( strcmp ( lLblType, "UHL" ) == 0 ) ||
        ( strcmp ( lLblType, "UTL" ) == 0 ) )   iLblType = 3;       /* UHL | UTL    User Labels */

    switch ( iLblType )
    {
        case    1:
        {
            char    volser[7];                              /* ( 5-10) Volume ID                */
            char    vsec[2]                                 /* (   11) Volume Accessability     */
            /* 5 bytes  */                                  /* (12-16) VTOC Pointer (not used)  */
            ;/* 21 bytes */                                 /* (17-37) Reserved                 */
            char    owner[15]                               /* (38-51) Owner ID                 */
            ;/* 29 bytes */                                 /* (52-80) Reserved                 */

            /*       1...5...10...15...20...25...30...35...40...45...50...55...60...65...70...75...80
             *       VOL1volsr|sRESERVED-----------------|owner--------|RESERVED--------------------|
             */
            sscanf ( gStdLblBuffer, "%*3c%*1c%6c%1c%*5c%*21c%14c%*29c", volser, vsec, owner );

            TERMINATE(volser);      /* Null terminate the arrays */
            TERMINATE(vsec);
            TERMINATE(owner);

            printf ( "\n%-2s", "" );

            if ( atoi( lLblNum ) == 1 )
                printf ( "Standard Label Tape\n\n%-4s"
                        "VolSer: %-10s"
                        "Owner: %s\n", "", volser, owner );
            else
                printf ( "%-4s %1s %-s\n", lLblType, lLblNum, &gStdLblBuffer[4] );
        }
            rc = TRUE;
            break;

        case    2:
        {
            switch ( atoi( lLblNum ) )
            {
                case 1:
                {
                    char    fid[18];                /* ( 5-21) rightmost 17 char of file Identifier (dataset name DSN)  */
                    char    afset[7];               /* (22-27) Aggregate volume ID (volser 1st vol)                     */
                    char    afseq[5];               /* (28-31) Aggregate volume seq (multi-volume)                      */
                    char    fseq[5];                /* (32-35) file seq number 0001-9999 < x'6F'xxxxxx 1-64000(bin)     */
                    char    gen[5];                 /* (36-39) generation number    (not used)                          */
                    char    gver[3];                /* (40-41) generation version   (not used)                          */
                    char    cdate[7]                /* (42-47) creation date                                            */
                    ;                               /*         cyyddd;c = blank 19, 0 = 20, 1 = 21; jdate               */
                    char    edate[7];               /* (48-53) expiration date                                          */
                    char    fsec[2]                 /* (   54) File Security        (not used)                          */
                    ;                               /*              0=none,1=pwd-R-W-Del,3=pwd-W-Del                    */
                    char    bcnt[7];                /* (55-60) block count (blockcnt % 1000000) (HDR=0) (EOF/EOV)       */
                    char    impid[14]               /* (61-73) System Code (IBMOS400|IBM OS/VS 370)                     */
                    ;                               /* (74-76) Reserved                                                 */
                    char    ebcnt[5];               /* (77-80) extended block count (blockcnt / 1000000)(EOF/EOV)       */

                    /*       1...5...10...15...20...25...30...35...40...45...50...55...60...65...70...75...80
                     *       HDR1DSNAME----------|afvst|afs|fsq|---|-|cdate|edate||bcnt-|syscode-----|RR|ebct
                     *       {EOF}                                 n/a         fsec^
                     *       {EOV}
                     */
                    sscanf( gStdLblBuffer, "%*3c%*1c%17c%6c%4c%4c%4c%2c%6c%6c%1c%6c%13c%*3c%4c",
                           fid, afset, afseq, fseq, gen, gver, cdate, edate, fsec, bcnt, impid, ebcnt);

                    TERMINATE(fid);             /* NULL Terminate the arrays */
                    TERMINATE(afset);
                    TERMINATE(afseq);
                    TERMINATE(fseq);
                    TERMINATE(gen);
                    TERMINATE(gver);
                    TERMINATE(cdate);
                    TERMINATE(edate);
                    TERMINATE(fsec);
                    TERMINATE(bcnt);
                    TERMINATE(impid);
                    TERMINATE(ebcnt);

                    if ( lLblType[0] == 'E' )
                    {
                        for ( i = 0; i < 4; i++ ) { if ( !isdigit( ebcnt[i] ) ) ebcnt[i] = '0'; }
                        ebcnt[4] = '\0';
                    }
                    else
                        if ( atoi( lLblNum ) == 1 )
                            printf ("\f");

                    if ( fseq[0] == '?' )       /* this is the indicator that IBM uses for seq no > 9999 ebcdic x'6f' */
                    {
                        fseq[0] = '\x00';
                        gLastFileSeqSL = ( ( fseq[0]    << 24 ) & 0xff000000 )
                        |( ( fseq[1]    << 16 ) & 0x00ff0000 )
                        |( ( fseq[2]    << 8  ) & 0x0000ff00 )
                        |( ( fseq[3]          ) & 0x000000ff );
                    }
                    else
                        gLastFileSeqSL = (UInt32)atol( fseq );

                    printf ( "\n%-4s"
                            "SL File Seq: %-4d%-3s"
                            "DSNAME: %-20s"
                            , "", atoi( fseq ), "", fid );

                    printf ( "Created: " );
                    if ( cdate[0] == ' ' )
                        if ( (int)( atol( &cdate[1] ) / 1000l ) < 1967 )
                            printf ( "20" );
                        else
                            printf ( "19" );
                    else
                        printf ( "2%1c", cdate[0] );
                    printf ( "%02d.%03d%-3s", (int)( atol( &cdate[1] ) / 1000l ), atoi( &cdate[3] ), "" );

                    if ( strcmp ( &edate[1], "00000" ) !=0 )
                    {
                        printf ( "Expires: " );
                        if ( atoi ( &edate[3] ) == 0 )
                            printf ( "TMS-%-5s", &edate[1] );
                        else
                        {
                            if ( edate[0] == ' ' )
                                if ( (int)( atol( &edate[1] ) / 1000l ) < 1967 )
                                    printf ( "20" );
                                else
                                    printf ( "19" );
                            else
                                printf ( "2%1c", edate[0] );
                            printf ( "%02d.%03d%-1s", (int)( atol( &edate[1] ) / 1000l ), atoi( &edate[3] ), "" );
                        }
                    }
                    else
                        printf ( "%-9s", "NO EXPDT" );

                    printf ( "%-3sSystem: %s\n", "", impid );

                    if ( gStdLblBuffer[0] == 'E' )
                    {
                        UInt64   lBlockCnt  = (UInt64)(atol( bcnt ) % 1000000l) + (UInt64)(atol( ebcnt ) * 1000000l);
                        printf ( "%-4sBlock Count: "
                                "Expected %llu; "
                                "Actual %d",
                                "", lBlockCnt, (int)gPrevBlkCnt );
                        if ( lBlockCnt == (UInt64)gPrevBlkCnt )
                            printf ( "\n" );
                        else
                            printf ( "%-4s---> BLOCK COUNT MISMATCH <---\n", "" );
                    }
                    else
                    {
                        gMltVolSet[0] = '\0';
                        gMltVolSeq[0] = '\0';
                        strcpy ( gMltVolSet, afset );
                        strcpy ( gMltVolSeq, afseq );
                    }
                }
                    break;

                case 2:
                {
                    char    fmt[2];                             /* (    5) Format F=fixed;V=variable;U=unblock              */
                    char    bsize[6];                           /* ( 6-10) Block Size 1-32767 (>32767 see large block size) */
                    char    rsize[6];                           /* (11-15) Record Size                                      */
                    char    tden[2];                            /* (   16) Density of tape 3=1600,4=6250,5=3200,blank=others */
                    char    mltv[2];                            /* (   17) Multi-volume switch 1/0 2nd + tape seq num       */
                    char    jname[9]                            /* (18-25) Job Name creating tape                           */
                    ;/* 1 byte */                               /* (   26) '/' Separator                                    */
                    char    sname[9];                           /* (27-34) Step Name creating tape                          */
                    char    rtech[3];                           /* (35-36) Adv. Recording tech. blank=none;'P '=IDRC        */
                    char    pcchr[2];                           /* (   37) Printer Control Char A=ANSI;M=machine            */
                    char    battr[2]                            /* (   38) Block Attr B=blkd;S=Spanned(V)|Std(F);R=B&S      */
                    ;/* 3 bytes */                              /* (39-47) Reserved                                         */
                    char    ckpt[2]                             /* (   48) Chkpt Data Set ID; C=secure CKPT dsn;blank - not */
                    ;/* 22 chars */                             /* (49-70) Reserved                                         */
                    char    lbsiz[11];                          /* (71-80) Large Block Size > 32767                         */

                    char    tmp[10];
                    char    dcb[80];

                    /*       1...5...10...15...20...25...30...35...40...45...50...55...60...65...70...75...80
                     *       HDR2|bsiz|rsiz|||jname--|/sname--|r||R|RR000000|RESERVED-------------|lbsize---|
                     *      {EOF}^-- FORMAT |^- MULTI-VOL        | ^- BLK'D ^- CKPT
                     *      {EOV}           ^-- DENSITY          ^-CC {A|M| }
                     */
                    sscanf( gStdLblBuffer,
                           "%*3c"               /*  3 HDR | EOF | EOV                           */
                           "%*1c"               /*  1 1-9                                       */
                           "%1c"                /*  1 fmt                                       */
                           "%5c"                /*  5 bsize                                     */
                           "%5c"                /*  5 rsize                                     */
                           "%1c"                /*  1 tden                                      */
                           "%1c"                /*  1 mltv      Multi-volume switch indicator   */
                           "%8c"                /*  8 jname                                     */
                           "%*1c"               /*  1 '/'                                       */
                           "%8c"                /*  8 sname                                     */
                           "%2c"                /*  2 rtech                                     */
                           "%1c"                /*  1 cc        A | M                           */
                           "%*1c"               /*  1 reserved                                  */
                           "%1c"                /*  1 battr     B | S | BS | ' '                */
                           "%*2c"               /*  2 reserved                                  */
                           "%*6c"               /*  6 Device Serial number or 6 blanks          */
                           "%1c"                /*  1 ckpt      Checkpoint Data Set Id          */
                           "%*22c"              /* 22 reserved                                  */
                           "%10c"               /* 10 lbsize    large block size (> 32767)      */
                           , fmt, bsize, rsize, tden, mltv, jname, sname, rtech, pcchr, battr, ckpt, lbsiz);

                    TERMINATE(fmt);         /* NULL terminate the arrays */
                    TERMINATE(bsize);
                    TERMINATE(rsize);
                    TERMINATE(tden);
                    TERMINATE(mltv);
                    TERMINATE(jname);
                    TERMINATE(sname);
                    TERMINATE(rtech);
                    TERMINATE(pcchr);
                    TERMINATE(battr);
                    TERMINATE(ckpt);
                    TERMINATE(lbsiz);

                    if ( gStdLblBuffer[0] == 'H' )
                    {
                        tmp[0] = dcb[0] = '\0';

                        printf ( "%-4sCreated by: Job %-8s; Step %-11s%-6s"
                                , "", jname, sname, "" );

                        strlcat ( dcb, "DCB=(RECFM=", sizeof(dcb) );

                        strlcat ( dcb, fmt, sizeof(dcb) );      /* first character of the RECFM F|V|U                   */
                                                                /* next 'S' means SPANNED for 'V' and STANDARD for 'F'  */
                        if ( battr[0] == 'R' )                  /* next 1 or 2 (if = 'R') characters B|S|R|' '          */
                            strlcat ( dcb, "BS", sizeof(dcb) ); /* 'R' = both B & S together                            */
                        else
                            if ( battr[0] != ' ' )
                                strlcat ( dcb, battr, sizeof(dcb) ); /* just the B|S if not 'R' - blank is not included      */

                        if ( pcchr[0] != ' ' )
                            strlcat ( dcb, pcchr, sizeof(dcb) );/* last is the printer carriage control type A|M        */
                                                                /* A = ANSI and M = Machine                             */
                        strlcat ( dcb, ",LRECL=", sizeof(dcb) );
                        sprintf ( tmp, "%d", atoi( rsize ) );
                        strlcat ( dcb, tmp, sizeof(dcb) );

                        strlcat ( dcb, ",BLKSIZE=", sizeof(dcb) );
                        if ( lbsiz[0] == '0' )
                            sprintf ( tmp, "%ld", atol( lbsiz ) );
                        else
                            sprintf ( tmp, "%d", atoi( bsize ) );
                        strlcat ( dcb, tmp, sizeof(dcb) );

                        strlcat ( dcb, ")", sizeof(dcb) );

                        printf ( "%-51s", dcb );

                        if ( mltv[0] == '1' || atoi( gMltVolSeq ) > 1 )
                            printf ( "\n%-4sTape is part %d of multi-volume set %s\n", "", atoi( gMltVolSeq ), gMltVolSet );

                        if ( rtech[0] == 'P' )
                            printf ( "%-3sCompression: IDRC", "" );

                        printf ( "\n" );
                    }
                    else
                        printf( "======================================"
                                "======================================"
                                "======================================"
                                "======================================\n" );
                }
                    break;

                default:
                    printf ( "%-4s %1d %-s\n", lLblType, *lLblNum, &gStdLblBuffer[4] );
                    break;
            }
        }
            rc = TRUE;
            break;

        case        3:
            printf ( "%-4s %1d %-s\n", lLblType, *lLblNum, &gStdLblBuffer[4] );
            rc = TRUE;
            break;

        default:
            rc = FALSE;
            break;
    }

    ZERO_OUT ( gStdLblBuffer, sizeof( gStdLblBuffer ) );
    return ( rc );

} /* end function Print_Standard_Labels */