_WCRTLINK void  __F_NAME(_splitpath2,_wsplitpath2)( CHAR_TYPE const *inp, CHAR_TYPE *outp,
                     CHAR_TYPE **drive, CHAR_TYPE **path, CHAR_TYPE **fn, CHAR_TYPE **ext ) {
/*=====================================================================*/

    CHAR_TYPE const *dotp;
    CHAR_TYPE const *fnamep;
    CHAR_TYPE const *startp;
    UINT_WC_TYPE    ch;

    /* take apart specification like -> //0/hd/user/fred/filename.ext for QNX */
    /* take apart specification like -> \\disk2\fred\filename.ext for UNC names */
    /* take apart specification like -> c:\fred\filename.ext for DOS, OS/2 */

    /* process node/drive/UNC specification */
    startp = inp;
    if( IS_PC( inp[ 0 ] ) && IS_PC( inp[ 1 ] ) )
    {
        inp += 2;
        for( ;; ) {
            if( *inp == NULLCHAR )
                break;
            if( IS_PC( *inp ) )
                break;
            if( *inp == '.' )
                break;
#if defined( __WIDECHAR__ ) || defined( __UNIX__ )
            ++inp;
#else
            inp = (char *)_mbsinc( (unsigned char *)inp );
#endif
        }
        outp = pcopy( drive, outp, startp, inp );
#if !defined(__UNIX__)
    /* process drive specification */
    } else if( inp[ 0 ] != NULLCHAR && inp[ 1 ] == ':' ) {
        if( drive != NULL ) {
            *drive = outp;
            outp[ 0 ] = inp[ 0 ];
            outp[ 1 ] = ':';
            outp[ 2 ] = NULLCHAR;
            outp += 3;
        }
        inp += 2;
#endif
    } else if( drive != NULL ) {
        *drive = outp;
        *outp = NULLCHAR;
        ++outp;
    }

    /* process /user/fred/filename.ext for QNX */
    /* process \fred\filename.ext for DOS, OS/2 */
    /* process /fred/filename.ext for DOS, OS/2 */
    dotp = NULL;
    fnamep = inp;
    startp = inp;

    for( ;; ) {
#if defined( __WIDECHAR__ ) || defined( __UNIX__ )
        ch = *inp;
#else
        ch = _mbsnextc( (unsigned char *)inp );
#endif
        if( ch == 0 )
            break;
        if( ch == '.' ) {
            dotp = inp;
            ++inp;
            continue;
        }
#if defined( __WIDECHAR__ ) || defined( __UNIX__ )
        inp++;
#else
        inp = (char *)_mbsinc( (unsigned char *)inp );
#endif
        if( IS_PC( ch ) ) {
            fnamep = inp;
            dotp = NULL;
        }
    }
    outp = pcopy( path, outp, startp, fnamep );
    if( dotp == NULL )
        dotp = inp;
    outp = pcopy( fn, outp, fnamep, dotp );
    outp = pcopy( ext, outp, dotp, inp );
}