bool SkXMLParser::parse(SkStream& input)
{
    size_t          len = input.read(NULL, 0);
    SkAutoMalloc    am(len);
    char*           doc = (char*)am.get();

    input.rewind();
    size_t  len2 = input.read(doc, len);
    SkASSERT(len2 == len);

    return this->parse(doc, len2);
}