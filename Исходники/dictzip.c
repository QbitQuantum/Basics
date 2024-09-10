static int dict_read_header( const char *filename,
			     dictData *header, int computeCRC )
{
   FILE          *str;
   int           id1, id2, si1, si2;
   char          buffer[BUFFERSIZE];
   int           extraLength, subLength;
   int           i;
   char          *pt;
   int           c;
   struct stat   sb;
   unsigned long crc   = crc32( 0L, Z_NULL, 0 );
   int           count;
   unsigned long offset;

   if (!(str = gd_fopen( filename, "rb" )))
   {
      err_fatal_errno( __func__,
		       "Cannot open data file \"%s\" for read\n", filename );
      return 1;
   }

   header->filename     = NULL;//str_find( filename );
   header->headerLength = GZ_XLEN - 1;
   header->type         = DICT_UNKNOWN;
   
   id1                  = getc( str );
   id2                  = getc( str );

   if (id1 != GZ_MAGIC1 || id2 != GZ_MAGIC2) {
      header->type = DICT_TEXT;
      fstat( fileno( str ), &sb );
      header->compressedLength = header->length = sb.st_size;
      header->origFilename     = NULL;//str_find( filename );
      header->mtime            = sb.st_mtime;
      if (computeCRC) {
	 rewind( str );
	 while (!feof( str )) {
	    if ((count = fread( buffer, 1, BUFFERSIZE, str ))) {
	       crc = crc32( crc, (Bytef *)buffer, count );
	    }
	 }
      }
      header->crc = crc;
      fclose( str );
      return 0;
   }
   header->type = DICT_GZIP;
   
   header->method       = getc( str );
   header->flags        = getc( str );
   header->mtime        = getc( str ) <<  0;
   header->mtime       |= getc( str ) <<  8;
   header->mtime       |= getc( str ) << 16;
   header->mtime       |= getc( str ) << 24;
   header->extraFlags   = getc( str );
   header->os           = getc( str );
   
   if (header->flags & GZ_FEXTRA) {
      extraLength          = getc( str ) << 0;
      extraLength         |= getc( str ) << 8;
      header->headerLength += extraLength + 2;
      si1                  = getc( str );
      si2                  = getc( str );
      
      if (si1 == GZ_RND_S1 && si2 == GZ_RND_S2) {
	 subLength            = getc( str ) << 0;
	 subLength           |= getc( str ) << 8;
	 header->version      = getc( str ) << 0;
	 header->version     |= getc( str ) << 8;
	 
	 if (header->version != 1)
	 {
	    err_internal( __func__,
			  "dzip header version %d not supported\n",
			  header->version );
	    fclose( str );
	    return 1;
	 }
   
	 header->chunkLength  = getc( str ) << 0;
	 header->chunkLength |= getc( str ) << 8;
	 header->chunkCount   = getc( str ) << 0;
	 header->chunkCount  |= getc( str ) << 8;
	 
	 if (header->chunkCount <= 0) {
	    fclose( str );
	    return 5;
	 }
	 header->chunks = xmalloc( sizeof( header->chunks[0] )
				   * header->chunkCount );
	 for (i = 0; i < header->chunkCount; i++) {
	    header->chunks[i]  = getc( str ) << 0;
	    header->chunks[i] |= getc( str ) << 8;
	 }
	 header->type = DICT_DZIP;
      } else {
	 fseek( str, header->headerLength, SEEK_SET );
      }
   }
   
   if (header->flags & GZ_FNAME) { /* FIXME! Add checking against header len */
      pt = buffer;
      while ((c = getc( str )) && c != EOF){
	 *pt++ = c;

	 if (pt == buffer + sizeof (buffer)){
	    err_fatal (
	       __func__,
	       "too long FNAME field in dzip file \"%s\"\n", filename);
	    fclose( str );
	    return 1;
	 }
      }

      *pt = '\0';
      header->origFilename = NULL;//str_find( buffer );
      header->headerLength += strlen( buffer ) + 1;
   } else {
      header->origFilename = NULL;
   }
   
   if (header->flags & GZ_COMMENT) { /* FIXME! Add checking for header len */
      pt = buffer;
      while ((c = getc( str )) && c != EOF){
	 *pt++ = c;

	 if (pt == buffer + sizeof (buffer)){
	    err_fatal (
	       __func__,
	       "too long COMMENT field in dzip file \"%s\"\n", filename);
	    fclose( str );
	    return 1;
	 }
      }

      *pt = '\0';
      header->comment = NULL;//str_find( buffer );
      header->headerLength += strlen( header->comment ) + 1;
   } else {
      header->comment = NULL;
   }

   if (header->flags & GZ_FHCRC) {
      getc( str );
      getc( str );
      header->headerLength += 2;
   }

   if (ftell( str ) != header->headerLength + 1)
   {
      err_internal( __func__,
		    "File position (%lu) != header length + 1 (%d)\n",
		    ftell( str ), header->headerLength + 1 );
      fclose( str );
      return 1;
   }

   fseek( str, -8, SEEK_END );
   header->crc     = getc( str ) <<  0;
   header->crc    |= getc( str ) <<  8;
   header->crc    |= getc( str ) << 16;
   header->crc    |= getc( str ) << 24;
   header->length  = getc( str ) <<  0;
   header->length |= getc( str ) <<  8;
   header->length |= getc( str ) << 16;
   header->length |= getc( str ) << 24;
   header->compressedLength = ftell( str );

				/* Compute offsets */
   header->offsets = xmalloc( sizeof( header->offsets[0] )
			      * header->chunkCount );
   for (offset = header->headerLength + 1, i = 0;
	i < header->chunkCount;
	i++)
   {
      header->offsets[i] = offset;
      offset += header->chunks[i];
   }

   fclose( str );
   return 0;
}