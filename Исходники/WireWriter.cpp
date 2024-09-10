bool WireWriter::writeTag(const char *tag, int split, int len) {
    if (!split) {
        return writeString(tag);
    }
    ConstString bit = "";
    char ch = 'x';
    while (ch!='\0') {
        ch = *tag;
        tag++;
        if (ch=='\0'||ch=='_') {
            if (bit.length()<=4) {
                writer.appendInt(BOTTLE_TAG_VOCAB);
                writer.appendInt(Vocab::encode(bit));
            } else {
                writeString(bit.c_str());
            }
            bit = "";
        } else {
            bit += ch;
        }
    }
    return true;
}