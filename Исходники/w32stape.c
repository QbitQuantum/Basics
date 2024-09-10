static
int w32_internal_mtop ( HANDLE hFile, U32* pStat, struct mtop* mtop, ifd_t ifd )
{
    int rc = 0;

    ASSERT( pStat && mtop );    // (sanity check)

    // General technique: do the i/o, save results, update the
    // device status (based on the results), then check results...

    switch ( mtop->mt_op )
    {
    case MTLOAD:    // (load media)
    {
        if ( 1 != mtop->mt_count )
        {
            errno = EINVAL;
            rc = -1;
        }
        else
        {
            do
            {
                errno = PrepareTape( hFile, TAPE_LOAD, FALSE );
                errno = w32_internal_rc ( pStat );
            }
            while ( EINTR == errno );
        }
    }
    break;

    case MTUNLOAD:  // (unload media)
    case MTOFFL:    // (make media offline (same as unload))
    {
        if ( 1 != mtop->mt_count )
        {
            errno = EINVAL;
            rc = -1;
        }
        else
        {
            do
            {
                errno = PrepareTape( hFile, TAPE_UNLOAD, FALSE );
                errno = w32_internal_rc ( pStat );
            }
            while ( EINTR == errno );
        }
    }
    break;

    case MTSEEK:    // (position media)
    {
        do
        {
            errno = SetTapePosition( hFile, TAPE_LOGICAL_BLOCK, 0, mtop->mt_count, 0, FALSE );
            errno = w32_internal_rc ( pStat );
        }
        while ( EINTR == errno );
    }
    break;

    case MTREW:     // (rewind)
    {
        if ( 1 != mtop->mt_count )
        {
            errno = EINVAL;
            rc = -1;
        }
        else
        {
            do
            {
                errno = SetTapePosition( hFile, TAPE_REWIND, 0, 0, 0, FALSE );
                errno = w32_internal_rc ( pStat );
            }
            while ( EINTR == errno );
        }
    }
    break;

    case MTFSF:     // (FORWARD  space FILE)
    case MTBSF:     // (BACKWARD space FILE)
    {
        if ( !mtop->mt_count )
        {
            errno = EINVAL;
            rc = -1;
        }
        else
        {
            LARGE_INTEGER liCount;

            liCount.QuadPart = mtop->mt_count;

            if ( MTBSF == mtop->mt_op )
                liCount.QuadPart = -liCount.QuadPart; // (negative == backwards)

            do
            {
                errno = SetTapePosition( hFile, TAPE_SPACE_FILEMARKS, 0, liCount.LowPart, liCount.HighPart, FALSE );
                errno = w32_internal_rc ( pStat );
            }
            while ( EINTR == errno );
        }
    }
    break;

    case MTFSR:     // (FORWARD  space BLOCK)
    case MTBSR:     // (BACKWARD space BLOCK)
    {
        if ( !mtop->mt_count )
        {
            errno = EINVAL;
            rc = -1;
        }
        else
        {
            LARGE_INTEGER liCount;

            liCount.QuadPart = mtop->mt_count;

            if ( MTBSR == mtop->mt_op )
                liCount.QuadPart = -liCount.QuadPart; // (negative == backwards)

            do
            {
                errno = SetTapePosition( hFile, TAPE_SPACE_RELATIVE_BLOCKS, 0, liCount.LowPart, liCount.HighPart, FALSE );
                errno = w32_internal_rc ( pStat );
            }
            while ( EINTR == errno );
        }
    }
    break;

    case MTSETBLK:  // (set blocksize)
    {
        TAPE_SET_MEDIA_PARAMETERS  media_parms;

        media_parms.BlockSize = mtop->mt_count;

        do
        {
            errno = SetTapeParameters( hFile, SET_TAPE_MEDIA_INFORMATION, &media_parms );
            errno = w32_internal_rc ( pStat );
        }
        while ( EINTR == errno );
    }
    break;

    case MTEOTWARN:   // (set EOT Warning Zone size in bytes)
    {
        TAPE_SET_DRIVE_PARAMETERS   set_drive_parms;

        set_drive_parms.ECC                = g_drive_parms[ifd].ECC;
        set_drive_parms.Compression        = g_drive_parms[ifd].Compression;
        set_drive_parms.DataPadding        = g_drive_parms[ifd].DataPadding;
        set_drive_parms.ReportSetmarks     = g_drive_parms[ifd].ReportSetmarks;
        set_drive_parms.EOTWarningZoneSize = mtop->mt_count;

        do
        {
            errno = SetTapeParameters( hFile, SET_TAPE_DRIVE_INFORMATION, &set_drive_parms );
            errno = w32_internal_rc ( pStat );
        }
        while ( EINTR == errno );
    }
    break;

    case MTWEOF:    // (write TAPEMARK)
    {
        if ( mtop->mt_count < 0 )
        {
            errno = EINVAL;
            rc = -1;
        }
        else
        {
            // PROGRAMMING NOTE: We prefer "long" filemarks over any other type
            // because, according to the SDK documentaion:
            //
            //    "A short filemark contains a short erase gap that cannot be
            //     overwritten unless the write operation is performed from the
            //     beginning of the partition or from an earlier long filemark."
            //
            //    "A long filemark contains a long erase gap that allows an
            //     application to position the tape at the beginning of the filemark
            //     and to overwrite the filemark and the erase gap."
            //
            // Thus if TAPE_LONG_FILEMARKS is not supported we try ONLY the generic
            // TAPE_FILEMARKS variety and return an error if that fails; we do NOT
            // ever attempt the TAPE_SHORT_FILEMARKS or TAPE_SETMARKS variety.

            DWORD  dwTapemarkType = TAPE_LONG_FILEMARKS;

            if ( !( g_drive_parms[ifd].FeaturesHigh & TAPE_DRIVE_WRITE_LONG_FMKS ) )
                dwTapemarkType = TAPE_FILEMARKS;

            do
            {
                errno = WriteTapemark( hFile, dwTapemarkType, mtop->mt_count, FALSE );
                errno = w32_internal_rc ( pStat );
            }
            while ( EINTR == errno );
        }
    }
    break;

    case MTERASE: // (write erase gap or erase entire tape (data security erase))
    {
        if (1
                && 0 != mtop->mt_count  // (0 == write erase gap at current position)
                && 1 != mtop->mt_count  // (1 == erases the remainder of entire tape)
           )
        {
            errno = EINVAL;
            rc = -1;
        }
        else
        {
            DWORD  dwEraseType  =
                mtop->mt_count ? TAPE_ERASE_LONG : TAPE_ERASE_SHORT;

            do
            {
                errno = EraseTape( hFile, dwEraseType, FALSE );
                errno = w32_internal_rc ( pStat );
            }
            while ( EINTR == errno );
        }
    }
    break;

    case MTNOP:         // (no operation)
    {
        errno = 0;
        rc = 0;
    }
    break;

    default:        // (invalid/unsupported tape operation)
    {
        errno = EINVAL;
        rc = -1;
    }
    break;
    }

    return (rc = (0 == errno || ENOSPC == errno) ? 0 : /* errno != 0 && errno != ENOSPC */ -1);
}