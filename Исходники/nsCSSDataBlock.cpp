void
nsCSSExpandedDataBlock::Compress(nsCSSCompressedDataBlock **aNormalBlock,
                                 nsCSSCompressedDataBlock **aImportantBlock,
                                 const nsTArray<uint32_t>& aOrder)
{
    nsAutoPtr<nsCSSCompressedDataBlock> result_normal, result_important;
    uint32_t i_normal = 0, i_important = 0;

    uint32_t numPropsNormal, numPropsImportant;
    ComputeNumProps(&numPropsNormal, &numPropsImportant);

    result_normal =
        new(numPropsNormal) nsCSSCompressedDataBlock(numPropsNormal);

    if (numPropsImportant != 0) {
        result_important =
            new(numPropsImportant) nsCSSCompressedDataBlock(numPropsImportant);
    } else {
        result_important = nullptr;
    }

    /*
     * Save needless copying and allocation by copying the memory
     * corresponding to the stored data in the expanded block, and then
     * clearing the data in the expanded block.
     */
    for (size_t i = 0; i < aOrder.Length(); i++) {
        nsCSSProperty iProp = static_cast<nsCSSProperty>(aOrder[i]);
        if (iProp >= eCSSProperty_COUNT) {
            // a custom property
            continue;
        }
        MOZ_ASSERT(mPropertiesSet.HasProperty(iProp),
                   "aOrder identifies a property not in the expanded "
                   "data block");
        MOZ_ASSERT(!nsCSSProps::IsShorthand(iProp), "out of range");
        bool important = mPropertiesImportant.HasProperty(iProp);
        nsCSSCompressedDataBlock *result =
            important ? result_important : result_normal;
        uint32_t* ip = important ? &i_important : &i_normal;
        nsCSSValue* val = PropertyAt(iProp);
        MOZ_ASSERT(val->GetUnit() != eCSSUnit_Null,
                   "Null value while compressing");
        result->SetPropertyAtIndex(*ip, iProp);
        result->RawCopyValueToIndex(*ip, val);
        new (val) nsCSSValue();
        (*ip)++;
        result->mStyleBits |=
            nsCachedStyleData::GetBitForSID(nsCSSProps::kSIDTable[iProp]);
    }

    MOZ_ASSERT(numPropsNormal == i_normal, "bad numProps");

    if (result_important) {
        MOZ_ASSERT(numPropsImportant == i_important, "bad numProps");
    }

#ifdef DEBUG
    {
      // assert that we didn't have any other properties on this expanded data
      // block that we didn't find in aOrder
      uint32_t numPropsInSet = 0;
      for (size_t iHigh = 0; iHigh < nsCSSPropertySet::kChunkCount; iHigh++) {
          if (!mPropertiesSet.HasPropertyInChunk(iHigh)) {
              continue;
          }
          for (size_t iLow = 0; iLow < nsCSSPropertySet::kBitsInChunk; iLow++) {
              if (mPropertiesSet.HasPropertyAt(iHigh, iLow)) {
                  numPropsInSet++;
              }
          }
      }
      MOZ_ASSERT(numPropsNormal + numPropsImportant == numPropsInSet,
                 "aOrder missing properties from the expanded data block");
    }
#endif

    ClearSets();
    AssertInitialState();
    *aNormalBlock = result_normal.forget();
    *aImportantBlock = result_important.forget();
}