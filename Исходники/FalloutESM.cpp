void ParseRecordHeader(ESMStream& stream, RecordHeader& header) {
    //FIXME: This is not portable.
    stream.ReadRaw(&header, sizeof(header));
}