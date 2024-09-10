/*
	ExpandVolume

	Sets the volume size in the volume header (and backup header) to a larger value,
	and resizes the filesystem within the volume (only NTFS supported)

	Parameters:

		hwndDlg : HWND
			[in] handle to progress dialog

		lpszVolume : char *
			[in] Pointer to a string that contains the path to the truecrypt volume

		pVolumePassword : Password *
			[in] Pointer to the volume password

		newHostSize : uint64
			[in] new value of the volume host size (can be zero for devices,
			     which means the volume should use all space of the host device)

		initFreeSpace : BOOL
			[in] if true, the new volume space will be initalized with random data

	Return value:

		int with Truecrypt error code (ERR_SUCCESS on success)

	Remarks: a lot of code is from TrueCrypt 'Common\Password.c' :: ChangePwd()

*/
static int ExpandVolume (HWND hwndDlg, wchar_t *lpszVolume, Password *pVolumePassword, int VolumePkcs5, int VolumePim, uint64 newHostSize, BOOL initFreeSpace)
{
    int nDosLinkCreated = 1, nStatus = ERR_OS_ERROR;
    wchar_t szDiskFile[TC_MAX_PATH], szCFDevice[TC_MAX_PATH];
    wchar_t szDosDevice[TC_MAX_PATH];
    char buffer[TC_VOLUME_HEADER_EFFECTIVE_SIZE];
    PCRYPTO_INFO cryptoInfo = NULL, ci = NULL;
    void *dev = INVALID_HANDLE_VALUE;
    DWORD dwError;
    BOOL bDevice;
    uint64 hostSize=0, newDataAreaSize, currentVolSize;
    DWORD HostSectorSize;
    FILETIME ftCreationTime;
    FILETIME ftLastWriteTime;
    FILETIME ftLastAccessTime;
    BOOL bTimeStampValid = FALSE;
    LARGE_INTEGER headerOffset;
    BOOL backupHeader;
    byte *wipeBuffer = NULL;
    uint32 workChunkSize = TC_VOLUME_HEADER_GROUP_SIZE;

    if (pVolumePassword->Length == 0) return -1;

    WaitCursor ();

    CreateFullVolumePath (szDiskFile, sizeof(szDiskFile), lpszVolume, &bDevice);

    if (bDevice == FALSE)
    {
        wcscpy (szCFDevice, szDiskFile);
    }
    else
    {
        nDosLinkCreated = FakeDosNameForDevice (szDiskFile, szDosDevice, sizeof(szDosDevice), szCFDevice, sizeof(szCFDevice), FALSE);

        if (nDosLinkCreated != 0) // note: nStatus == ERR_OS_ERROR
            goto error;
    }

    dev = CreateFile (szCFDevice, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    if (dev == INVALID_HANDLE_VALUE)
        goto error;

    if (bDevice)
    {
        /* This is necessary to determine the hidden volume header offset */

        if (dev == INVALID_HANDLE_VALUE)
        {
            goto error;
        }
        else
        {
            PARTITION_INFORMATION diskInfo;
            DWORD dwResult;
            BOOL bResult;

            bResult = GetPartitionInfo (lpszVolume, &diskInfo);

            if (bResult)
            {
                hostSize = diskInfo.PartitionLength.QuadPart;
                HostSectorSize = TC_SECTOR_SIZE_FILE_HOSTED_VOLUME; //TO DO: get the real host disk sector size
            }
            else
            {
                DISK_GEOMETRY driveInfo;

                bResult = DeviceIoControl (dev, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0,
                                           &driveInfo, sizeof (driveInfo), &dwResult, NULL);

                if (!bResult)
                    goto error;

                hostSize = driveInfo.Cylinders.QuadPart * driveInfo.BytesPerSector *
                           driveInfo.SectorsPerTrack * driveInfo.TracksPerCylinder;

                HostSectorSize = driveInfo.BytesPerSector;
            }

            if (hostSize == 0)
            {
                nStatus = ERR_VOL_SIZE_WRONG;
                goto error;
            }
        }
    }
    else
    {
        LARGE_INTEGER fileSize;
        if (!GetFileSizeEx (dev, &fileSize))
        {
            nStatus = ERR_OS_ERROR;
            goto error;
        }

        hostSize = fileSize.QuadPart;
        HostSectorSize = TC_SECTOR_SIZE_FILE_HOSTED_VOLUME; //TO DO: get the real host disk sector size
    }

    if (Randinit ())
    {
        if (CryptoAPILastError == ERROR_SUCCESS)
            nStatus = ERR_RAND_INIT_FAILED;
        else
            nStatus = ERR_CAPI_INIT_FAILED;
        goto error;
    }

    if (!bDevice && bPreserveTimestamp)
    {
        /* Remember the container modification/creation date and time, (used to reset file date and time of
        file-hosted volumes after password change (or attempt to), in order to preserve plausible deniability
        of hidden volumes (last password change time is stored in the volume header). */

        if (GetFileTime ((HANDLE) dev, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime) == 0)
        {
            bTimeStampValid = FALSE;
            MessageBoxW (hwndDlg, GetString ("GETFILETIME_FAILED_PW"), lpszTitle, MB_OK | MB_ICONEXCLAMATION);
        }
        else
            bTimeStampValid = TRUE;
    }

    // Seek the volume header
    headerOffset.QuadPart = TC_VOLUME_HEADER_OFFSET;

    if (!SetFilePointerEx ((HANDLE) dev, headerOffset, NULL, FILE_BEGIN))
    {
        nStatus = ERR_OS_ERROR;
        goto error;
    }

    /* Read in volume header */
    nStatus = _lread ((HFILE) dev, buffer, sizeof (buffer));
    if (nStatus != sizeof (buffer))
    {
        // Windows may report EOF when reading sectors from the last cluster of a device formatted as NTFS
        memset (buffer, 0, sizeof (buffer));
    }

    /* Try to decrypt the header */

    nStatus = ReadVolumeHeader (FALSE, buffer, pVolumePassword, VolumePkcs5, VolumePim, FALSE, &cryptoInfo, NULL);
    if (nStatus == ERR_CIPHER_INIT_WEAK_KEY)
        nStatus = 0;	// We can ignore this error here

    if (nStatus != 0)
    {
        cryptoInfo = NULL;
        goto error;
    }

    if (cryptoInfo->HeaderFlags & TC_HEADER_FLAG_ENCRYPTED_SYSTEM)
    {
        nStatus = ERR_SYS_HIDVOL_HEAD_REENC_MODE_WRONG;
        goto error;
    }

    if (bDevice && newHostSize == 0)
    {
        // this means we shall take all host space as new volume size
        newHostSize = hostSize;
    }

    if ( newHostSize % cryptoInfo->SectorSize != 0  || newHostSize > TC_MAX_VOLUME_SIZE || (bDevice && newHostSize > hostSize) )
    {
        // 1. must be multiple of sector size
        // 2. truecrypt volume size limit
        // 3. for devices volume size can't be larger than host size
        cryptoInfo = NULL;
        nStatus = ERR_PARAMETER_INCORRECT;
        goto error;
    }

    newDataAreaSize = GetVolumeDataAreaSize (newHostSize, cryptoInfo->LegacyVolume);

    if (cryptoInfo->LegacyVolume)
    {
        if (bDevice)
        {
            if (initFreeSpace)
            {
                // unsupported
                cryptoInfo = NULL;
                nStatus = ERR_PARAMETER_INCORRECT;
                goto error;
            }
            else
            {
                // note: dummy value (only used for parameter checks)
                cryptoInfo->VolumeSize.Value = newDataAreaSize - TC_MINVAL_FS_EXPAND;
            }
        }
        else
        {
            cryptoInfo->VolumeSize.Value = GetVolumeDataAreaSize (hostSize, TRUE);
        }
    }

    currentVolSize = GetVolumeSizeByDataAreaSize (cryptoInfo->VolumeSize.Value, cryptoInfo->LegacyVolume);

    if ( newDataAreaSize < cryptoInfo->VolumeSize.Value + TC_MINVAL_FS_EXPAND )
    {
        // shrinking a volume or enlarging by less then TC_MINVAL_FS_EXPAND is not allowed
        cryptoInfo = NULL;
        nStatus = ERR_PARAMETER_INCORRECT;
        goto error;
    }

    InitProgressBar ( newHostSize, currentVolSize, FALSE, FALSE, FALSE, TRUE);

    if (bVolTransformThreadCancel)
    {
        SetLastError(0);
        nStatus = ERR_USER_ABORT;
        goto error;
    }

    if (!bDevice) {
        LARGE_INTEGER liNewSize;

        liNewSize.QuadPart=(LONGLONG)newHostSize;

        // Preallocate the file
        if (!SetFilePointerEx (dev, liNewSize, NULL, FILE_BEGIN)
                || !SetEndOfFile (dev)
                || SetFilePointer (dev, 0, NULL, FILE_BEGIN) != 0)
        {
            nStatus = ERR_OS_ERROR;
            goto error;
        }
    }

    if (initFreeSpace)
    {
        uint64 startSector;
        int64 num_sectors;

        // fill new space with random data
        startSector = currentVolSize/HostSectorSize ;
        num_sectors = (newHostSize/HostSectorSize) - startSector;

        if (bDevice && !StartFormatWriteThread())
        {
            nStatus = ERR_OS_ERROR;
            goto error;
        }

        DebugAddProgressDlgStatus(hwndDlg, L"Writing random data to new space ...\r\n");

        SetFormatSectorSize(HostSectorSize);
        nStatus = FormatNoFs (hwndDlg, startSector, num_sectors, dev, cryptoInfo, FALSE);

        dwError = GetLastError();
        StopFormatWriteThread();
        SetLastError (dwError);
    }
    else
    {
        UpdateProgressBar(newHostSize);
    }

    if (nStatus != ERR_SUCCESS)
    {
        dwError = GetLastError();
        DebugAddProgressDlgStatus(hwndDlg, L"Error: failed to write random data ...\r\n");
        if ( !bDevice ) {
            // restore original size of the container file
            LARGE_INTEGER liOldSize;
            liOldSize.QuadPart=(LONGLONG)hostSize;
            if (!SetFilePointerEx (dev, liOldSize, NULL, FILE_BEGIN) || !SetEndOfFile (dev))
            {
                DebugAddProgressDlgStatus(hwndDlg, L"Warning: failed to restore original size of the container file\r\n");
            }
        }
        SetLastError (dwError);
        goto error;
    }

    RandSetHashFunction (cryptoInfo->pkcs5);

    // Re-encrypt the volume header forn non-legacy volumes: backup header first
    backupHeader = TRUE;
    headerOffset.QuadPart = TC_VOLUME_HEADER_OFFSET + newHostSize - TC_VOLUME_HEADER_GROUP_SIZE;

    /* note: updating the header is not neccessary for legay volumes */
    while ( !cryptoInfo->LegacyVolume )
    {
        if (backupHeader)
            DebugAddProgressDlgStatus(hwndDlg, L"Writing re-encrypted backup header ...\r\n");
        else
            DebugAddProgressDlgStatus(hwndDlg, L"Writing re-encrypted primary header ...\r\n");

        // Prepare new volume header
        nStatus = CreateVolumeHeaderInMemory (hwndDlg, FALSE,
                                              buffer,
                                              cryptoInfo->ea,
                                              cryptoInfo->mode,
                                              pVolumePassword,
                                              cryptoInfo->pkcs5,
                                              VolumePim,
                                              (char*)(cryptoInfo->master_keydata),
                                              &ci,
                                              newDataAreaSize,
                                              0, // hiddenVolumeSize
                                              cryptoInfo->EncryptedAreaStart.Value,
                                              newDataAreaSize,
                                              cryptoInfo->RequiredProgramVersion,
                                              cryptoInfo->HeaderFlags,
                                              cryptoInfo->SectorSize,
                                              TRUE ); // use slow poll

        if (ci != NULL)
            crypto_close (ci);

        if (nStatus != 0)
            goto error;

        if (!SetFilePointerEx ((HANDLE) dev, headerOffset, NULL, FILE_BEGIN))
        {
            nStatus = ERR_OS_ERROR;
            goto error;
        }

        nStatus = _lwrite ((HFILE) dev, buffer, TC_VOLUME_HEADER_EFFECTIVE_SIZE);
        if (nStatus != TC_VOLUME_HEADER_EFFECTIVE_SIZE)
        {
            nStatus = ERR_OS_ERROR;
            goto error;
        }

        if ( ( backupHeader && !initFreeSpace )
                || ( bDevice
                     && !cryptoInfo->LegacyVolume
                     && !cryptoInfo->hiddenVolume
                     && cryptoInfo->HeaderVersion == 4	// BUG in TrueCrypt: doing this only for v4 make no sense
                     && (cryptoInfo->HeaderFlags & TC_HEADER_FLAG_NONSYS_INPLACE_ENC) != 0
                     && (cryptoInfo->HeaderFlags & ~TC_HEADER_FLAG_NONSYS_INPLACE_ENC) == 0 )
           )
        {
            //DebugAddProgressDlgStatus(hwndDlg, L"WriteRandomDataToReservedHeaderAreas() ...\r\n");
            nStatus = WriteRandomDataToReservedHeaderAreas (hwndDlg, dev, cryptoInfo, newDataAreaSize, !backupHeader, backupHeader);
            if (nStatus != ERR_SUCCESS)
                goto error;
        }

        FlushFileBuffers (dev);

        if (!backupHeader)
            break;

        backupHeader = FALSE;
        headerOffset.QuadPart = TC_VOLUME_HEADER_OFFSET; // offset for main header
    }

    /* header successfully updated */
    nStatus = ERR_SUCCESS;

    if (bVolTransformThreadCancel)
    {
        nStatus = ERR_USER_ABORT;
        goto error;
    }

    /* wipe old backup header */
    if ( !cryptoInfo->LegacyVolume )
    {
        byte wipeRandChars [TC_WIPE_RAND_CHAR_COUNT];
        byte wipeRandCharsUpdate [TC_WIPE_RAND_CHAR_COUNT];
        byte wipePass;
        UINT64_STRUCT unitNo;
        LARGE_INTEGER offset;
        WipeAlgorithmId wipeAlgorithm = TC_WIPE_35_GUTMANN;

        if (	!RandgetBytes (hwndDlg, wipeRandChars, TC_WIPE_RAND_CHAR_COUNT, TRUE)
                || !RandgetBytes (hwndDlg, wipeRandCharsUpdate, TC_WIPE_RAND_CHAR_COUNT, TRUE)
           )
        {
            nStatus = ERR_OS_ERROR;
            goto error;
        }

        DebugAddProgressDlgStatus(hwndDlg, L"Wiping old backup header ...\r\n");

        wipeBuffer = (byte *) TCalloc (workChunkSize);
        if (!wipeBuffer)
        {
            nStatus = ERR_OUTOFMEMORY;
            goto error;
        }

        offset.QuadPart = currentVolSize - TC_VOLUME_HEADER_GROUP_SIZE;
        unitNo.Value = offset.QuadPart;

        for (wipePass = 1; wipePass <= GetWipePassCount (wipeAlgorithm); ++wipePass)
        {
            if (!WipeBuffer (wipeAlgorithm, wipeRandChars, wipePass, wipeBuffer, workChunkSize))
            {
                ULONG i;
                for (i = 0; i < workChunkSize; ++i)
                {
                    wipeBuffer[i] = wipePass;
                }

                EncryptDataUnits (wipeBuffer, &unitNo, workChunkSize / ENCRYPTION_DATA_UNIT_SIZE, cryptoInfo);
                memcpy (wipeRandCharsUpdate, wipeBuffer, sizeof (wipeRandCharsUpdate));
            }

            if ( !SetFilePointerEx (dev, offset, NULL, FILE_BEGIN)
                    || _lwrite ((HFILE)dev, (LPCSTR)wipeBuffer, workChunkSize) == HFILE_ERROR
               )
            {
                // Write error
                DebugAddProgressDlgStatus(hwndDlg, L"Warning: Failed to wipe old backup header\r\n");
                MessageBoxW (hwndDlg, L"WARNING: Failed to wipe old backup header!\n\nIt may be possible to use the current volume password to decrypt the old backup header even after a future password change.\n", lpszTitle, MB_OK | MB_ICONEXCLAMATION);
                if (wipePass == 1)
                    continue; // retry once
                // non-critical error - it's better to continue
                nStatus = ERR_SUCCESS;
                goto error;
            }
            FlushFileBuffers(dev);
            // we don't check FlushFileBuffers() return code, because it fails for devices
            // (same implementation in password.c - a bug or not ???)
        }

        burn (wipeRandChars, TC_WIPE_RAND_CHAR_COUNT);
        burn (wipeRandCharsUpdate, TC_WIPE_RAND_CHAR_COUNT);
    }

error:
    dwError = GetLastError ();

    if (wipeBuffer)
    {
        burn (wipeBuffer, workChunkSize);
        TCfree (wipeBuffer);
        wipeBuffer = NULL;
    }

    burn (buffer, sizeof (buffer));

    if (cryptoInfo != NULL)
        crypto_close (cryptoInfo);

    if (bTimeStampValid)
    {
        // Restore the container timestamp (to preserve plausible deniability of possible hidden volume).
        if (SetFileTime (dev, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime) == 0)
            MessageBoxW (hwndDlg, GetString ("SETFILETIME_FAILED_PW"), lpszTitle, MB_OK | MB_ICONEXCLAMATION);
    }

    if (dev != INVALID_HANDLE_VALUE)
        CloseHandle ((HANDLE) dev);

    if (nDosLinkCreated == 0)
        RemoveFakeDosName (szDiskFile, szDosDevice);

    RandStop (FALSE);

    if (bVolTransformThreadCancel)
        nStatus = ERR_USER_ABORT;

    SetLastError (dwError);

    if (nStatus == ERR_SUCCESS)
    {
        nStatus = ExtendFileSystem (hwndDlg, lpszVolume, pVolumePassword, VolumePkcs5, VolumePim, newDataAreaSize);
    }

    return nStatus;
}