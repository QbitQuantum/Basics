  ft_io_stream( FT_Stream       stream,
                unsigned long   offset,
                unsigned char*  buffer,
                unsigned long   count )
  {
//  FILE*  file;
    BPTR   file;        // TetiSoft


    file = STREAM_FILE( stream );

//  fseek( file, offset, SEEK_SET );
    Seek( file, offset, OFFSET_BEGINNING );     // TetiSoft

//  return (unsigned long)fread( buffer, 1, count, file );
    return (unsigned long)FRead( file, buffer, 1, count);
  }