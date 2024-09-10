extern DEFTYPE_API void serializeRecordMeta(MemoryBuffer & target, IDefRecordMeta * meta, bool compress)
{
    if (compress)
    {
        MemoryBuffer temp;
        doSerializeRecordMeta(temp, meta);
        compressToBuffer(target, temp.length(), temp.toByteArray());
    }
    else
        doSerializeRecordMeta(target, meta);
}