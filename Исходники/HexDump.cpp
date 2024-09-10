AutoPtr<ArrayOf<Byte> > HexDump::HexStringToByteArray(
    /* [in] */ const String& hexString)
{
    Int32 length = hexString.GetLength();
    AutoPtr<ArrayOf<Byte> > buffer = ArrayOf<Byte>::Alloc(length / 2);

    for (Int32 i = 0; i < length; i += 2) {
        (*buffer)[i / 2] = (Byte)((ToByte(hexString.GetChar(i)) << 4) | ToByte(hexString.GetChar(i+1)));
    }

    return buffer;
}