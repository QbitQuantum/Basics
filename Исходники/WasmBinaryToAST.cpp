static bool
AstDecodeName(AstDecodeContext& c, AstName* name)
{
    Bytes bytes;
    if (!c.d.readBytes(&bytes))
        return false;
    size_t length = bytes.length();
    char16_t *buffer = static_cast<char16_t *>(c.lifo.alloc(length * sizeof(char16_t)));
    for (size_t i = 0; i < length; i++)
        buffer[i] = bytes[i];
    *name = AstName(buffer, length);
    return true;
}