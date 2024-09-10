String createStringWithMirroredCharacters(StringView string)
{
    unsigned length = string.length();
    StringBuilder mirroredCharacters;
    mirroredCharacters.reserveCapacity(length);
    for (unsigned i = 0; i < length; ) {
        UChar32 character;
        U16_NEXT(string, i, length, character);
        mirroredCharacters.append(u_charMirror(character));
    }
    return mirroredCharacters.toString();
}