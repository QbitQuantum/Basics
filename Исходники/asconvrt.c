void
AsInsertPrefix (
    char                    *Buffer,
    char                    *Keyword,
    UINT8                   Type)
{
    char                    *SubString;
    char                    *SubBuffer;
    char                    *EndKeyword;
    int                     StrLength;
    int                     InsertLength;
    char                    *InsertString;
    int                     TrailingSpaces;
    char                    LowerKeyword[128];
    int                     KeywordLength;


    switch (Type)
    {
    case SRC_TYPE_STRUCT:
        InsertString = "struct ";
        break;

    case SRC_TYPE_UNION:
        InsertString = "union ";
        break;

    default:
        return;
    }

    strcpy (LowerKeyword, Keyword);
    strlwr (LowerKeyword);

    SubBuffer = Buffer;
    SubString = Buffer;
    InsertLength = strlen (InsertString);
    KeywordLength = strlen (Keyword);


    while (SubString)
    {
        /* Find an instance of the keyword */

        SubString = strstr (SubBuffer, LowerKeyword);

        if (!SubString)
        {
            return;
        }

        SubBuffer = SubString;

        /* Must be standalone word, not a substring */

        if (AsMatchExactWord (SubString, KeywordLength))
        {
            /* Make sure the keyword isn't already prefixed with the insert */

            if (!strncmp (SubString - InsertLength, InsertString, InsertLength))
            {
                /* Add spaces if not already at the end-of-line */

                if (*(SubBuffer + KeywordLength) != '\n')
                {
                    /* Already present, add spaces after to align structure members */

#if 0
/* ONLY FOR C FILES */
                    AsInsertData (SubBuffer + KeywordLength, "        ", 8);
#endif
                }
                goto Next;
            }

            /* Make sure the keyword isn't at the end of a struct/union */
            /* Note: This code depends on a single space after the brace */

            if (*(SubString - 2) == '}')
            {
                goto Next;
            }

            /* Prefix the keyword with the insert string */

            Gbl_MadeChanges = TRUE;
            StrLength = strlen (SubString);

            /* Is there room for insertion */

            EndKeyword = SubString + strlen (LowerKeyword);

            TrailingSpaces = 0;
            while (EndKeyword[TrailingSpaces] == ' ')
            {
                TrailingSpaces++;
            }

            /*
             * Use "if (TrailingSpaces > 1)" if we want to ignore casts
             */
            SubBuffer = SubString + InsertLength;

            if (TrailingSpaces > InsertLength)
            {
                /* Insert the keyword */

                memmove (SubBuffer, SubString, KeywordLength);

                /* Insert the keyword */

                memmove (SubString, InsertString, InsertLength);
            }
            else
            {
                AsInsertData (SubString, InsertString, InsertLength);
            }
        }

Next:
        SubBuffer += KeywordLength;
    }
}