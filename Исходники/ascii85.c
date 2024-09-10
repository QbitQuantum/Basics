/**
 * This routine gets characters from the filter's underlying file, and
 * decodes them according to the ascii85 scheme. It returns the number
 * of bytes placed into the filter's buffer through the ret_bytes arguments.
 * This number is negative if the EOD is found.
 * It returns FALSE if anything goes wrong.
 *
 * \param[in,out]  filter       Input and output streams for the filter
 * \param[out]     ret_bytes    Number of bytes placed in output buffer
 *                              (negative if EOD found)
 * \return                      Success status
 */
static Bool ascii85DecodeBuffer(FILELIST *filter, int32 *ret_bytes)
{
  ASCII85DECODESTATE *ascii85state ;
  uint32    *ptr, *end;
  int32     i5, nbytes;
  FILELIST  *in;
  FOURBYTES  fb;

  HQASSERT(filter, "NULL /ASCII85Decode filter");
  ascii85state = theIFilterPrivate( filter ) ;
  HQASSERT( ascii85state, "ascii85state NULL in ascii85DecodeBuffer." ) ;

  if (ascii85state->cached_error != NOT_AN_ERROR)
    return error_handler( ascii85state->cached_error ) ;

  in = filter->underlying_file;
  ptr = (uint32 *)(filter->buffer);
  end = ptr + (filter->buffersize/sizeof(uint32));
  asInt(fb) = 0;

  HQASSERT(in, "NULL /ASCII85Decode input buffer");
  HQASSERT(ptr,  "NULL /ASCII85Decode output buffer");

  for ( i5 = 0, nbytes = 0; ptr < end; )
  {
    /*
     * Optimised code for the typical case :
     *
     * 0xffffffff (ascii85)-> s8W-! == 82/23/54/12/0
     * So if the first byte is less than 's'
     * then we do not need to test for overflow
     */
    if ( i5 == 0 && in->count > 5 && in->ptr[0] >= '!' && in->ptr[0] < 's' &&
         IS85(in->ptr[1]) && IS85(in->ptr[2]) &&
         IS85(in->ptr[3]) && IS85(in->ptr[4]) )
    {
      FOURBYTES  b4;

      asInt(b4) = POWER4 * (uint32)(in->ptr[0] - 33) +
                  POWER3 * (uint32)(in->ptr[1] - 33) +
                  POWER2 * (uint32)(in->ptr[2] - 33) +
                  POWER1 * (uint32)(in->ptr[3] - 33) +
                           (uint32)(in->ptr[4] - 33);

      HighOrder4Bytes(asBytes(b4));
      *ptr++ = asInt(b4);
      in->count -= 5;
      in->ptr   += 5;
    }
    else
    {
      register int32 ch = Getc(in);

      if ( IS85(ch) ) /* Part of valid ascii85 5-tuple */
      {
        if ( i5 == 4 )
        {
          if ( asInt(fb) > MAXHIGH4BYTES )
            return error_handler(IOERROR);
          asInt(fb) = POWER4 * (uint32)asBytes(fb)[BYTE_INDEX(0)] +
                      POWER3 * (uint32)asBytes(fb)[BYTE_INDEX(1)] +
                      POWER2 * (uint32)asBytes(fb)[BYTE_INDEX(2)] +
                      POWER1 * (uint32)asBytes(fb)[BYTE_INDEX(3)] +
                               (uint32)(ch - 33);
          HighOrder4Bytes(asBytes(fb));
          *ptr++ = asInt(fb);
          i5 = 0;
          asInt(fb) = 0;
        }
        else
          asBytes(fb)[BYTE_INDEX(i5++)] = (uint8)(ch - 33);
      }
      else if ( ch == 'z') /* special zero case */
      {
        if ( i5 != 0 )
          return error_handler(IOERROR);
        *ptr++ = 0;
      }
      else if ((ch == EOF ) || ( ch == '~' )) /* found EOD marker */
      {
        nbytes = (int32)(sizeof(uint32)*(ptr - (uint32 *)(filter->buffer)));

        if ( isIIOError(in) )
          return FALSE;
        if ( ch == '~' )
        {
          do
          {
            ch = Getc(in);
          } while ( IsWhiteSpace(ch) );

          if ( ch != '>')
            return error_handler(IOERROR);
        }
        if ( i5 > 0 ) /* only partial 5-tuple */
        {
          if ( i5 == 1 )
            return delay_filter_error(ascii85state, IOERROR, ret_bytes, nbytes);
          if ( asInt( fb ) > MAXHIGH4BYTES )
            return error_handler( IOERROR );
          asInt(fb) = POWER4 * (uint32)asBytes(fb)[BYTE_INDEX(0)] +
                      POWER3 * (uint32)asBytes(fb)[BYTE_INDEX(1)] +
                      POWER2 * (uint32)asBytes(fb)[BYTE_INDEX(2)] +
                      POWER1 * (uint32)asBytes(fb)[BYTE_INDEX(3)];
          if ( (int32)asBytes(fb)[BYTE_INDEX(i5 - 1)] >= 128 ) /* carry 1 */
            asInt(fb) += (uint32) (1 << (( 4 - i5 + 1 ) * 8 ));
          HighOrder4Bytes(asBytes(fb));
          *ptr++ = asInt(fb);
          nbytes = -(nbytes + i5 - 1);
        }
        else
          nbytes = -nbytes;
        break;
      }
      else if ( !IsWhiteSpace(ch) ) /* skip spaces, everything else errors */
        return error_handler(IOERROR);
    }
  }
  if ( nbytes == 0 )
    nbytes = (int32)(sizeof(uint32)*(ptr - (uint32 *)(filter->buffer)));
  *ret_bytes = nbytes;
  return TRUE;
}