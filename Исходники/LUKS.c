// ----------------------------------------------------------------------------
BOOL LUKS_IdentifyCypher(
    char* cypherName,
    int keySizeBits,
    char* cypherMode,
    BOOL baseIVCypherOnHashLength,

    WCHAR *cypherKernelModeDeviceName,
    GUID* cypherGUID,
    SECTOR_IV_GEN_METHOD* sectorIVGenMethod,
    WCHAR *IVHashKernelModeDeviceName,
    GUID* IVHashGUID,
    WCHAR *IVCypherKernelModeDeviceName,
    GUID* IVCypherGUID
)
{
    BOOL allOK;
    CYPHER_MODE currCypherMode;
    CYPHER_MODE useCypherMode;
    char* IVGenMethod;
    HASH IVHashDetails;
    char ucCypherMode[LUKS_CIPHERMODE_L];
    char ucCypherName[LUKS_CIPHERNAME_L];
    char tmpUCtestMode[LUKS_CIPHERMODE_L];
    char* tmpPtr;
    WCHAR strMode_WCHAR[10];  // Enough to hold any cypher mode as a string
    char strMode_char[10];  // Enough to hold any cypher mode as a string

    BOOL gotImplDetails;

    int countImplCypher = 0;
    DRIVER_AND_ALG* implCypher = NULL;  // Array of options
    int countImplHash = 0;
    DRIVER_AND_ALG* implHash = NULL;  // Array of options


    allOK = TRUE;

    gotImplDetails = FALSE;

    // Standardise to uppercase; removes any potential problems with case
    // sensitivity
    SDUstrtoupper(ucCypherMode, cypherMode);
    SDUstrtoupper(ucCypherName, cypherName);


    // Detect IV generation method
    // Examples: ecb
    //           cbc-plain
    //           lrw-plain
    //           cbc-essiv:sha256
    // The stuff before the "-" is the cypher mode; the stuff after is the IV
    // generation
    // Note: ESSIV is NOT specified in the LUKS specification, but LUKS implements
    //       this anyway as "-essiv:<hash>"
    if (allOK) 
        {
        // Fallback to none... (e.g. ECB)
        *sectorIVGenMethod = SCTRIVGEN_NONE;
        wcscpy(IVHashKernelModeDeviceName, TEXT(""));
        *IVHashGUID = FREEOTFE_NULL_GUID;

        tmpPtr = strstr(ucCypherMode, "-");
        if (tmpPtr != NULL)
            {
            tmpPtr[0] = 0;  // Replace "-" with terminating NULL for ucCypherMode
            // tick on a char to point to IV generation method
            IVGenMethod = &(tmpPtr[1]);

            // Search for "-plain64" and strip off cypher mode
            SDUstrtoupper(tmpUCtestMode, PLAIN64_IV);
            tmpPtr = strstr(IVGenMethod, tmpUCtestMode);
            if (tmpPtr != NULL)
                {
                *sectorIVGenMethod = SCTRIVGEN_64BIT_SECTOR_ID;
                }
            else
                {
            // Search for "-plain" and strip off cypher mode
            SDUstrtoupper(tmpUCtestMode, PLAIN_IV);
            tmpPtr = strstr(IVGenMethod, tmpUCtestMode);
            if (tmpPtr != NULL)
                {
                *sectorIVGenMethod = SCTRIVGEN_32BIT_SECTOR_ID;
                }
                }

            // Search for "-essiv" and strip off cypher mode
            SDUstrtoupper(tmpUCtestMode, ESSIV_IV);
            tmpPtr = strstr(IVGenMethod, tmpUCtestMode);
            if (tmpPtr != NULL)
                {
                *sectorIVGenMethod = SCTRIVGEN_ESSIV;

                // Get the hash
                tmpPtr = strstr(IVGenMethod, ":");
                allOK = (tmpPtr != NULL);
                if (allOK)
                    {
                    tmpPtr = &(tmpPtr[1]);  // Move on 1 char
                    allOK = LUKS_IdentifyHash(
                                              tmpPtr,
                                              IVHashKernelModeDeviceName,
                                              IVHashGUID
                                             );
                    }

                }

            // Search for "-benbi" and strip off cypher mode
            SDUstrtoupper(tmpUCtestMode, BENBI_IV);
            tmpPtr = strstr(IVGenMethod, tmpUCtestMode);
            if (tmpPtr != NULL)
                {
                *sectorIVGenMethod = SCTRIVGEN_NONE;

                // Get the hash
                tmpPtr = strstr(IVGenMethod, ":");
                // Optional/not needed for "benbi"?
                if (tmpPtr != NULL)
                    {
                    tmpPtr = &(tmpPtr[1]);  // Move on 1 char
                    allOK = LUKS_IdentifyHash(
                                tmpPtr,
                                IVHashKernelModeDeviceName,
                                IVHashGUID
                                );
                    }
                }

            }
        }

    // Determine cypher mode
    useCypherMode = CYPHER_MODE_UNKNOWN;
    if (allOK)
        {
        for (
            currCypherMode = _CYPHER_MODE_FIRST; 
            currCypherMode <= _CYPHER_MODE_LAST;
            currCypherMode++
            )
            {
            // Convert cypher mode to simple char text representation, in uppercase
            driver_CypherPrettyprintAlgMode(currCypherMode, strMode_WCHAR);
            memset(strMode_char, 0, sizeof(strMode_char));
            wcstombs(strMode_char, strMode_WCHAR, wcslen(strMode_WCHAR));
            SDUstrtoupper(strMode_char, strMode_char);

            if (strcmp(strMode_char, ucCypherMode) == 0)
                {
                useCypherMode = currCypherMode;
                break;
                }

            }

        allOK = (useCypherMode != CYPHER_MODE_UNKNOWN);
        }

    // Obtain details of all cyphers...
    if (allOK)
        {
        gotImplDetails = driver_GetAllAlgorithmDriverOptions(
                                &countImplHash,
                                &implHash,

                                &countImplCypher,
                                &implCypher,

                                TRUE
                                );
        }


    // Given the information we've determined, identify the FreeOTFE driver to
    // map the details to
    if (allOK)
        {
        allOK = LUKS_IdentifyCypher_SearchCyphers(
                                countImplCypher,
                                implCypher,
                                cypherName,
                                keySizeBits,
                                useCypherMode,
                                cypherKernelModeDeviceName,
                                cypherGUID
                                );
        }

    // Sort out the IV cypher driver
    if (allOK)
        {
        wcscpy(IVCypherKernelModeDeviceName, cypherKernelModeDeviceName);
        *IVCypherGUID = *cypherGUID;

        // Because of a bug in dm-crypt, the cypher used to generate ESSIV IVs may
        // ***NOT*** be the same cypher as used for the bulk encryption of data
        // This is because it passes the IV hash's length to the cypher when it
        // creates the ESSIV cypher - as a result, the ESSIV cypher may have a
        // different keylength to the bulk encryption cypher
        if (
            (baseIVCypherOnHashLength) &&
            (*sectorIVGenMethod == SCTRIVGEN_ESSIV)
            ) 
            {
            allOK = driver_HashGetImplDetails(
                                IVHashKernelModeDeviceName,
                                IVHashGUID,
                                &IVHashDetails
                                );

            if (allOK)
                {
                allOK = LUKS_IdentifyCypher_SearchCyphers(
                                    countImplCypher,
                                    implCypher,
                                    cypherName,
                                    IVHashDetails.Length,
                                    useCypherMode,
                                    IVCypherKernelModeDeviceName,
                                    IVCypherGUID
                                    );
                }
            }

        }

    if (gotImplDetails) 
        {
        driver_FreeAllAlgorithmDriverOptions(
                        &countImplHash,
                        &implHash,

                        &countImplCypher,
                        &implCypher
                        );
        }

    return allOK;
}