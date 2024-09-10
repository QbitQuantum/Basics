U_NAMESPACE_BEGIN

le_uint32 LookupProcessor::applyLookupTable(const LEReferenceTo<LookupTable> &lookupTable, GlyphIterator *glyphIterator,
                                         const LEFontInstance *fontInstance, LEErrorCode& success) const
{
    if (LE_FAILURE(success)) {
        return 0;
    }

    le_uint16 lookupType = SWAPW(lookupTable->lookupType);
    le_uint16 subtableCount = SWAPW(lookupTable->subTableCount);
    le_int32 startPosition = glyphIterator->getCurrStreamPosition();
    le_uint32 delta;

    for (le_uint16 subtable = 0; subtable < subtableCount; subtable += 1) {
      LEReferenceTo<LookupSubtable> lookupSubtable = lookupTable->getLookupSubtable(lookupTable, subtable, success);

        delta = applySubtable(lookupSubtable, lookupType, glyphIterator, fontInstance, success);
        if (delta > 0 && LE_FAILURE(success)) {
#if LE_TRACE
          _LETRACE("Posn #%d, type %X, applied subtable #%d/%d - %s\n", startPosition, lookupType, subtable, subtableCount, u_errorName((UErrorCode)success));
#endif
          return 1;
        }

        glyphIterator->setCurrStreamPosition(startPosition);
    }

    return 1;
}