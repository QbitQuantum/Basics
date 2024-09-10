unsigned char *pnd_emit_icon_to_buffer ( pnd_disco_t *p, unsigned int *r_buflen ) {
  // this is shamefully mostly a copy of emit_icon() above; really, need to refactor that to use this routine
  // with a fwrite at the end...
  char from [ FILENAME_MAX ];   // source filename
  char bits [ 8 * 1024 ];
  unsigned int bitlen;
  FILE *pnd = NULL;
  unsigned char *target = NULL, *targiter = NULL;

  // prelim .. if a pnd file, and no offset found, discovery code didn't locate icon.. so bail.
  if ( ( p -> object_type == pnd_object_type_pnd ) &&
       ( ! p -> pnd_icon_pos ) )
  {
    return ( NULL ); // discover code didn't find it, so FAIL
  }

  /* first.. open the source file, by type of application:
   * are we looking through a pnd file or a dir?
   */
  if ( p -> object_type == pnd_object_type_directory ) {
    sprintf ( from, "%s/%s", p -> object_path, p -> icon );
  } else if ( p -> object_type == pnd_object_type_pnd ) {
    sprintf ( from, "%s/%s", p -> object_path, p -> object_filename );
  }

  pnd = fopen ( from, "r" );

  if ( ! pnd ) {
    return ( NULL );
  }

  // determine length of file, then adjust by icon position to find begin of icon
  unsigned int len;

  fseek ( pnd, 0, SEEK_END );
  len = ftell ( pnd );
  //fseek ( pnd, 0, SEEK_SET );

  fseek ( pnd, p -> pnd_icon_pos, SEEK_SET );

  len -= p -> pnd_icon_pos;

  // create target buffer
  target = malloc ( len );

  if ( ! target ) {
    fclose ( pnd );
    return ( 0 );
  }

  targiter = target;

  if ( r_buflen ) {
    *r_buflen = len;
  }

  // copy over icon to target
  while ( len ) {

    if ( len > (8*1024) ) {
      bitlen = (8*1024);
    } else {
      bitlen = len;
    }

    if ( fread ( bits, bitlen, 1, pnd ) != 1 ) {
      fclose ( pnd );
      free ( target );
      return ( NULL );
    }

    memmove ( targiter, bits, bitlen );
    targiter += bitlen;

    len -= bitlen;
  } // while

  fclose ( pnd );

  return ( target );
}