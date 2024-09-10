String FileUtils::BuildValidFatFilename(
    /* [in] */ const String& name)
{
    if (name.IsEmpty() || name.Equals(String(".")) || name.Equals(String(".."))) {
        return String("(invalid)");
    }

    Int32 length = name.GetLength();
    StringBuilder res(length);
    for (Int32 i = 0; i < length; i++) {
        Char32 c = name.GetChar(i);
        if (IsValidFatFilenameChar(c)) {
            res.AppendChar(c);
        }
        else {
            res.AppendChar('_');
        }
    }
    return res.ToString();
}