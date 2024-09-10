ECode DhcpPacket::AddTlv(
    /* [in] */ IByteBuffer* buf,
    /* [in] */ Byte type,
    /* [in] */ const String& str)
{
    if (str != NULL) {
        buf->Put(type);
        buf->Put((Byte) str.GetLength());
        for (Int32 i = 0; i < str.GetLength(); i++) {
            buf->Put((Byte) str.GetChar(i));
        }
    }
    return NOERROR;
}