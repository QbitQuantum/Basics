/*
 * FUNCTION: Finds next file in the cabinet that matches a search criteria
 * ARGUMENTS:
 *     Search = Pointer to search structure
 * RETURNS:
 *     Status of operation
 */
ULONG
CabinetFindNext(PCAB_SEARCH Search)
{
    PCFFILE Prev;
    ANSI_STRING AnsiString;
    UNICODE_STRING UnicodeString;
    WCHAR FileName[MAX_PATH];

    if (wcscmp(Search->Cabinet, CabinetName) != 0)
    {
        /* restart search of cabinet has changed since last find */
        Search->File = 0;
    }

    if (!Search->File)
    {
        /* starting new search or cabinet */
        Search->File = (PCFFILE)(FileBuffer + PCABHeader->FileTableOffset);
        Search->Index = 0;
        Prev = 0;
    }
    else
        Prev = Search->File;

    while (TRUE)
    {
        /* look at each file in the archive and see if we found a match */
        if (Search->File->FolderIndex == 0xFFFD ||
            Search->File->FolderIndex == 0xFFFF)
        {
            /* skip files continued from previous cab */
            DPRINT("Skipping file (%s): FileOffset (0x%X), "
                   "LastFileOffset (0x%X)\n", (char *)(Search->File + 1),
                   Search->File->FileOffset, LastFileOffset);
        }
        else
        {
            // FIXME: check for match against search criteria
            if (Search->File != Prev)
            {
                if (Prev == NULL || Search->File->FolderIndex != Prev->FolderIndex)
                {
                    Search->CFData = NULL;
                    Search->Offset = 0;
                }
                
                /* don't match the file we started with */
                if (wcscmp(Search->Search, L"*") == 0)
                {
                    /* take any file */
                    break;
                }
                else
                {
                    /* otherwise, try to match the exact file name */
                    RtlInitAnsiString(&AnsiString, Search->File->FileName);
                    UnicodeString.Buffer = FileName;
                    UnicodeString.Buffer[0] = 0;
                    UnicodeString.Length = 0;
                    UnicodeString.MaximumLength = sizeof(FileName);
                    RtlAnsiStringToUnicodeString(&UnicodeString, &AnsiString, FALSE);
                    if (wcscmp(Search->Search, UnicodeString.Buffer) == 0)
                        break;
                }
            }
        }

        /* if we make it here we found no match, so move to the next file */
        Search->Index++;
        if (Search->Index >= PCABHeader->FileCount)
        {
            /* we have reached the end of this cabinet */
            DPRINT("End of cabinet reached\n");
            return CAB_STATUS_NOFILE;
        }
        else
            Search->File = (PCFFILE)(strchr((char *)(Search->File + 1), 0) + 1);
    }

    DPRINT("Found file %s\n", Search->File->FileName);
    return CAB_STATUS_SUCCESS;
}