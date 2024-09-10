static void
ProcessFile ( const char * fileName  )
{
    bool ok;
    char buffer [1000];

    SXMPMeta  xmpMeta;
    SXMPFiles xmpFile;
    XMP_FileFormat format;
    XMP_OptionBits openFlags, handlerFlags;
    XMP_PacketInfo xmpPacket;

    sprintf ( buffer, "Dumping main XMP for %s", fileName );
    WriteMinorLabel ( sLogFile, buffer );

    xmpFile.OpenFile ( fileName, kXMP_UnknownFile, kXMPFiles_OpenForRead );
    ok = xmpFile.GetFileInfo ( 0, &openFlags, &format, &handlerFlags );
    if ( ! ok ) return;

    fprintf ( sLogFile, "File info : format = \"%.4s\", handler flags = %.8X\n", &format, handlerFlags );
    fflush ( sLogFile );

    ok = xmpFile.GetXMP ( &xmpMeta, 0, &xmpPacket );
    if ( ! ok ) return;

    XMP_Int32 offset = (XMP_Int32)xmpPacket.offset;
    XMP_Int32 length = xmpPacket.length;
    fprintf ( sLogFile, "Packet info : offset = %d, length = %d\n", offset, length );
    fflush ( sLogFile );

    fprintf ( sLogFile, "\nInitial XMP from %s\n", fileName );
    xmpMeta.DumpObject ( DumpCallback, sLogFile );

    xmpFile.CloseFile();

}	// ProcessFile