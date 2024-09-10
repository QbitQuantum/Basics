VOID
DrawFileSystemList(
    IN PFILE_SYSTEM_LIST List)
{
    PLIST_ENTRY ListEntry;
    PFILE_SYSTEM_ITEM Item;
    COORD coPos;
    DWORD Written;
    ULONG Index = 0;
    CHAR Buffer[70];

    ListEntry = List->ListHead.Flink;
    while (ListEntry != &List->ListHead)
    {
        Item = CONTAINING_RECORD(ListEntry, FILE_SYSTEM_ITEM, ListEntry);

        coPos.X = List->Left;
        coPos.Y = List->Top + (SHORT)Index;
        FillConsoleOutputAttribute(StdOutput,
                                   FOREGROUND_WHITE | BACKGROUND_BLUE,
                                   sizeof(Buffer),
                                   coPos,
                                   &Written);
        FillConsoleOutputCharacterA(StdOutput,
                                    ' ',
                                    sizeof(Buffer),
                                    coPos,
                                    &Written);

        if (Item->FileSystemName)
        {
            if (Item->QuickFormat)
                snprintf(Buffer, sizeof(Buffer), MUIGetString(STRING_FORMATDISK1), Item->FileSystemName);
            else
                snprintf(Buffer, sizeof(Buffer), MUIGetString(STRING_FORMATDISK2), Item->FileSystemName);
        }
        else
            snprintf(Buffer, sizeof(Buffer), MUIGetString(STRING_KEEPFORMAT));

        if (ListEntry == &List->Selected->ListEntry)
            CONSOLE_SetInvertedTextXY(List->Left,
                                      List->Top + (SHORT)Index,
                                      Buffer);
        else
            CONSOLE_SetTextXY(List->Left,
                              List->Top + (SHORT)Index,
                              Buffer);
        Index++;
        ListEntry = ListEntry->Flink;
    }
}