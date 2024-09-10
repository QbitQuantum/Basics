void DumpImageDbgHeader(MPanelItem *pRoot, PIMAGE_SEPARATE_DEBUG_HEADER pImageSepDbgHeader)
{
    UINT headerFieldWidth = 30;

    pRoot->printf("  %-*s%04X\n", headerFieldWidth, "Flags:",
                pImageSepDbgHeader->Flags);
    pRoot->printf("  %-*s%04X %s\n", headerFieldWidth, "Machine:",
                pImageSepDbgHeader->Machine,
                GetMachineTypeName(pImageSepDbgHeader->Machine));
    pRoot->printf("  %-*s%04X\n", headerFieldWidth, "Characteristics:",
                pImageSepDbgHeader->Characteristics);
	__time32_t timeStamp = pImageSepDbgHeader->TimeDateStamp;
    pRoot->printf("  %-*s%08X -> %s", headerFieldWidth, "TimeDateStamp:",
                pImageSepDbgHeader->TimeDateStamp, _ctime32(&timeStamp) );
    pRoot->printf("  %-*s%08X\n", headerFieldWidth, "CheckSum:",
                pImageSepDbgHeader->CheckSum);
    pRoot->printf("  %-*s%08X\n", headerFieldWidth, "ImageBase:",
                pImageSepDbgHeader->ImageBase);
    pRoot->printf("  %-*s%08X\n", headerFieldWidth, "Size of Image:",
                pImageSepDbgHeader->SizeOfImage);
    pRoot->printf("  %-*s%04X\n", headerFieldWidth, "Number of Sections:",
                pImageSepDbgHeader->NumberOfSections);
    pRoot->printf("  %-*s%04X\n", headerFieldWidth, "ExportedNamesSize:",
                pImageSepDbgHeader->ExportedNamesSize);
    pRoot->printf("  %-*s%08X\n", headerFieldWidth, "DebugDirectorySize:",
                pImageSepDbgHeader->DebugDirectorySize);
    pRoot->printf("  %-*s%08X\n", headerFieldWidth, "SectionAlignment:",
                pImageSepDbgHeader->SectionAlignment);
}