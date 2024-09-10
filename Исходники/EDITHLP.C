/****************************************************************************
 * Creator: T. M. Farrington
 * Purpose: To search a binary file that contains command syntaxes.
 *
 * Inputs:  One binary file, the name of which is defined in the include file.
 *          Character pointer to the function name to be looked up.
 *          Character pointer to a buffer where the full command syntax will
 *             be placed if it is found.
 *          Maximum string size that the buffer can receive.
 *
 * Outputs: Return TRUE if search was successful, FALSE if not.
 *          If TRUE, places full command syntax in the buffer.
 *
 ****************************************************************************/
int W_EXPORT KpeGetKALHelp(LPSTR fnameptr, LPSTR buffer, int maxsiz)
{
    FILE *finptr;
    int iFile;
    OFSTRUCT of;
    char pFullPath[FILENAME_MAX];
    unsigned short csfname = lstrlen(fnameptr) + 1;
    unsigned short ssfname, ssrecord;
    unsigned short found = FALSE;

    /* First look for the file in KAPPA's system directory. *
     * If not there, then use the PATH.                     */
    KppGetSystemDirectory(pFullPath, FILENAME_MAX);
    strncat(pFullPath, binary_file, FILENAME_MAX - strlen(pFullPath) - 1);
    if ((iFile = OpenFile(pFullPath, &of, OF_READ)) == -1)
        iFile = OpenFile(binary_file, &of, OF_READ);

    if ((iFile == -1) || ((finptr = fdopen(iFile, "rb")) == NULL))
    {
        RegisterKappaMessage(IDE_FCANTOPEN,
                             KppAddAtom(binary_file), NULLID, NULLID);
        KppIncrementPopupCountCB(EDITW);
        PostKappaMessage();
        KppDecrementPopupCountCB(EDITW);
        return FALSE;
    }

    rewind(finptr);

    /* While not found, get the two string length values (2 bytes each)
     * at the begining of the record. 
     */
    while (!found)
    {
        fread(&ssfname, 2, 1, finptr);
        if (feof(finptr))
            break;

        fread(&ssrecord, 2, 1, finptr);
        if (feof(finptr))
            break;

        /* If the size of the parameter function name ==
            * size of the scanned function name,
                */
        if (csfname == ssfname)
        {
            char data[MAX_RECORD_LENGTH];

            /* then read the function name and if the strings match, */
            if ((fread(data, ssfname, 1, finptr) != NULL) &&
                (!lstrcmp(fnameptr, data)))
            {
                /* get the rest of the record and concatenate both strings
                    into the output file,
                        RBP: Do not concatenate */
                /* kstrcpy (buffer, data, maxsiz); */
                if (fread(data, ssrecord - ssfname - 4, 1, finptr) != NULL)
                    _fstrncpy(buffer, data, maxsiz);

                /* Stop the search. */
                found = TRUE;
            }
            else
                /* otherwise advance the file pointer to the next record.*/
                fseek(finptr, (long) ssrecord - 4 - ssfname, SEEK_CUR);
        }
        else                        /* otherwise advance the file pointer to the next record. */
            fseek(finptr, (long) ssrecord - 4, SEEK_CUR);
    }

    fclose(finptr);

    if (!found && (KppGetKalFunctionSyntaxCB(KppCheckAtom(fnameptr),
                                             buffer, maxsiz) != -1 ||
                   KppGetDLLFunctionSyntax(fnameptr, buffer, maxsiz) != -1))
        found = TRUE;

    return found;
}