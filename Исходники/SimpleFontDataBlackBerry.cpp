bool SimpleFontData::canRenderCombiningCharacterSequence(const UChar* characters, size_t length) const
{
    if (!m_combiningCharacterSequenceSupport)
        m_combiningCharacterSequenceSupport = adoptPtr(new HashMap<String, bool>);

    WTF::HashMap<String, bool>::AddResult addResult = m_combiningCharacterSequenceSupport->add(String(characters, length), false);
    if (!addResult.isNewEntry)
        return addResult.iterator->value;

    UErrorCode error = U_ZERO_ERROR;
    Vector<UChar, 4> normalizedCharacters(length);
    int32_t normalizedLength = unorm_normalize(characters, length, UNORM_NFC, UNORM_UNICODE_3_2, &normalizedCharacters[0], length, &error);
    if (U_FAILURE(error))
        return false;

    int position = 0;
    while (position < normalizedLength) {
        UChar32 character;
        int nextPosition = position;
        U16_NEXT(normalizedCharacters, nextPosition, normalizedLength, character);

        if (!u_hasBinaryProperty(character, UCHAR_DEFAULT_IGNORABLE_CODE_POINT)) {
            FS_USHORT glyph = FS_map_char(m_platformData.font(), static_cast<FS_ULONG>(character));
            if (!glyph)
                return false;
        }

        position = nextPosition;
    }

    addResult.iterator->value = true;
    return true;
}