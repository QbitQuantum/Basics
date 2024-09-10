void
OMXMLWriterSimple::writeProlog(void)
{
    TRACE("OMXMLWriterSimple::writeProlog");
    
    if (_encoding == UTF16)
    {
        OMUInt8 bom[2];
        if (_byteOrder == BE)
        {
            bom[0] = 0xFE;
            bom[1] = 0xFF;
        }
        else
        {
            bom[0] = 0xFF;
            bom[1] = 0xFE;
        }
        writeRaw(bom, 2);
    }

    write(L"<?xml version=\"1.0\" encoding=\"", 30);
    if (_encoding == UTF8)
    {
        write(L"UTF-8\"?>\n", 9);
    }
    else
    {
        write(L"UTF-16\"?>\n", 10);
    }
}