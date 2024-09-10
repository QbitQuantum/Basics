LONG CED6AsDecompiler::DumpToFile(ED6_ACTION_SCRIPT_INFO *pAsInfo, LPWSTR pszAsFile, LPWSTR pszOutput)
{
    LONG        Status;
    CHAR        Buffer[0x400];
    CFileDisk   file;

    Status = CreateDefinition(pszAsFile, Buffer);
    AS_IF_FAIL_RETURN(Status);

    Status = ASDECL_ERROR_UNKNOWN;
    LOOP_ONCE
    {
        if (!file.Create(pszOutput))
            AS_BREAK(Status, ASDECL_ERROR_CREATE_FILE);

        _wsetlocale(LC_CTYPE, L"");
        WriteScr(
            "@_FILE \"debug_%S\"\n"
            "@_INCLUDE \"%s\"\n"
            "\n",
            findnamew(pszAsFile), NAME_DEFINITION_FILE);

        WriteScr(
            "@%s %d\n"
            "\n",
            NAME_HEADER_UNKNOWN,
            pAsInfo->Unknown);

        WriteScr(
            "(%s:s)\n"
            "(%s:s)\n"
            "(%s:s)\n"
            "\n",
            LABEL_CRAFT_OFFSET_TABLE,
            LABEL_CRAFT_OFFSET_TABLE_END,
            NAME_HEADER_UNKNOWN);

        WriteScr("; Char chip pattern info  CH_Index, CH_DAT_Index, CP_Index, CP_DAT_Index\n");

        CHAR_CHIP_PATTERN_INFO *pChipPtn = pAsInfo->pChrChipPtnInfo;
        for (ULONG Index = 0, Count = pAsInfo->ChrChipPtnCount; Count; ++Index, --Count)
        {
            WriteScr(
                " (0x%04X:s, 0x%04X:s, 0x%04X:s, 0x%04X:s)",
                pChipPtn->CHIndex,
                pChipPtn->CHDatIndex,
                pChipPtn->CPIndex,
                pChipPtn->CPDatIndex);
            ++pChipPtn;

            if (Index & 1)
                WriteScr("\n");
        }
        WriteScr("\n[FF FF FF FF]\n\n");

        WriteScr("; 3d model file\n");

        for (LPSTR pszX3FileName = pAsInfo->pszXFileName; ; )
        {
            LPSTR pString;
            ULONG Length;

            Length  = StrLengthA(pszX3FileName) + 1;
            pString = *pszX3FileName == 0 ? NULL : AllocString(pszX3FileName, Length);
            WriteScr("\"%s\"\n", pString == NULL ? pszX3FileName : pString);
            FreeString(pString);

            if (*pszX3FileName == 0)
            {
                if (pszX3FileName != pAsInfo->pszXFileName)
                    WriteScr("[%02X %02X]\n", pszX3FileName[1], pszX3FileName[2]);
                break;
            }

            pszX3FileName += Length;
        }

        WriteScr("\n#%s\n", LABEL_CRAFT_OFFSET_TABLE);

        ED6_AS_CRAFT_INFO *pCraft;
        ED6_INSTRUCTION   *pInstruction;

        pCraft = pAsInfo->pCraftInfo;
        for (ULONG Index = 0, Count = pAsInfo->CraftCount; Count; ++pCraft, ++Index, --Count)
        {
            ULONG TrueIndex;

            if (pCraft->Offset == ED6_INVALID_OFFSET)
            {
                PBYTE p = (PBYTE)&pCraft->Offset;

                WriteScr("[%02X", *p++);
                for (ULONG Len = sizeof(ED6_INVALID_OFFSET) - 1; Len; --Len)
                    WriteScr(" %02X", *p++);
                WriteScr("]\n");

                continue;
            }

            pInstruction = UnlinkInstruction(pCraft->pInstruction);
            if (pInstruction == NULL)
                continue;

            TrueIndex = Index;
            for (ULONG i = 0; i != Index; ++i)
            {
                if (pInstruction->Offset == pAsInfo->pCraftInfo[i].Offset)
                {
                    TrueIndex = i;
                    break;
                }
            }

            GetCraftName(pAsInfo, TrueIndex, Buffer);
            WriteScr(" (%s:s)", Buffer);

            if (Index >=countof(g_szIntrinsicCraft) && (Index + 1 - countof(g_szIntrinsicCraft)) % 5 != 0)
                continue;

            WriteScr("\n");
        }
        WriteScr("\n#%s\n\n", LABEL_CRAFT_OFFSET_TABLE_END);

        PBYTE pbFlags = pAsInfo->pbAsBuffer + pAsInfo->CraftOffsetTableEndOffset;
        WriteScr(
            "[%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X]\n\n",
            pbFlags[0], pbFlags[1], pbFlags[2], pbFlags[3], pbFlags[4],
            pbFlags[5], pbFlags[6], pbFlags[7], pbFlags[8], pbFlags[9],
            pbFlags[10], pbFlags[11], pbFlags[12], pbFlags[13], pbFlags[14],
            pbFlags[15], pbFlags[16]);

        Status = DumpCrafts(pAsInfo, file, Buffer);
        AS_IF_FAIL_BREAK(Status);

        Status = DumpFunctions(pAsInfo, file, Buffer);
    }

    return Status;
}