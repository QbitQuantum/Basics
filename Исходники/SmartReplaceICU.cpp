bool isCharacterSmartReplaceExempt(UChar32 c, bool isPreviousCharacter)
{
    return uset_contains(getSmartSet(isPreviousCharacter), c);
}