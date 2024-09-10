String WifiTile::RemoveDoubleQuotes(
    /* [in] */ const String& string)
{
    if (string == NULL) return String(NULL);
    const Int32 length = string.GetLength();
    if ((length > 1) && (string.GetChar(0) == '"') && (string.GetChar(length - 1) == '"')) {
        return string.Substring(1, length - 1);
    }
    return string;
}