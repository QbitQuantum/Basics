STATIC
UINT64*
GetBlockEntryListFromAddress (
  IN  UINT64       *RootTable,
  IN  UINT64        RegionStart,
  OUT UINTN        *TableLevel,
  IN OUT UINT64    *BlockEntrySize,
  OUT UINT64      **LastBlockEntry
  )
{
  UINTN   RootTableLevel;
  UINTN   RootTableEntryCount;
  UINT64 *TranslationTable;
  UINT64 *BlockEntry;
  UINT64 *SubTableBlockEntry;
  UINT64  BlockEntryAddress;
  UINTN   BaseAddressAlignment;
  UINTN   PageLevel;
  UINTN   Index;
  UINTN   IndexLevel;
  UINTN   T0SZ;
  UINT64  Attributes;
  UINT64  TableAttributes;

  // Initialize variable
  BlockEntry = NULL;

  // Ensure the parameters are valid
  if (!(TableLevel && BlockEntrySize && LastBlockEntry)) {
    ASSERT_EFI_ERROR (EFI_INVALID_PARAMETER);
    return NULL;
  }

  // Ensure the Region is aligned on 4KB boundary
  if ((RegionStart & (SIZE_4KB - 1)) != 0) {
    ASSERT_EFI_ERROR (EFI_INVALID_PARAMETER);
    return NULL;
  }

  // Ensure the required size is aligned on 4KB boundary and not 0
  if ((*BlockEntrySize & (SIZE_4KB - 1)) != 0 || *BlockEntrySize == 0) {
    ASSERT_EFI_ERROR (EFI_INVALID_PARAMETER);
    return NULL;
  }

  T0SZ = ArmGetTCR () & TCR_T0SZ_MASK;
  // Get the Table info from T0SZ
  GetRootTranslationTableInfo (T0SZ, &RootTableLevel, &RootTableEntryCount);

  // If the start address is 0x0 then we use the size of the region to identify the alignment
  if (RegionStart == 0) {
    // Identify the highest possible alignment for the Region Size
    BaseAddressAlignment = LowBitSet64 (*BlockEntrySize);
  } else {
    // Identify the highest possible alignment for the Base Address
    BaseAddressAlignment = LowBitSet64 (RegionStart);
  }

  // Identify the Page Level the RegionStart must belong to. Note that PageLevel
  // should be at least 1 since block translations are not supported at level 0
  PageLevel = MAX (3 - ((BaseAddressAlignment - 12) / 9), 1);

  // If the required size is smaller than the current block size then we need to go to the page below.
  // The PageLevel was calculated on the Base Address alignment but did not take in account the alignment
  // of the allocation size
  while (*BlockEntrySize < TT_BLOCK_ENTRY_SIZE_AT_LEVEL (PageLevel)) {
    // It does not fit so we need to go a page level above
    PageLevel++;
  }

  //
  // Get the Table Descriptor for the corresponding PageLevel. We need to decompose RegionStart to get appropriate entries
  //

  TranslationTable = RootTable;
  for (IndexLevel = RootTableLevel; IndexLevel <= PageLevel; IndexLevel++) {
    BlockEntry = (UINT64*)TT_GET_ENTRY_FOR_ADDRESS (TranslationTable, IndexLevel, RegionStart);

    if ((IndexLevel != 3) && ((*BlockEntry & TT_TYPE_MASK) == TT_TYPE_TABLE_ENTRY)) {
      // Go to the next table
      TranslationTable = (UINT64*)(*BlockEntry & TT_ADDRESS_MASK_DESCRIPTION_TABLE);

      // If we are at the last level then update the last level to next level
      if (IndexLevel == PageLevel) {
        // Enter the next level
        PageLevel++;
      }
    } else if ((*BlockEntry & TT_TYPE_MASK) == TT_TYPE_BLOCK_ENTRY) {
      // If we are not at the last level then we need to split this BlockEntry
      if (IndexLevel != PageLevel) {
        // Retrieve the attributes from the block entry
        Attributes = *BlockEntry & TT_ATTRIBUTES_MASK;

        // Convert the block entry attributes into Table descriptor attributes
        TableAttributes = TT_TABLE_AP_NO_PERMISSION;
        if (Attributes & TT_NS) {
          TableAttributes = TT_TABLE_NS;
        }

        // Get the address corresponding at this entry
        BlockEntryAddress = RegionStart;
        BlockEntryAddress = BlockEntryAddress >> TT_ADDRESS_OFFSET_AT_LEVEL(IndexLevel);
        // Shift back to right to set zero before the effective address
        BlockEntryAddress = BlockEntryAddress << TT_ADDRESS_OFFSET_AT_LEVEL(IndexLevel);

        // Set the correct entry type for the next page level
        if ((IndexLevel + 1) == 3) {
          Attributes |= TT_TYPE_BLOCK_ENTRY_LEVEL3;
        } else {
          Attributes |= TT_TYPE_BLOCK_ENTRY;
        }

        // Create a new translation table
        TranslationTable = (UINT64*)AllocateAlignedPages (EFI_SIZE_TO_PAGES(TT_ENTRY_COUNT * sizeof(UINT64)), TT_ALIGNMENT_DESCRIPTION_TABLE);
        if (TranslationTable == NULL) {
          return NULL;
        }

        // Populate the newly created lower level table
        SubTableBlockEntry = TranslationTable;
        for (Index = 0; Index < TT_ENTRY_COUNT; Index++) {
          *SubTableBlockEntry = Attributes | (BlockEntryAddress + (Index << TT_ADDRESS_OFFSET_AT_LEVEL(IndexLevel + 1)));
          SubTableBlockEntry++;
        }

        // Fill the BlockEntry with the new TranslationTable
        ReplaceLiveEntry (BlockEntry,
          ((UINTN)TranslationTable & TT_ADDRESS_MASK_DESCRIPTION_TABLE) | TableAttributes | TT_TYPE_TABLE_ENTRY);
      }
    } else {
      if (IndexLevel != PageLevel) {