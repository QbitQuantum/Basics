BSTR JSStringCopyBSTR(const JSStringRef string)
{
    return SysAllocStringLen(JSStringGetCharactersPtr(string), JSStringGetLength(string));
}