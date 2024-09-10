static
VOID
DrawListEntries(
    PGENERIC_LIST GenericList)
{
    PGENERIC_LIST_ENTRY ListEntry;
    PLIST_ENTRY Entry;
    COORD coPos;
    DWORD Written;
    USHORT Width;

    coPos.X = GenericList->Left + 1;
    coPos.Y = GenericList->Top + 1;
    Width = GenericList->Right - GenericList->Left - 1;

    Entry = GenericList->FirstShown;
    while (Entry != &GenericList->ListHead)
    {
        ListEntry = CONTAINING_RECORD (Entry, GENERIC_LIST_ENTRY, Entry);

        if (coPos.Y == GenericList->Bottom)
            break;
        GenericList->LastShown = Entry;

        FillConsoleOutputAttribute (StdOutput,
                                    (GenericList->CurrentEntry == ListEntry) ?
                                    FOREGROUND_BLUE | BACKGROUND_WHITE :
                                    FOREGROUND_WHITE | BACKGROUND_BLUE,
                                    Width,
                                    coPos,
                                    &Written);

        FillConsoleOutputCharacterA (StdOutput,
                                     ' ',
                                     Width,
                                     coPos,
                                     &Written);

        coPos.X++;
        WriteConsoleOutputCharacterA (StdOutput,
                                      ListEntry->Text,
                                      min (strlen(ListEntry->Text), (SIZE_T)Width - 2),
                                      coPos,
                                      &Written);
        coPos.X--;

        coPos.Y++;
        Entry = Entry->Flink;
    }

    while (coPos.Y < GenericList->Bottom)
    {
        FillConsoleOutputAttribute (StdOutput,
                                    FOREGROUND_WHITE | BACKGROUND_BLUE,
                                    Width,
                                    coPos,
                                    &Written);

        FillConsoleOutputCharacterA (StdOutput,
                                     ' ',
                                     Width,
                                     coPos,
                                     &Written);
        coPos.Y++;
    }
}