UCharIterator createIterator(StringView string)
{
    if (string.is8Bit())
        return createLatin1Iterator(string.characters8(), string.length());
    UCharIterator iterator;
    uiter_setString(&iterator, string.characters16(), string.length());
    return iterator;
}