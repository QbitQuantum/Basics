int OGRDXFWriterLayer::WriteValue( int nCode, int nValue )

{
    CPLString osLinePair;

    osLinePair.Printf( "%3d\n%d\n", nCode, nValue );

    return VSIFWriteL( osLinePair.c_str(),
                       1, osLinePair.size(), fp ) == osLinePair.size();
}