int
main(
    int argc,
    char *argv[]
    )
{
    ULONG i;
    PSZ Psz;

    PPREFIX_TABLE_ENTRY PfxEntry;
    PPREFIX_NODE PfxNode;

    STRING String;

    //
    //  We're starting the test
    //

    DbgPrint("Start Prefix Test\n");

    //
    //  Calculate the alphabet size for use by AnotherPrefix
    //

    AlphabetLength = strlen(Alphabet);

    //
    //  Initialize the prefix table
    //

    PfxInitialize(&PrefixTable);

    //
    //  Insert the root prefix
    //

    RtlInitString( &Prefixes[i].String, "\\" );
    if (PfxInsertPrefix( &PrefixTable,
                         &Prefixes[0].String,
                         &Prefixes[0].PfxEntry )) {
        DbgPrint("Insert root prefix\n");
    } else {
        DbgPrint("error inserting root prefix\n");
    }

    //
    //  Insert prefixes
    //

    Seed = 0;

    for (i = 1, Psz = AnotherPrefix(3);
         (i < PREFIXES) && (Psz != NULL);
         i += 1, Psz = AnotherPrefix(3)) {

        DbgPrint("[0x%x] = ", i);
        DbgPrint("\"%s\"", Psz);

        RtlInitString(&Prefixes[i].String, Psz);

        if (PfxInsertPrefix( &PrefixTable,
                             &Prefixes[i].String,
                             &Prefixes[i].PfxEntry )) {

            DbgPrint(" inserted in table\n");

        } else {

            DbgPrint(" already in table\n");

        }

    }

    //
    //  Enumerate the prefix table
    //

    DbgPrint("Enumerate Prefix Table the first time\n");

    for (PfxEntry = PfxNextPrefix(&PrefixTable, TRUE);
         PfxEntry != NULL;
         PfxEntry = PfxNextPrefix(&PrefixTable, FALSE)) {

        PfxNode = CONTAINING_RECORD(PfxEntry, PREFIX_NODE, PfxEntry);

        DbgPrint("%s\n", PfxNode->String.Buffer);

    }

    DbgPrint("Start Prefix search 0x%x\n", NextBufferChar);

    //
    //  Search for prefixes
    //

    for (Psz = AnotherPrefix(4); Psz != NULL; Psz = AnotherPrefix(4)) {

        DbgPrint("0x%x ", NextBufferChar);

        RtlInitString(&String, Psz);

        PfxEntry = PfxFindPrefix( &PrefixTable, &String, FALSE );

        if (PfxEntry == NULL) {

            PfxEntry = PfxFindPrefix( &PrefixTable, &String, TRUE );

            if (PfxEntry == NULL) {

                DbgPrint("Not found      \"%s\"\n", Psz);

                NOTHING;

            } else {

                PfxNode = CONTAINING_RECORD(PfxEntry, PREFIX_NODE, PfxEntry);

                DbgPrint("Case blind     \"%s\" is \"%s\"\n", Psz, PfxNode->String.Buffer);

                PfxRemovePrefix( &PrefixTable, PfxEntry );

            }

        } else {

            PfxNode = CONTAINING_RECORD(PfxEntry, PREFIX_NODE, PfxEntry);

            DbgPrint(    "Case sensitive \"%s\" is \"%s\"\n", Psz, PfxNode->String.Buffer);

            if (PfxNode != &Prefixes[0]) {

                PfxRemovePrefix( &PrefixTable, PfxEntry );

            }

        }

    }

    //
    //  Enumerate the prefix table
    //

    DbgPrint("Enumerate Prefix Table a second time\n");

    for (PfxEntry = PfxNextPrefix(&PrefixTable, TRUE);
         PfxEntry != NULL;
         PfxEntry = PfxNextPrefix(&PrefixTable, FALSE)) {

        PfxNode = CONTAINING_RECORD(PfxEntry, PREFIX_NODE, PfxEntry);

        DbgPrint("%s\n", PfxNode->String.Buffer);

    }

    //
    //  Now enumerate and zero out the table
    //

    for (PfxEntry = PfxNextPrefix(&PrefixTable, TRUE);
         PfxEntry != NULL;
         PfxEntry = PfxNextPrefix(&PrefixTable, FALSE)) {

        PfxNode = CONTAINING_RECORD(PfxEntry, PREFIX_NODE, PfxEntry);

        DbgPrint("Delete %s\n", PfxNode->String.Buffer);

        PfxRemovePrefix( &PrefixTable, PfxEntry );

    }

    //
    //  Enumerate again but this time the table should be empty
    //

    for (PfxEntry = PfxNextPrefix(&PrefixTable, TRUE);
         PfxEntry != NULL;
         PfxEntry = PfxNextPrefix(&PrefixTable, FALSE)) {

        PfxNode = CONTAINING_RECORD(PfxEntry, PREFIX_NODE, PfxEntry);

        DbgPrint("This Node should be gone \"%s\"\n", PfxNode->String.Buffer);

    }

    DbgPrint("End PrefixTest()\n");

    return TRUE;
}