// ---------------------------------------------------------------------------
// WriteData()
// ---------------------------------------------------------------------------
//
TInt TReportUtils::WriteData(HBufC8& aData, const CField* aField,
    TInt aIndex, TInt aValue)
    {
    if ( 0 <= aIndex && aIndex < aField->Count() )
        {
        // The offset in bits from the start of the report to the value
        TInt offset = aField->Offset() + aIndex * aField->Size();

        // How many bits in the least significant byte are not part of the value
        TInt bitsToShift = offset & KThreeLSB;

        TUint mask = KValueMask >> ((KSizeOfByte * sizeof(TInt)) - aField->Size());
        mask <<= bitsToShift;
        aValue <<= bitsToShift;

        TPtr8 data = aData.Des();

        // Write out the bytes, least significant first
        for ( TInt i = offset >> KThreeLSBShift; mask && i < aData.Length(); i++ )
            {
            TUint8 maskByte = static_cast<TUint8>(mask);

            // The extra cast is because MSVC6 thinks that or-ing 2
            // TUint8s together gives an int.
            data[i] = static_cast<TUint8>(
                (static_cast<TUint8>(aValue) & maskByte)
                | (aData[i] & ~maskByte));
            mask >>= KSizeOfByte;
            aValue >>= KSizeOfByte;
            }

        return KErrNone;
        }