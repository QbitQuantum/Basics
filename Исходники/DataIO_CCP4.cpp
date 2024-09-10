// DataIO_CCP4::ID_DataFormat()
bool DataIO_CCP4::ID_DataFormat( CpptrajFile& infile ) {
    bool isCCP4 = false;
    if (!infile.OpenFile()) {
        unsigned char MAP[4];
        if (infile.Seek(52 * wSize) == 0) {
            infile.Read( MAP, wSize );
            isCCP4 = MapCharsValid( MAP );
        }
        infile.CloseFile();
    }
    return isCCP4;
}